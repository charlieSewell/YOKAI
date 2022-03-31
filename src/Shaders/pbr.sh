#include "common.sh"
#ifndef PBR_SH_HEADER_GUARD
#define PBR_SH_HEADER_GUARD

#define PI     (3.141592653589793)
#define INV_PI (0.31830988618)
#define MIN_ROUGHNESS 0.045

struct PBRMaterial
{
    vec4 albedo;
    float metallic;
    float roughness;
    vec3 normal;
    float occlusion;
    vec3 emissive;

    // calculated from the above

    vec3 diffuseColor; // this becomes black for higher metalness
    vec3 F0; // Fresnel reflectance at normal incidence
    float a; // remapped roughness (^2)
};

#ifdef WRITE_LUT
IMAGE2D_WR(i_texAlbedoLUT, rg16f, 0);
#else
SAMPLER2D(s_texAlbedoLUT, 0);
#endif

// only define this if you need to retrieve the material parameters
// without it you can still use the struct definition or BRDF functions
#ifdef READ_MATERIAL

SAMPLER2D(s_texBaseColor,         1);
SAMPLER2D(s_texMetallicRoughness, 2);
SAMPLER2D(s_texNormal,            3);
SAMPLER2D(s_texOcclusion,         4);
SAMPLER2D(s_texEmissive,          5);
// Light Buffer has 6
SAMPLERCUBE(s_prefilterMap,         7);
SAMPLERCUBE(s_irradianceMap,         8);


uniform vec4 u_baseColorFactor;
uniform vec4 u_factors;
uniform vec4 u_emissiveFactorVec;
uniform vec4 u_hasTextures;

#define u_metallicRoughnessFactor (u_factors.xy)
#define u_normalScale             (u_factors.z)
#define u_occlusionStrength       (u_factors.w)
#define u_emissiveFactor          (u_emissiveFactorVec.xyz)

#endif // READ_MATERIAL

#if BGFX_SHADER_TYPE_FRAGMENT
// Reduce specular aliasing by producing a modified roughness value
// Tokuyoshi et al. 2019. Improved Geometric Specular Antialiasing.
// http://www.jp.square-enix.com/tech/library/pdf/ImprovedGeometricSpecularAA.pdf
float specularAntiAliasing(vec3 N, float a)
{
    // normal-based isotropic filtering
    // this is originally meant for deferred rendering but is a bit simpler to implement than the forward version
    // saves us from calculating uv offsets and sampling textures for every light
    const float SIGMA2 = 0.25; // squared std dev of pixel filter kernel (in pixels)
    const float KAPPA  = 0.18; // clamping threshold
    vec3 dndu = dFdx(N);
    vec3 dndv = dFdy(N);
    float variance = SIGMA2 * (dot(dndu, dndu) + dot(dndv, dndv));
    float kernelRoughness2 = min(2.0 * variance, KAPPA);
    return saturate(a + kernelRoughness2);
}
// Turquin. 2018. Practical multiple scattering compensation for microfacet models.
// https://blog.selfshadow.com/publications/turquin/ms_comp_final.pdf
vec3 multipleScatteringFactor(float a, vec3 F0, float metallic, float NoV)
{
    // Turquin approximates the multiple scattering portion of the BRDF using a scaled down version of the single scattering BRDF
    // That scale factor is E: the directional albedo for single scattering, ie. the total reflectance for a viewing direction
    vec2 E = texture2D(s_texAlbedoLUT, vec2(NoV, a)).xy;

    // for metals, the albedo value is calculated with F = 1 (perfect reflection)
    // fresnel determines whether light is reflected or absorbed
    vec3 factorMetallic = vec3_splat(1.0) + F0 * (1.0 / E.x - 1.0);

    // for dielectrics, fresnel determines the ratio between specular and diffuse energy
    // so the albedo depends on F as a variable
    // however, dielectrics in GLTF have a fixed F0 of 0.04 so we can do this with a second LUT
    vec3 factorDielectric = vec3_splat(1.0 / E.y);

    return mix(factorDielectric, factorMetallic, metallic);
}
#endif

// Physically based shading
// Metallic + roughness workflow (GLTF 2.0 core material spec)
// BRDF, no sub-surface scattering
// https://github.com/KhronosGroup/glTF/tree/master/specification/2.0#metallic-roughness-material
// Some GLSL code taken from
// https://google.github.io/filament/Filament.md.html
// and
// https://learnopengl.com/PBR/Lighting

// Schlick approximation to Fresnel equation
vec3 F_Schlick(float VoH, vec3 F0)
{
    float val = 1.0 - VoH;
    return F0 + (1.0 - F0) * (val*val*val*val*val); //Faster than pow
}
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness, 1.0 - roughness, 1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}   

// Normal Distribution Function
// (aka specular distribution)
// distribution of microfacets

// Bruce Walter et al. 2007. Microfacet Models for Refraction through Rough Surfaces.
// equivalent to Trowbridge-Reitz
float D_GGX(float NoH, float a)
{
    a = NoH * a;
    float k = a / (1.0 - NoH * NoH + a * a);
    return k * k * INV_PI;
}

// Visibility function
// = Geometric Shadowing/Masking Function G, divided by the denominator of the Cook-Torrance BRDF (4 NoV NoL)
// G is the probability of the microfacet being visible in the outgoing (masking) or incoming (shadowing) direction

// Heitz 2014. Understanding the Masking-Shadowing Function in Microfacet-Based BRDFs.
// http://jcgt.org/published/0003/02/03/paper.pdf
// based on height-correlated Smith-GGX
float V_SmithGGXCorrelated(float NoV, float NoL, float a)
{
    float a2 = a * a;
    float GGXV = NoL * sqrt(NoV * NoV * (1.0 - a2) + a2);
    float GGXL = NoV * sqrt(NoL * NoL * (1.0 - a2) + a2);
    return 0.5 / (GGXV + GGXL);
}

// version without height-correlation
float V_SmithGGX(float NoV, float NoL, float a)
{
    float a2 = a * a;
    float GGXV = NoV + sqrt(NoV * NoV * (1.0 - a2) + a2);
    float GGXL = NoL + sqrt(NoL * NoL * (1.0 - a2) + a2);
    return 1.0 / (GGXV * GGXL);
}

// Lambertian diffuse BRDF
// uniform color
float Fd_Lambert()
{
    // normalize to conserve energy
    // cos integrates to pi over the hemisphere
    // incoming light is multiplied by cos and BRDF
    return INV_PI;
}

vec2 hammersley(uint i, uint N)
{
    uint bits = (i << 16u) | (i >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    float rdi = float(bits) * 2.3283064365386963e-10;
    return vec2(float(i) /float(N), rdi);
}

vec3 toWorldCoords(ivec3 globalId, float size)
{
    vec2 uvc = (vec2(globalId.xy) + 0.5) / size;
    uvc = 2.0 * uvc - 1.0;
    uvc.y *= -1.0;
    switch (globalId.z) {
    case 0:
        return vec3(1.0, uvc.y, -uvc.x);
    case 1:
        return vec3(-1.0, uvc.y, uvc.x);
    case 2:
        return vec3(uvc.x, 1.0, -uvc.y);
    case 3:
        return vec3(uvc.x, -1.0, uvc.y);
    case 4:
        return vec3(uvc.x, uvc.y, 1.0);
    default:
        return vec3(-uvc.x, uvc.y, -1.0);
    }
}

// Based on Karis 2014
vec3 importanceSampleGGX(vec2 Xi, float roughness, vec3 N)
{
    float a = roughness * roughness;
    // Sample in spherical coordinates
    float phi = 2.0 * PI * Xi.x;
    float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a * a - 1.0) * Xi.y));
    float sinTheta = sqrt(1.0 - cosTheta * cosTheta);
    // Construct tangent space vector
    vec3 H = vec3(
        sinTheta * cos(phi),
        sinTheta * sin(phi),
        cosTheta
    );
    // Tangent to world space
    vec3 upVector = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
    vec3 tangentX = normalize(cross(upVector, N));
    vec3 tangentY = normalize(cross(N, tangentX));
    return normalize(tangentX * H.x + tangentY * H.y + N * H.z);
    // Convert to world Space
    return normalize(tangentX * H.x + tangentY * H.y + N * H.z);
}

#endif // PBR_SH_HEADER_GUARD