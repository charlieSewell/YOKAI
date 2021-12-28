project(render)

add_library(render STATIC
	DataTypes.cpp
    DataTypes.hpp
    DrawItem.hpp
    LightManager.cpp
    LightManager.hpp
    RenderAPI.cpp
    RenderAPI.hpp
    Renderer.cpp
    Renderer.hpp
    Window.cpp
    Window.hpp
    Mesh.hpp
    Mesh.cpp
    bgfx/bgfxDataTypes.hpp
    bgfx/bgfxDataTypes.cpp
    bgfx/bgfximgui.hpp
    bgfx/bgfxRenderer.cpp
    bgfx/bgfxRenderer.hpp
    bgfx/bgfxShader.hpp
    bgfx/bgfxShader.cpp
    bgfx/bgfxutil.cpp
    bgfx/bgfxutil.hpp
)

target_compile_options(render PRIVATE -fPIC)
target_link_libraries(render PRIVATE glfw glm bgfx bx bimg imgui spdlog)
target_include_directories(render PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)
