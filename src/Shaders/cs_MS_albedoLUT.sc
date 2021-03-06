
#define WRITE_LUT
#include "common.sh"
#include "pbr.sh"

#define GROUP_SIZE 256
#define THREADS 16
// Karis 2014
vec2 integrateBRDF(float roughness, float NoV)
{
	vec3 V;
    V.x = sqrt(1.0 - NoV * NoV); // sin
    V.y = NoV;
    V.z = 0.0; // cos

    // N points straight upwards for this integration
    const vec3 N = vec3(0.0, 1.0, 0.0);

    float A = 0.0;
    float B = 0.0;
    const uint numSamples = 1024;

    for (uint i = 0u; i < numSamples; i++) {
        vec2 Xi = hammersley(i, numSamples);
        // Sample microfacet direction
        vec3 H = importanceSampleGGX(Xi, roughness, N);

        // Get the light direction
        vec3 L = 2.0 * dot(V, H) * H - V;

        float NoL = saturate(dot(N, L));
        float NoH = saturate(dot(N, H));
        float VoH = saturate(dot(V, H));

        if (NoL > 0.0) {
            // Terms besides V are from the GGX PDF we're dividing by
            float V_pdf = V_SmithGGXCorrelated(NoV, NoL, roughness) * VoH * NoL / NoH;
            float Fc = pow(1.0 - VoH, 5.0);
            A += (1.0 - Fc) * V_pdf;
            B += Fc * V_pdf;
        }
    }

    return 4.0 * vec2(A, B) / float(numSamples);
}


NUM_THREADS(THREADS, THREADS, 1)
void main()
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = vec2(gl_GlobalInvocationID.xy) / vec2(imageSize(i_texAlbedoLUT).xy);
    float mu = max(uv.x, 0.001); //Stop division by 0 and NaN
    float a = max(uv.y, MIN_ROUGHNESS);


    // Output to screen
    vec2 res = integrateBRDF(a, mu);

    // Scale and Bias for F0 (as per Karis 2014)
    imageStore(i_texAlbedoLUT, ivec2(gl_GlobalInvocationID.xy), vec4(res, 0.0, 0.0));
}