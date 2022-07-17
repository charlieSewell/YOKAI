#ifndef COMMON_SH_HEADER_GUARD
#define COMMON_SH_HEADER_GUARD

#include <bgfx_shader.sh>
#include <bgfx_compute.sh>
#include "shaderlib.sh"

#if BGFX_SHADER_LANGUAGE_SPIRV
    #undef BGFX_SHADER_LANGUAGE_HLSL
    #define BGFX_SHADER_LANGUAGE_HLSL 5
#endif

#endif // COMMON_SH_HEADER_GUARD