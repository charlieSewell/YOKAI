
project(glew)

add_library(glew STATIC
	include/GL/glew.h
	include/GL/eglew.h
	include/GL/glxew.h
	include/GL/wglew.h
	src/glew.c
	src/glewinfo.c
	src/visualinfo.c
)

target_compile_options(glew PRIVATE -fPIC)

target_include_directories(glew PUBLIC include/)
