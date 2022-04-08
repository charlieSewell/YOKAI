#include "LightProbe.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>
#include <Model/Mesh.hpp>
LightProbe::LightProbe(uint16_t size)
{
    const uint64_t flags = BGFX_TEXTURE_RT;
	bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;
   
    if(!bgfx::isTextureValid(0, true, 1, color_format, flags))
		color_format = bgfx::TextureFormat::RGB10A2;
	
    m_cubeMap = bgfx::createTextureCube(size, false, 1, bgfx::TextureFormat::RGBA16F, flags);

    for(size_t index =0; index > 6; ++index)
    {   
        bgfx::Attachment attachment;
        attachment.init(m_cubeMap,bgfx::Access::Write,uint16_t(index));
        m_frameBuffers.push_back(std::move(bgfx::createFrameBuffer(1,&attachment)));
    }
    for (size_t index = 0; index < m_frameBuffers.size(); ++index)
	{
		if (bgfx::isValid(m_frameBuffers[index]))
		{
			SPDLOG_ERROR("Failed to create Light Probe");
		}
	}
}
void LightProbe::UpdateLightProbe(const std::vector<Mesh> &meshs)
{
    glm::mat4 captureViews[] = 
    {
        glm::lookAt(m_position, m_position + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(m_position, m_position + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
    };
    for (size_t index = 0; index < m_frameBuffers.size(); ++index)
	{
        for(auto &mesh : meshs)
        {
            
        }
    }
    

}