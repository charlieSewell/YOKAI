$input a_position, a_normal, a_tangent, a_texcoord0, a_indices, a_weight
$output v_position, v_normal, v_tangent, v_bitangent, v_texcoord0

#include "common.sh"
#include <bgfx_shader.sh>

// model transformation for normals to preserve perpendicularity
// usually this is based on the model view matrix
// but shading is done in world space
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 u_boneTransforms[100];

uniform mat4 u_normalMatrix;

void main()
{
    
    vec4 PosL = vec4(a_position, 1.0);
    
    #ifdef SKINNED_MESH
        mat4 BoneTransform = u_boneTransforms[a_indices.x] * a_weight.x;
        BoneTransform +=     u_boneTransforms[a_indices.y] * a_weight.y;
        BoneTransform +=     u_boneTransforms[a_indices.z] * a_weight.z;
        BoneTransform +=     u_boneTransforms[a_indices.w] * a_weight.w;
        PosL = mul(BoneTransform, vec4(a_position, 1.0));
    #endif

    v_position = mul(u_model[0], a_position.xyz);

    v_normal    = normalize(mul(u_normalMatrix, vec4(a_normal, 0.0)).xyz);
    v_tangent   = normalize(mul(u_model[0], vec4(a_tangent.xyz, 0.0)).xyz);
    v_bitangent = normalize(cross(v_normal, v_tangent)) * a_tangent.w;

    v_texcoord0 = a_texcoord0;

    gl_Position = mul(u_modelViewProj, PosL);
}