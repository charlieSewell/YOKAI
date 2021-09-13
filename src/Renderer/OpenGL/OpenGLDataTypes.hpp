//
// Created by Charlie Sewell on 9/03/2021.
//
#pragma once

#include <glad/glad.h>
#include "Renderer/DataTypes.hpp"
#include <memory>
/**
 * @class OpenGLTexture
 * @brief Holds a texture to be rendered by OpenGL
 */
class OpenGLTexture : public Texture
{
  public:
    /**
     * @brief Destructor for an OpenGL Texture
     */
    ~OpenGLTexture() override;
    /**
     * @brief Constructor for OpenGLTexture
     * @param string - fileName
     */
    OpenGLTexture(const std::string& fileName);
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
    int getID() override;

  private:
    ///Texture ID
    unsigned int textureID;
};
/**
 * @class OpenGLVertexBuffer
 * @brief Holds a Vertex Buffer to be used by OpenGL
 */
class OpenGLVertexBuffer : public VertexBuffer
{
  public:
    /**
     * @brief Destructor for OpenGLVertexBuffer
     */
    ~OpenGLVertexBuffer() override;
    /**
     * @brief Constructor for OpenGLVertexBuffer
     * @param vector<Vertex> - vertices
     */
    OpenGLVertexBuffer(std::vector<Vertex> &vertices);
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
    unsigned int vboID;
};
/**
 * @class OpenGLIndexBuffer
 * @brief Holds an Index Buffer to be used by OpenGL
 */
class OpenGLIndexBuffer : public IndexBuffer
{
  public:
    /**
     * @brief Destructor for OpenGLIndexBuffer
     */
    ~OpenGLIndexBuffer() override;
    /**
     * @brief Constructor for OpenGLIndexBuffer
     * @param vector<unsigned int> - indices
     */
    OpenGLIndexBuffer(std::vector<unsigned int> &indices);
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
    unsigned int ibID;
};
/**
 * @class OpenGLVertexArrayBuffer
 * @brief Holds a Vertex Array Buffer to be used by OpenGL
 */
class OpenGLVertexArrayBuffer : public VertexArrayBuffer
{
  public:
    /**
     * @brief Destructor for OpenGLVertexArrayBuffer
     */
    ~OpenGLVertexArrayBuffer() override;
    /**
     * @brief Constructor for OpenGLVertexArrayBuffer
     * @param vector<Vertex> - vertices
     * @param vector<unisigned int> - indices
     */
    OpenGLVertexArrayBuffer(std::vector<Vertex>& vertices,std::vector<unsigned int>& indices);
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
    unsigned int vaoID;
    ///Pointer to Vertex Buffer
    std::shared_ptr<OpenGLVertexBuffer> vertexBuffer;
    ///Pointer to Index Buffer
    std::shared_ptr<OpenGLIndexBuffer> indexBuffer;
};
