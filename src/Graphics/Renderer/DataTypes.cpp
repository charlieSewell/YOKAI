//
// Created by Charlie Sewell on 9/03/2021.
//
#include "DataTypes.hpp"
#include <utility>
#include "bgfx/bgfxDataTypes.hpp"

std::shared_ptr<VertexBuffer> VertexBuffer::Create(std::vector<Vertex> &vertices)
{
    return std::make_shared<bgfxVertexBuffer>(vertices);
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(std::vector<uint16_t> &indices)
{
    return std::make_shared<bgfxIndexBuffer>(indices);
}

std::shared_ptr<VertexArrayBuffer> VertexArrayBuffer::Create(std::vector<Vertex>& vertices, std::vector<uint16_t>& indices)
{
    return std::make_shared<bgfxVertexArrayBuffer>(vertices,indices);
}

std::shared_ptr<Texture> Texture::Create(const std::string fileName)
{
    return std::make_shared<bgfxTexture>(fileName);
}
