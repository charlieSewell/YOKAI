$input v_position, v_normal, v_tangent, v_bitangent, v_texcoord0

#define READ_MATERIAL

#define DIELECTRIC_SPECULAR 0.04
#define MIN_ROUGHNESS 0.045

#include "common.sh"
#include "util.sh"
#include "pbr.sh"
#include "lights.sh"

uniform vec4 u_envParams;
#define numEnvLevels u_envParams.x

uniform vec4 u_camPos;

void main()
{
    //MikktSpace normals
    vec3 N = texture2D(s_texNormal, v_texcoord0).xyz * 2.0 - 1.0;
    N = normalize(N.x * v_tangent + N.y * v_bitangent + N.z * v_normal);
    //View Dir
    vec3 V = normalize(u_camPos.xyz - v_position);
    
    vec3 lightDir = reflect(-V, N);
    
    vec3 H = normalize(lightDir + V);
    float VoH = clampDot(V, H);
    float NoV = clamp(dot(N, V), 1e-5, 1.0);

    vec4 baseColor = toLinear(texture2D(s_texBaseColor, v_texcoord0)) * u_baseColorFactor;
    vec2 roughnessMetal = texture2D(s_texMetallicRoughness, v_texcoord0).yz;
    float roughness = max(roughnessMetal.x * u_metallicRoughnessFactor.g, MIN_ROUGHNESS);
    float metallic = roughnessMetal.y * u_metallicRoughnessFactor.r;
    float occlusion = texture2D(s_texOcclusion, v_texcoord0).x;
    vec3 emissive = toLinear(texture2D(s_texEmissive, v_texcoord0)).xyz * u_emissiveFactor;

    // From GLTF spec
    vec3 c_diff = baseColor * (1.0 - DIELECTRIC_SPECULAR) * (1.0 - metallic);
    vec3 F0 = mix(vec3_splat(DIELECTRIC_SPECULAR), baseColor.xyz, metallic);

    float a = roughness * roughness;
    a = specularAntiAliasing(N, a);
    a = max(a, 0.00001);

    vec3 radianceOut = vec3_splat(0.0);

    uint lights = pointLightCount();
    for(uint i = 0; i < lights; i++)
    {
        PointLight light = getPointLight(i);
        float dist = distance(light.position, v_position);
        float attenuation = smoothAttenuation(dist, light.radius);
        if(attenuation > 0.0)
        {
            vec3 L = normalize(light.position - v_position);
            vec3 H = normalize(V + L);
            vec3 radiance = light.intensity * attenuation *100;
            
            float NoL = clampDot(N, L);
            float NoH = clampDot(N, H);
            float VoH = clampDot(V, H);
            
            float NDF = D_GGX(NoH, roughness);
            float G = V_SmithGGXCorrelated(NoV, NoL, roughness);
            vec3 F = F_Schlick(VoH, F0);
            
            vec3 BRDF   = NDF * G * F;

            vec3 lightColor = attenuation * light.intensity * NoL;
            radianceOut += (c_diff + PI * BRDF) * lightColor;
        }
    }
    //radianceOut += getAmbientLight().irradiance * mat.diffuseColor * mat.occlusion;
    //radianceOut += emissive;

    vec2 f_ab = texture2D(s_texAlbedoLUT, vec2(NoV, roughness)).xy;
    float lodLevel = roughness * numEnvLevels;
    vec3 radiance = textureCubeLod(s_prefilterMap, lightDir, lodLevel).xyz;
    vec3 irradiance = textureCubeLod(s_irradianceMap, N, 0).xyz;

    vec3 k_S = F0;
    // Roughness dependent fresnel, from Fdez-Aguera
    vec3 Fr = max(vec3_splat(1.0 - roughness), F0) - F0;
    k_S += Fr * pow(1.0 - NoV, 5.0);

    vec3 FssEss = k_S * f_ab.x + f_ab.y;

    // Multiple scattering, from Fdez-Aguera
    float Ems = (1.0 - (f_ab.x + f_ab.y));
    vec3 F_avg = F0 + (1.0 - F0) / 21.0;
    vec3 FmsEms = Ems * FssEss * F_avg / (1.0 - F_avg * Ems);
    vec3 k_D = baseColor * (1.0 - FssEss - FmsEms);
    radianceOut += FssEss * radiance + (FmsEms + k_D) * irradiance;

    gl_FragColor = vec4(radianceOut * occlusion + emissive, baseColor.w);
}