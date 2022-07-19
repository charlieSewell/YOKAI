#pragma once

#include <bgfx/bgfx.h>
#include <cstdint>
#include <map>
#include <string>
#include "Renderer/DataTypes.hpp"
class bgfxShader
{
    public:
        enum class Type
        {
            Vertex,
            Fragment,
            Compute,
        };

        bgfxShader() = delete;
        bgfxShader(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
        ~bgfxShader();

        bool SetTexture(const char* samplerName, uint8_t slot, std::shared_ptr<Texture> texture) const;
        bool SetUniform(const char* uniformName, const void* value, uint16_t numElements = 1) const;

        [[nodiscard]] bgfx::ProgramHandle GetRawHandle() const { return m_program; }

    private:
        void LoadUniforms(bgfx::ShaderHandle handle);
        bgfx::ProgramHandle m_program;
        std::map<std::string, bgfx::UniformHandle> m_uniforms;
};