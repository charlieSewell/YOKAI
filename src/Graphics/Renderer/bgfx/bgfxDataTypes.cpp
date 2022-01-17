#include "bgfxDataTypes.hpp"

bgfx::VertexLayout bgfxVertex::layout;
bgfx::VertexLayout PosColorTexCoord0Vertex::layout;


bgfxTexture::bgfxTexture(const std::string fileName, const bool sRGB)
{
    m_textureID = LoadTexture(fileName, sRGB);
}

bgfxTexture::~bgfxTexture()
{
    if(bgfx::isValid(m_textureID))
    {
        bgfx::destroy(m_textureID);
        m_textureID = BGFX_INVALID_HANDLE;
    }
}

void bgfxTexture::Bind(size_t slot) 
{
    //DEPRECATED
}

void bgfxTexture::UnBind(size_t slot) 
{
    //DEPRECATED
}
uint16_t bgfxTexture::GetID()
{
    return m_textureID.idx;
}

bgfxVertexBuffer::bgfxVertexBuffer(std::vector<Vertex> &vertices)
{
    uint32_t stride = bgfxVertex::layout.getStride();
    const bgfx::Memory* vertexMem = bgfx::alloc(vertices.size() * stride);
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        unsigned int offset = i * stride;
        Vertex& vertex = *(Vertex*)(vertexMem->data + offset);
        vertex = vertices[i];
    }
    m_vbo = bgfx::createVertexBuffer(vertexMem, bgfxVertex::layout);
}
bgfxVertexBuffer::~bgfxVertexBuffer()
{
    if(bgfx::isValid(m_vbo))
    {
        bgfx::destroy(m_vbo);
        m_vbo = BGFX_INVALID_HANDLE;
    }
}
void bgfxVertexBuffer::Bind()
{
    bgfx::setVertexBuffer(0, m_vbo);
}
void bgfxVertexBuffer::UnBind()
{
    bgfx::setVertexBuffer(0, 0);
}

bgfxIndexBuffer::bgfxIndexBuffer(std::vector<uint16_t> &indices)
{
    const bgfx::Memory* iMem = bgfx::alloc(indices.size() * sizeof(uint16_t));
    uint16_t* indicesMem = (uint16_t*)iMem->data;
    for(unsigned int i = 0; i < indices.size(); i++)
    {
        indicesMem[i] = indices[i];
    }
    m_ibo = bgfx::createIndexBuffer(iMem);
}
bgfxIndexBuffer::~bgfxIndexBuffer()
{
    if(bgfx::isValid(m_ibo))
    {
        bgfx::destroy(m_ibo);
        m_ibo = BGFX_INVALID_HANDLE;
    }
}
void bgfxIndexBuffer::Bind()
{
    bgfx::setIndexBuffer(m_ibo);
}
void bgfxIndexBuffer::UnBind()
{
    bgfx::setIndexBuffer(0);
}

bgfxVertexArrayBuffer::~bgfxVertexArrayBuffer()
{

}
    
bgfxVertexArrayBuffer::bgfxVertexArrayBuffer(std::vector<Vertex>& vertices,std::vector<uint16_t>& indices)
{
    m_vertexBuffer = std::make_shared<bgfxVertexBuffer>(vertices);
    m_indexBuffer = std::make_shared<bgfxIndexBuffer>(indices);
}
    
void bgfxVertexArrayBuffer::Bind()
{
    m_vertexBuffer->Bind();
    m_indexBuffer->Bind();
}
    
void bgfxVertexArrayBuffer::UnBind()
{
    m_vertexBuffer->UnBind();
    m_indexBuffer->UnBind();
}