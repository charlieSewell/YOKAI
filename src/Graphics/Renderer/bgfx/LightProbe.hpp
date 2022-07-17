#pragma once
#include <bgfx/bgfx.h>
#include <vector>
#include <glm/glm.hpp>
#include <Renderer/DrawItem.hpp>
class LightProbe
{
    public:
        LightProbe();
        ~LightProbe();
        LightProbe(glm::vec3 position, uint16_t size);
        void UpdateLightProbe(const std::vector<RENDER::DrawItem> meshs);
        inline bgfx::TextureHandle GetCubeMap(){return m_cubeMap;}
    private:
        void SetupProbe();
        bgfx::TextureHandle m_cubeMap;
        std::vector<bgfx::FrameBufferHandle> m_frameBuffers;
        glm::vec3 m_position = {};
        uint16_t m_size = 0;
};