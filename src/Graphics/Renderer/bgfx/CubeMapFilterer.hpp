#pragma once

#include<bgfx/bgfx.h>

struct FilteredCubeMap
{
    bgfx::TextureHandle sourceCubeMap = BGFX_INVALID_HANDLE;
    bgfx::TextureHandle filteredCubeMap = BGFX_INVALID_HANDLE;
    bgfx::TextureHandle irradianceMap = BGFX_INVALID_HANDLE;
};

class CubeMapFilterer
{
    public:
        CubeMapFilterer();
        FilteredCubeMap CreateFilteredCubeMap(uint16_t size, bgfx::ViewId view, bgfx::TextureHandle sourceCubeMap);

    private:
        bgfx::UniformHandle u_params = BGFX_INVALID_HANDLE;
        bgfx::UniformHandle u_sourceCubeMap = BGFX_INVALID_HANDLE;
        bgfx::ProgramHandle c_preFilteringProgram = BGFX_INVALID_HANDLE;
        bgfx::ProgramHandle c_irradianceProgram = BGFX_INVALID_HANDLE;
        
        uint16_t m_irradianceMapSize = 64u;

        bool m_destroyTextures = true;
};