#include "bgfxShader.hpp"
#include "bgfxutil.hpp"
#include <spdlog/spdlog.h>
bgfxShader::bgfxShader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
    uint16_t numShaderUniforms = 0;
	bgfx::UniformInfo info = {};
	std::vector<bgfx::UniformHandle> uniforms;
    bgfx::ShaderHandle vertexShader = loadShader(vertexShaderPath.c_str());
    bgfx::ShaderHandle fragmentShader = loadShader(fragmentShaderPath.c_str());
	numShaderUniforms = bgfx::getShaderUniforms(vertexShader);
	uniforms.resize(numShaderUniforms);
	bgfx::getShaderUniforms(vertexShader, uniforms.data(), numShaderUniforms);
	for (uint16_t i = 0; i < numShaderUniforms; ++i)
	{
		bgfx::getUniformInfo(uniforms[i], info);
		m_uniforms.emplace(std::string(info.name), uniforms[i]);
	}

	numShaderUniforms = bgfx::getShaderUniforms(fragmentShader);
	uniforms.resize(numShaderUniforms);
	bgfx::getShaderUniforms(fragmentShader, uniforms.data(), numShaderUniforms);
	for (uint16_t i = 0; i < numShaderUniforms; ++i)
	{
		bgfx::getUniformInfo(uniforms[i], info);
		m_uniforms.emplace(std::string(info.name), uniforms[i]);
	}

	m_program = bgfx::createProgram(vertexShader, fragmentShader, true);
	
	if(!bgfx::isValid(m_program))
	{
		throw new std::exception("OOPPSSS");
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

void bgfxShader::SetTexture(const char* samplerName, uint8_t bindPoint, std::shared_ptr<Texture> texture) const
{
	auto uniform = m_uniforms.find(samplerName);
	bgfx::TextureHandle handle;
	handle.idx =texture->GetID();
	if (uniform != m_uniforms.cend())
	{
		bgfx::setTexture(bindPoint, uniform->second, handle);
	}
	else
	{
		//SPDLOG_WARN("Could not find texture sampler {}", samplerName);
	}
}

void bgfxShader::SetUniform(const char* uniformName, const void* value) const
{
	auto uniform = m_uniforms.find(uniformName);
	if (uniform != m_uniforms.cend())
	{
		bgfx::setUniform(uniform->second, value);
	}
	else
	{
		SPDLOG_WARN("Could not find uniform {}", uniformName);
	}
}
