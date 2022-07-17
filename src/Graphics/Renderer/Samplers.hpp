#pragma once

#include <cstdint>

namespace Samplers
{
    constexpr uint8_t PBR_ALBEDO_LUT = 0;

    constexpr uint8_t PBR_BASECOLOR = 1;
    constexpr uint8_t PBR_METALROUGHNESS = 2;
    constexpr uint8_t PBR_NORMAL = 3;
    constexpr uint8_t PBR_OCCLUSION = 4;
    constexpr uint8_t PBR_EMISSIVE = 5;
    
    constexpr uint8_t LIGHTS_POINTLIGHTS = 6;

    constexpr uint8_t PBR_PREFILTER_ENV_MAP = 7;
    constexpr uint8_t PBR_IRRADIANCE_MAP = 8; 
}