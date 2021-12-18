$input v_texcoord0

#include "common.sh"
uniform vec4 u_color;
SAMPLER2D(s_texColor, 0);

void main()
{
	vec4 color = toLinear(texture2D(s_texColor, v_texcoord0) );

	if (color.x < 0.1)
	{
		discard;
	}

	gl_FragColor = color;
}