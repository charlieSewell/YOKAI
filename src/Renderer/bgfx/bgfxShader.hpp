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

        void SetTexture(const char* samplerName, uint8_t slot, Texture& texture) const;
        void SetUniform(const char* uniformName, const void* value) const;

        [[nodiscard]] bgfx::ProgramHandle GetRawHandle() const { return m_program; }

    private:
        bgfx::ProgramHandle m_program;
        std::map<std::string, bgfx::UniformHandle> m_uniforms;
};