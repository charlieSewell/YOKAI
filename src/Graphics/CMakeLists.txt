project(graphics)

set(SUPPRESS
        Model/ObjectLoading/mikktspace.h
        Model/ObjectLoading/mikktspace.c
)
set(SOURCE
        Renderer/DataTypes.cpp
        Renderer/DataTypes.hpp
        Renderer/DrawItem.hpp
        Renderer/LightingTypes.hpp
        Renderer/PointLight.hpp
        Renderer/LightManager.cpp
        Renderer/LightManager.hpp
        Renderer/RenderAPI.cpp
        Renderer/RenderAPI.hpp
        Renderer/Renderer.cpp
        Renderer/Renderer.hpp
        Renderer/Window.cpp
        Renderer/Window.hpp
        Renderer/bgfx/LightBuffer.hpp
        Renderer/bgfx/LightBuffer.cpp
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
        Renderer/bgfx/CubeMapFilterer.hpp
        Renderer/bgfx/CubeMapFilterer.cpp
        Renderer/bgfx/LightProbe.hpp
        Renderer/bgfx/LightProbe.cpp
        Renderer/TextureManager.hpp
        Renderer/TextureManager.cpp
        Renderer/Samplers.hpp
        Renderer/imgui_impl_glfw.h
        Renderer/imgui_impl_glfw.cpp

        Model/ObjectLoading/ModelLoader.hpp
        Model/ObjectLoading/ModelLoader.cpp
        Model/ObjectLoading/CalcTangent.hpp
        Model/ObjectLoading/CalcTangent.cpp
        Model/Animator.hpp
        Model/Animator.cpp
        Model/Mesh.hpp
        Model/Mesh.cpp
        Model/Model.hpp
        Model/Model.cpp
        Model/Material.hpp
        Model/ModelManager.hpp
        Model/ModelManager.cpp
        Model/SkeletalAnimation.hpp
        Model/SkeletalAnimation.cpp

        Renderer/bgfx/fs_ocornut_imgui.bin.h
        Renderer/bgfx/vs_ocornut_imgui.bin.h
)
add_library(graphics STATIC ${SOURCE} ${SUPPRESS} ${SHADERS})


set_target_properties(graphics PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
target_compile_options(graphics PRIVATE
        # Clang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # Disable specific warnings.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors
        -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors -fPIC>
        # GCC
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
        # Visual Studio
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /external:anglebrackets /external:W0>
        # Enable the clang sanitizer.
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )

target_link_libraries(graphics PRIVATE bgfx bx bimg core)
target_link_libraries(graphics PUBLIC assimp)
target_include_directories(graphics PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)

