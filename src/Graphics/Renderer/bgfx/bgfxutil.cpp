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
	bgfx::ShaderHandle vs;
	bgfx::ShaderHandle fs;
	vs = loadShader(vsName);
	fs = loadShader(fsName);
	bgfx::ProgramHandle program = bgfx::createProgram( vs, fs, true );
	if(!bgfx::isValid(program))
	{
		SPDLOG_ERROR("Shader Failed to load");
	}
	SPDLOG_INFO("Loaded Shader {} {}",vsName,fsName);
	return program;
}