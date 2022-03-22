#pragma once
#include <bgfx/bgfx.h>
#include <vector>
#include <glm/glm.hpp>

class LightProbe
{
    public:
        LightProbe(uint16_t size);
        void UpdateLightProbe(glm::mat4 projMatrix);
    private:
        bgfx::TextureHandle m_cubeMap;
        std::vector<bgfx::FrameBufferHandle> m_frameBuffers;
        glm::vec3 m_position;
};