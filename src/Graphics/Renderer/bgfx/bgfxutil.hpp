#pragma once
#pragma warning (disable : 4100)
#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <iostream>
#include <fstream>
#include "bgfxDataTypes.hpp"
const bgfx::Memory* loadMemory( const char* filename );
bgfx::ShaderHandle loadShader( std::string vsName );
bgfx::ProgramHandle loadProgram( std::string vsName, std::string fsName );
void screenSpaceQuad(float _textureWidth, float _textureHeight, bool _originBottomLeft = false, float _width= 1.0f , float _height= 1.0f );
bgfx::TextureFormat::Enum findDepthFormat(uint64_t textureFlags, bool stencil);
// allocator
class Allocator : public bx::AllocatorI
{
    public:
		void* realloc( void* _ptr, size_t _size, size_t _align, const char* _file, uint32_t _line )
		{
			if ( _size == 0 )
			{
				free( _ptr );
				return nullptr;
			}
			else
			{
				return malloc( _size );
			}
		}
	
};