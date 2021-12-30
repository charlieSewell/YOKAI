project(graphics)


add_library(graphics STATIC
	  Renderer/DataTypes.cpp
    Renderer/DataTypes.hpp
    Renderer/DrawItem.hpp
    Renderer/RenderAPI.cpp
    Renderer/RenderAPI.hpp
    Renderer/Renderer.cpp
    Renderer/Renderer.hpp
    Renderer/Window.cpp
    Renderer/Window.hpp
    Renderer/Mesh.hpp
    Renderer/Mesh.cpp
    Renderer/bgfx/bgfxDataTypes.hpp
    Renderer/bgfx/bgfxDataTypes.cpp
    Renderer/bgfx/bgfximgui.hpp
    Renderer/bgfx/bgfximgui.cpp
    Renderer/bgfx/bgfxRenderer.cpp
    Renderer/bgfx/bgfxRenderer.hpp
    Renderer/bgfx/bgfxShader.hpp
    Renderer/bgfx/bgfxShader.cpp
    Renderer/bgfx/bgfxutil.cpp
    Renderer/bgfx/bgfxutil.hpp
    Renderer/TextureManager.hpp
    Renderer/TextureManager.cpp

    Model/ObjectLoading/ModelLoader.hpp
    Model/ObjectLoading/ModelLoader.cpp
    Model/Animator.hpp
    Model/Animator.cpp
    Model/Model.hpp
    Model/Model.cpp
    Model/ModelManager.hpp
    Model/ModelManager.cpp
    Model/SkeletalAnimation.hpp
    Model/SkeletalAnimation.cpp


    Renderer/bgfx/fs_ocornut_imgui.bin.h
    Renderer/bgfx/vs_ocornut_imgui.bin.h
    Renderer/imgui_impl_glfw.h
    Renderer/imgui_impl_glfw.cpp
)

set_target_properties(graphics PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )

target_compile_options(graphics PRIVATE -fPIC)
target_link_libraries(graphics PRIVATE bgfx bx bimg core )
target_link_libraries(graphics PUBLIC assimp)
target_include_directories(graphics PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)
