#pragma once
#include <bgfx/bgfx.h>
#include <bx/allocator.h>
#include <iostream>
#include <fstream>
const bgfx::Memory* loadMemory( const char* filename );
bgfx::ShaderHandle loadShader( const char* shader );
bgfx::ProgramHandle loadProgram( const char* vsName, const char* fsName );

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