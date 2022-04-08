#pragma once
#include <bgfx/bgfx.h>
#include <vector>
#include <glm/glm.hpp>

class LightProbe
{
    public:
        LightProbe(uint16_t size);
        void UpdateLightProbe(const std::vector<Mesh> &meshs);
    private:
        bgfx::TextureHandle m_cubeMap;
        std::vector<bgfx::FrameBufferHandle> m_frameBuffers;
        glm::vec3 m_position;
};