#include "bgfxutil.hpp"
#include <spdlog/spdlog.h>
namespace
{
    static bx::DefaultAllocator allocator;
}
const bgfx::Memory* loadMemory( const char* filename )
{
    std::ifstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try
    {
        file.open(filename, std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        SPDLOG_INFO(file.tellg());
	    file.seekg( 0, std::ios::beg );
	    const bgfx::Memory* mem = bgfx::alloc( uint32_t( size + 1 ) );
	    if ( file.read( ( char* )mem->data, size ) )
	    {
		    mem->data[ mem->size - 1 ] = '\0';
		    return mem;
	    }
	    return nullptr;
    }catch(std::ifstream::failure e)
    {
        SPDLOG_ERROR(e.what());
        return nullptr;
    }
	
	return nullptr;
}

bgfx::ShaderHandle loadShader( std::string shader )
{
	switch(bgfx::getRendererType())
	{
		case bgfx::RendererType::OpenGL:
			return bgfx::createShader(loadMemory(("shaders/glsl/" + shader).c_str()));
		case bgfx::RendererType::Direct3D11:
			return bgfx::createShader(loadMemory(("shaders/dx11/" + shader).c_str()));
		case bgfx::RendererType::Direct3D12:
			return bgfx::createShader(loadMemory(("shaders/dx11/" + shader).c_str()));
		case bgfx::RendererType::Vulkan:
			return bgfx::createShader(loadMemory(("shaders/spirv/" + shader).c_str()));
		default:
			return BGFX_INVALID_HANDLE;
	}
	return BGFX_INVALID_HANDLE;
}

bgfx::ProgramHandle loadProgram( std::string vsName, std::string fsName )
{
	bgfx::ProgramHandle program;
	if(!fsName.empty())
	{
		bgfx::ShaderHandle vs;
		bgfx::ShaderHandle fs;
		vs = loadShader(vsName);
		fs = loadShader(fsName);
		program = bgfx::createProgram( vs, fs, true );
	}
	else
	{
		bgfx::ShaderHandle cs;
		cs = loadShader(vsName);
        
		program = bgfx::createProgram( cs, true );
	}
	
	if(!bgfx::isValid(program))
	{
		SPDLOG_ERROR("Shader Failed to load");
	}
	SPDLOG_INFO("Loaded Shader {} {}",vsName,fsName);
	return program;
}

bgfx::TextureFormat::Enum findDepthFormat(uint64_t textureFlags, bool stencil)
{
    const bgfx::TextureFormat::Enum depthFormats[] = { bgfx::TextureFormat::D16, bgfx::TextureFormat::D32 };

    const bgfx::TextureFormat::Enum depthStencilFormats[] = { bgfx::TextureFormat::D24S8 };

    const bgfx::TextureFormat::Enum* formats = stencil ? depthStencilFormats : depthFormats;
    size_t count = stencil ? BX_COUNTOF(depthStencilFormats) : BX_COUNTOF(depthFormats);

    bgfx::TextureFormat::Enum depthFormat = bgfx::TextureFormat::Count;
    for(size_t i = 0; i < count; i++)
    {
        if(bgfx::isTextureValid(0, false, 1, formats[i], textureFlags))
        {
            depthFormat = formats[i];
            break;
        }
    }

    assert(depthFormat != bgfx::TextureFormat::Enum::Count);

    return depthFormat;
}


    

void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft, float _width, float _height)
{
	
    if (3 == bgfx::getAvailTransientVertexBuffer(3, PosColorTexCoord0Vertex::layout))
    {
		float s_texelHalf = 0.0f;
        bgfx::TransientVertexBuffer vb;
        bgfx::allocTransientVertexBuffer(&vb, 3, PosColorTexCoord0Vertex::layout);
        PosColorTexCoord0Vertex* vertex = (PosColorTexCoord0Vertex*)vb.data;
        const float zz = 0.0f;
        const float minx = -_width;
        const float maxx = _width;
        const float miny = 0.0f;
        const float maxy = _height * 2.0f;
        const float texelHalfW = s_texelHalf / _textureWidth;
        const float texelHalfH = s_texelHalf / _textureHeight;
        const float minu = -1.0f + texelHalfW;
        const float maxu = 1.0f + texelHalfW;
        float minv = texelHalfH;
        float maxv = 2.0f + texelHalfH;
        if (_originBottomLeft)
        {
            float temp = minv;
            minv = maxv;
            maxv = temp;
            minv -= 1.0f;
            maxv -= 1.0f;
        }
        vertex[0].pos.x = minx;
        vertex[0].pos.y = miny;
        vertex[0].pos.z = zz;
        vertex[0].rgba = 0xffffffff;
        vertex[0].texcoord.x = minu;
        vertex[0].texcoord.y = minv;
        vertex[1].pos.x = maxx;
        vertex[1].pos.y = miny;
        vertex[1].pos.z = zz;
        vertex[1].rgba = 0xffffffff;
        vertex[1].texcoord.x = maxu;
        vertex[1].texcoord.y = minv;
        vertex[2].pos.x = maxx;
        vertex[2].pos.y = maxy;
        vertex[2].pos.z = zz;
        vertex[2].rgba = 0xffffffff;
        vertex[2].texcoord.x = maxu;
        vertex[2].texcoord.y = maxv;
        bgfx::setVertexBuffer(0, &vb);
    }
}

bgfx::TextureHandle LoadTexture(const std::string fileName, const bool sRGB)
{
    bgfx::TextureHandle tex;
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
        SPDLOG_ERROR("{}: {}",err.getMessage().getPtr(),fileName);
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
        uint64_t textureFlags = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE;
        
        if(sRGB)
            textureFlags |= BGFX_TEXTURE_SRGB;
        if (image->m_cubeMap)
		{
			tex = bgfx::createTextureCube(
					uint16_t(image->m_width)
					, 1 < image->m_numMips
					, image->m_numLayers
					, bgfx::TextureFormat::Enum(image->m_format)
					, textureFlags
					, mem
					);
            return tex; 
		}
		else if (1 < image->m_depth)
		{
			tex = bgfx::createTexture3D(
				  uint16_t(image->m_width)
				, uint16_t(image->m_height)
				, uint16_t(image->m_depth)
				, 1 < image->m_numMips
				, bgfx::TextureFormat::Enum(image->m_format)
				, textureFlags
				, mem
				);
            return tex;
	    }
        else if(bgfx::isTextureValid(0, false, image->m_numLayers, (bgfx::TextureFormat::Enum)image->m_format, textureFlags))
        {
            tex = bgfx::createTexture2D((uint16_t)image->m_width,
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
