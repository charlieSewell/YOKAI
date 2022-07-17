$input a_position, a_texcoord0, a_normal
$output v_texcoord0 ,v_normal

#include "common.sh" 

const int MAX_BONES = 100;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 boneTrans[100];
uniform bool isAnimated;
uniform vec3 viewPosition;

void main()
{
	gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0));

    v_normal = a_normal;
    v_texcoord0 = a_texcoord0;
}