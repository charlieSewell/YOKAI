#include "bgfxShader.hpp"
#include "bgfxutil.hpp"
#include <spdlog/spdlog.h>
bgfxShader::bgfxShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    bgfx::ShaderHandle vertexShader = loadShader(vertexShaderPath.c_str());
    bgfx::ShaderHandle fragmentShader = loadShader(fragmentShaderPath.c_str());
	LoadUniforms(vertexShader);
	LoadUniforms(fragmentShader);
	m_program = bgfx::createProgram(vertexShader, fragmentShader, true);
	if(!bgfx::isValid(m_program))
	{
		SPDLOG_ERROR("Shader {} Failed to load",name.c_str());
	}
	bgfx::setName(vertexShader, (name + "_vs").c_str());
	bgfx::setName(fragmentShader, (name + "_fs").c_str());
	bgfx::frame();
}
bgfxShader::~bgfxShader()
{
	if (bgfx::isValid(m_program))
	{
		bgfx::destroy(m_program);
	}
}
void bgfxShader::LoadUniforms(bgfx::ShaderHandle handle)
{
	std::vector<bgfx::UniformHandle> uniforms;
	bgfx::UniformInfo info = {};
	uint16_t numShaderUniforms = bgfx::getShaderUniforms(handle);
	uniforms.resize(numShaderUniforms);
	bgfx::getShaderUniforms(handle, uniforms.data(), numShaderUniforms);
	for (uint16_t i = 0; i < numShaderUniforms; ++i)
	{
		bgfx::getUniformInfo(uniforms[i], info);
		m_uniforms.emplace(std::string(info.name), uniforms[i]);
	}
}
bool bgfxShader::SetTexture(const char* samplerName, uint8_t bindPoint, std::shared_ptr<Texture> texture) const
{
	auto uniform = m_uniforms.find(samplerName);
	
	if (uniform != m_uniforms.cend() && texture != nullptr)
	{
		bgfx::TextureHandle handle;
		handle.idx =texture->GetID();
		bgfx::setTexture(bindPoint, uniform->second, handle);
		return true;
	}
	else
	{
		SPDLOG_WARN("Could not find texture sampler {}", samplerName);
		return false;
	}
}

bool bgfxShader::SetUniform(const char* uniformName, const void* value, uint16_t numElements) const
{
	auto uniform = m_uniforms.find(uniformName);
	if (uniform != m_uniforms.cend())
	{
		bgfx::setUniform(uniform->second, value, numElements);
		return true;
	}
	else
	{
		SPDLOG_WARN("Could not find uniform {}", uniformName);
		return false;
	}
}
