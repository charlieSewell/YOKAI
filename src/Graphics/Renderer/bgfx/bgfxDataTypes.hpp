#pragma once
#include <bgfx/bgfx.h>
#include <bx/file.h>
#include <bimg/decode.h>
#include <bx/allocator.h>
#include <algorithm>
#include "Renderer/DataTypes.hpp"
#include <spdlog/spdlog.h>
struct bgfxVertex
{
    static void Init()
    {
        layout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Indices, 4, bgfx::AttribType::Int16)
            .add(bgfx::Attrib::Weight, 4, bgfx::AttribType::Float)
            .end();
    }
    static bgfx::VertexLayout layout;
};
struct PosColorTexCoord0Vertex
{
    glm::vec3 pos;
    uint32_t rgba;
    glm::vec2 texcood;
    static void init()
    {
        layout
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
            .end();
    }
    static bgfx::VertexLayout layout;
};
/**
 * @class bgfxTexture
 * @brief Holds a texture to be rendered by bgfx
 */
class bgfxTexture : public Texture
{
  public:
    /**
     * @brief Destructor for an bgfx Texture
     */
    ~bgfxTexture() override;
    /**
     * @brief Constructor for bgfxTexture
     * @param string - fileName
     */
    bgfxTexture(const std::string fileName);
    /**
     * @brief Binds the texture
     * @param size_t - slot
     */
    void Bind(size_t slot) override;
    /**
     * @brief Unbinds the texture
     */
    void UnBind(size_t slot) override;
    /**
     * @brief Returns the TextureID
     * @return int
     */
    uint16_t GetID() override;

  private:
    ///Texture ID
    bgfx::TextureHandle m_textureID = BGFX_INVALID_HANDLE;
};
/**
 * @class bfgxVertexBuffer
 * @brief Holds a Vertex Buffer to be used by bgfx
 */
class bgfxVertexBuffer : public VertexBuffer
{
    public:
    /**
     * @brief Destructor for bgfxVertexBuffer
     */
    ~bgfxVertexBuffer() override;
    /**
     * @brief Constructor for bgfxVertexBuffer
     * @param vector<Vertex> - vertices
     */
    bgfxVertexBuffer(std::vector<Vertex> &vertices);
    /**
     * @brief Binds the VertexBuffer
     */
    void Bind() override;
    /**
     * @brief Unbinds the VertexBuffer
     */
    void UnBind() override;

  private:
    ///Vertex Buffer ID
    bgfx::VertexBufferHandle m_vbo = BGFX_INVALID_HANDLE;
};
/**
 * @class bgfxIndexBuffer
 * @brief Holds a Index Buffer to be used by bgfx
 */
class bgfxIndexBuffer : public IndexBuffer
{
    public:
    /**
     * @brief Destructor for bgfxIndexBuffer
     */
    ~bgfxIndexBuffer() override;
    /**
     * @brief Constructor for bgfxIndexBuffer
     * @param indices<unsigned int> - indices
     */
    bgfxIndexBuffer(std::vector<unsigned int> &indices);
    /**
     * @brief Binds the IndexBuffer
     */
    void Bind() override;
    /**
     * @brief Unbinds the IndexBuffer
     */
    void UnBind() override;

  private:
    ///Index Buffer ID
    bgfx::IndexBufferHandle m_ibo = BGFX_INVALID_HANDLE;
};
class bgfxVertexArrayBuffer : public VertexArrayBuffer
{
  public:
    /**
     * @brief Destructor for bgfxVertexArrayBuffer
     */
    ~bgfxVertexArrayBuffer() override;
    /**
     * @brief Constructor for bgfxVertexArrayBuffer
     * @param vector<Vertex> - vertices
     * @param vector<unisigned int> - indices
     */
    bgfxVertexArrayBuffer(std::vector<Vertex>& vertices,std::vector<unsigned int>& indices);
    /**
     * @brief Binds the VertexArrayBuffer
     */
    void Bind() override;
    /**
     * @brief Unbinds the VertexArrayBuffer
     */
    void UnBind() override;

  private:
    ///Vertex Array Buffer ID
    unsigned int m_vaoID;
    ///Pointer to Vertex Buffer
    std::shared_ptr<bgfxVertexBuffer> m_vertexBuffer;
    ///Pointer to Index Buffer
    std::shared_ptr<bgfxIndexBuffer> m_indexBuffer;
};