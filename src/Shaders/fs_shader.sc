$input v_texcoord0, v_normal

#include "common.sh"
uniform vec4 u_color;

SAMPLER2D(texture_diffuse1, 0);
SAMPLER2D(texture_normal1, 1);
void main()
{
	vec4 color = toLinear(texture2D(texture_diffuse1, v_texcoord0) );

	gl_FragColor = color;
}