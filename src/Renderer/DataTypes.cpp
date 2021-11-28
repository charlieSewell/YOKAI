//
// Created by Charlie Sewell on 9/03/2021.
//
#include "DataTypes.hpp"
#include <utility>
#include "Renderer/OpenGL/OpenGLDataTypes.hpp"

std::shared_ptr<VertexBuffer> VertexBuffer::Create(std::vector<Vertex> &vertices)
{
    return std::make_shared<OpenGLVertexBuffer>(vertices);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(std::vector<unsigned int> &indices)
{
    return std::make_shared<OpenGLIndexBuffer>(indices);
}

std::shared_ptr<VertexArrayBuffer> VertexArrayBuffer::Create(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    return std::make_shared<OpenGLVertexArrayBuffer>(vertices,indices);
}

std::shared_ptr<Texture> Texture::Create(const std::string fileName)
{
    return std::make_shared<OpenGLTexture>(fileName);
}
