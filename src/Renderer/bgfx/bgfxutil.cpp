#include "bgfxutil.hpp"

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
	return bgfx::createShader(loadMemory( shader.c_str()));
}

bgfx::ProgramHandle loadProgram( std::string vsName, std::string fsName )
{
	bgfx::ShaderHandle vs;
	bgfx::ShaderHandle fs;
	switch(bgfx::getRendererType())
	{
		case bgfx::RendererType::OpenGL:
			vs = loadShader( "Shaders/glsl/"+ vsName );
			fs = loadShader( "Shaders/glsl/"+ fsName );
			break;
		case bgfx::RendererType::Direct3D11:
			vs = loadShader( "Shaders/dx11/"+ vsName );
			fs = loadShader( "Shaders/dx11/"+ fsName );
			break;
		case bgfx::RendererType::Vulkan:
			vs = loadShader( "Shaders/spirv/"+ vsName );
			fs = loadShader( "Shaders/spirv/"+ fsName );
			break;
		default:
			vs = loadShader( "Shaders/glsl/"+ vsName );
			fs = loadShader( "Shaders/glsl/"+ fsName );
			break;
	}
	return bgfx::createProgram( vs, fs, true );
}