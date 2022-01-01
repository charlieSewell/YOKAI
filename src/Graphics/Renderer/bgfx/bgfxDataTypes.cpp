#include "bgfxDataTypes.hpp"

bgfx::VertexLayout bgfxVertex::layout;
bgfx::VertexLayout PosColorTexCoord0Vertex::layout;
static bx::DefaultAllocator allocator;

bgfx::TextureHandle LoadTexture(const std::string fileName)
{
    void* data = nullptr;
    uint32_t size = 0;

    bx::FileReader reader;
    bx::Error err;
    if(bx::open(&reader, fileName.c_str(), &err))
    {
        size = (uint32_t)bx::getSize(&reader);
        data = BX_ALLOC(&allocator, size);
        bx::read(&reader, data, size, &err);
        bx::close(&reader);
    }

    if(!err.isOk())
    {
        BX_FREE(&allocator, data);
        SPDLOG_ERROR(err.getMessage().getPtr());
    }

    bimg::ImageContainer* image = bimg::imageParse(&allocator, data, size);
    if(image)
    {
        // the callback gets called when bgfx is done using the data (after 2 frames)
        const bgfx::Memory* mem = bgfx::makeRef(
            image->m_data,
            image->m_size,
            [](void*, void* data) { bimg::imageFree((bimg::ImageContainer*)data); },
            image);
        BX_FREE(&allocator, data);

        // default wrap mode is repeat, there's no flag for it
        uint64_t textureFlags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_MIN_ANISOTROPIC | BGFX_SAMPLER_MAG_ANISOTROPIC;
        /*
        if(sRGB)
            textureFlags |= BGFX_TEXTURE_SRGB;
        */
        if(bgfx::isTextureValid(0, false, image->m_numLayers, (bgfx::TextureFormat::Enum)image->m_format, textureFlags))
        {
            bgfx::TextureHandle tex = bgfx::createTexture2D((uint16_t)image->m_width,
                                                            (uint16_t)image->m_height,
                                                            image->m_numMips > 1,
                                                            image->m_numLayers,
                                                            (bgfx::TextureFormat::Enum)image->m_format,
                                                            textureFlags,
                                                            mem);
            //bgfx::setName(tex, file); // causes debug errors with DirectX SetPrivateProperty duplicate
            return tex;
        }
        else
            SPDLOG_ERROR("Unsupported format");
    }

    BX_FREE(&allocator, data);
    SPDLOG_ERROR(err.getMessage().getPtr());
    return BGFX_INVALID_HANDLE;
}

bgfxTexture::bgfxTexture(const std::string fileName)
{
    m_textureID = LoadTexture(fileName);
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