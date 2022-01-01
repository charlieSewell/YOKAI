#include "bgfxutil.hpp"
#include <spdlog/spdlog.h>
const bgfx::Memory* loadMemory( const char* filename )
{
	std::ifstream file( filename, std::ios::binary | std::ios::ate );
	std::streamsize size = file.tellg();
	file.seekg( 0, std::ios::beg );
	const bgfx::Memory* mem = bgfx::alloc( uint32_t( size + 1 ) );
	if ( file.read( ( char* )mem->data, size ) )
	{
		mem->data[ mem->size - 1 ] = '\0';
		return mem;
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
	/*
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
        vertex[0].texcood.x = minu;
        vertex[0].texcood.y = minv;
        vertex[1].pos.x = maxx;
        vertex[1].pos.y = miny;
        vertex[1].pos.z = zz;
        vertex[1].rgba = 0xffffffff;
        vertex[1].texcood.x = maxu;
        vertex[1].texcood.y = minv;
        vertex[2].pos.x = maxx;
        vertex[2].pos.y = maxy;
        vertex[2].pos.z = zz;
        vertex[2].rgba = 0xffffffff;
        vertex[2].texcood.x = maxu;
        vertex[2].texcood.y = maxv;
        bgfx::setVertexBuffer(0, &vb);
    }
	*/
}