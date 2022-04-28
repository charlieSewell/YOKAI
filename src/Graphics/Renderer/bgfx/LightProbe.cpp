#include "LightProbe.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>
#include <Model/Mesh.hpp>
#include <bx/math.h>
#include "Renderer/Renderer.hpp"
#include "bgfxShader.hpp"
namespace
{
    std::shared_ptr<bgfxShader> PROGRAM;
}

LightProbe::LightProbe():
    m_size(1024),
    m_position({0,0,0})
{
    SetupProbe();
}

LightProbe::LightProbe(glm::vec3 position, uint16_t size):
    m_size(size),
    m_position(position)
{
    SetupProbe();
}
LightProbe::~LightProbe()
{
    bgfx::destroy(m_cubeMap);
    for(auto& frameBuffer: m_frameBuffers)
    {
        bgfx::destroy(frameBuffer);
    }
}
void LightProbe::SetupProbe()
{
    if(PROGRAM == nullptr)
    {
        PROGRAM = std::make_shared<bgfxShader>("Light Probe Shader","vs_pbrshader.bin","fs_pbrshader.bin");
    }
    const uint64_t flags = BGFX_TEXTURE_RT;
	bgfx::TextureFormat::Enum color_format = bgfx::TextureFormat::RGBA16F;
   
    if(!bgfx::isTextureValid(0, true, 1, color_format, flags))
    {
        SPDLOG_ERROR("Texture format for lightProbe is incorrect");
        color_format = bgfx::TextureFormat::RGBA16F;
    }
		
	
    m_cubeMap = bgfx::createTextureCube(m_size, false, 1, bgfx::TextureFormat::RGBA16F, flags);

    for(size_t index =0; index < 6; ++index)
    {   
        bgfx::Attachment attachment[2];
        attachment[0].init(m_cubeMap,bgfx::Access::Write,uint16_t(index));
        bgfx::TextureHandle depthBuffer = bgfx::createTexture2D(
            m_size, m_size,
            false,
            1,
            bgfx::TextureFormat::D24S8,
            BGFX_TEXTURE_RT);
        attachment[1].init(depthBuffer,bgfx::Access::Write,0,1);

        m_frameBuffers.push_back(bgfx::createFrameBuffer(2,attachment));
    }
    for (size_t index = 0; index < m_frameBuffers.size(); ++index)
	{
		if (!bgfx::isValid(m_frameBuffers[index]))
		{
			SPDLOG_ERROR("Failed to create Light Probe");
		}
	}
}
void LightProbe::UpdateLightProbe(const std::vector<RENDER::DrawItem> meshs)
{
    uint64_t state = BGFX_STATE_DEFAULT;
    glm::mat4 projMat = {};
    bx::mtxProj(glm::value_ptr(projMat),
                90.0f,
                1.0f,
                0.1f,
                300.0f,
                bgfx::getCaps()->homogeneousDepth,bx::Handness::Right);
    glm::mat4 captureViews[] = 
    {
        glm::lookAt(m_position, m_position + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  1.0f,  0.0f)),
        glm::lookAt(m_position, m_position + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f,  1.0f,  0.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f,  1.0f,  0.0f)),
        glm::lookAt(m_position, m_position + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f,  1.0f,  0.0f))
    };
    for (size_t index = 0; index < m_frameBuffers.size(); ++index)
	{
        bgfx::ViewId viewID = uint16_t(30+index);
        //30+ index is temporry view ID please change at some point
        bgfx::setViewClear(viewID, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH | BGFX_CLEAR_STENCIL, 0x303030FF, 1.0f, 0);
        bgfx::setViewRect(viewID, 0, 0, m_size, m_size);
        
        //bgfx::touch(viewID);
        bgfx::setViewTransform(viewID, glm::value_ptr(captureViews[index]), glm::value_ptr(projMat));
        bgfx::setViewFrameBuffer(viewID, m_frameBuffers[index]);
        for(auto &mesh : meshs)
        {
            RENDER::DrawItem drawItem;
            drawItem.mesh = mesh.mesh;
            drawItem.transform = mesh.transform;
            drawItem.state = state;
            drawItem.shader = PROGRAM;
            drawItem.viewID = viewID;
            drawItem.camPos = m_position;

            Renderer::getInstance().AddToDraw(drawItem);
        }
    }
    

}