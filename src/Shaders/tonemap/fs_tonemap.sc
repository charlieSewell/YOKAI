#include "../common.sh"
#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);
SAMPLER2D(s_texAvgLum, 1);

uniform vec4 u_tonemap;

void main()
{
  vec2 texcoord = gl_FragCoord.xy / u_viewRect.zw;
  vec3 rgb = texture2D(s_texColor, texcoord).rgb;
  float lum = texture2D(s_texAvgLum, texcoord).r;

  vec3 Yxy = convertRGB2Yxy(rgb);

  float whiteSqr   = u_tonemap.x;

  Yxy.x /= (9.6 * lum + 0.0001);

  rgb = convertYxy2RGB(Yxy);
  
  rgb.x = Tonemap_Uchimura(rgb.x);
  rgb.y = Tonemap_Uchimura(rgb.y);
  rgb.z = Tonemap_Uchimura(rgb.z);
  gl_FragColor = toGammaAccurate(vec4(rgb, 1.0) );
}