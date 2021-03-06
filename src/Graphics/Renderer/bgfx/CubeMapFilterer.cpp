#include "CubeMapFilterer.hpp"
#include "bgfxutil.hpp"
#include <bx/math.h>
CubeMapFilterer::CubeMapFilterer()
{
    c_preFilteringProgram = loadProgram("cs_prefilter_env_map.bin", "");
    c_irradianceProgram = loadProgram("cs_irradiance.bin", "");
    u_sourceCubeMap = bgfx::createUniform("u_source", bgfx::UniformType::Sampler);
    u_params = bgfx::createUniform("u_params", bgfx::UniformType::Vec4);
}
FilteredCubeMap CubeMapFilterer::CreateFilteredCubeMap(uint16_t size, bgfx::ViewId view, bgfx::TextureHandle sourceCubeMap)
{
    uint64_t flags = BGFX_TEXTURE_COMPUTE_WRITE;
    bgfx::TextureHandle filteredCubeMap = bgfx::createTextureCube(size, true, 1, bgfx::TextureFormat::RGBA16F, flags);
    bgfx::TextureHandle irradianceMap = bgfx::createTextureCube(m_irradianceMapSize, false, 1, bgfx::TextureFormat::RGBA16F, flags);
    
    bgfx::setName(filteredCubeMap, "Prefilter Env Map");
    
    const uint16_t threadCount = 8u;
    bgfx::setViewName(view, "Env Map Filtering Pass");
    float maxMipLevel = bx::log2(float(size));
    for (float mipLevel = 0; mipLevel <= maxMipLevel; ++mipLevel)
    {
        uint16_t mipWidth = size / uint16_t(bx::pow(2.0f, mipLevel));
        float roughness = mipLevel / maxMipLevel;
        float params[] = { roughness, float(mipLevel), float(size), 0.0f };
        bgfx::setUniform(u_params, params);
        bgfx::setTexture(0, u_sourceCubeMap, sourceCubeMap);
        bgfx::setImage(1, filteredCubeMap, uint8_t(mipLevel), bgfx::Access::Write, bgfx::TextureFormat::RGBA16F);
        bgfx::dispatch(view, c_preFilteringProgram, mipWidth / threadCount, mipWidth / threadCount, 1);
    
    }
    bgfx::setTexture(0, u_sourceCubeMap, sourceCubeMap);
    bgfx::setImage(1, irradianceMap, 0, bgfx::Access::Write, bgfx::TextureFormat::RGBA16F);
    bgfx::dispatch(view, c_irradianceProgram, m_irradianceMapSize / threadCount, m_irradianceMapSize / threadCount, 1);

    return{sourceCubeMap,filteredCubeMap,irradianceMap};
}