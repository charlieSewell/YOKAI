function(target_ignore_header_warnings target scope)
    get_target_property(lib_include_dirs ${target} INTERFACE_INCLUDE_DIRECTORIES)
    target_include_directories(${target} SYSTEM ${scope} ${lib_include_dirs})
endfunction()

# Library build options.
option(ASSIMP_BUILD_TESTS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(OPTION_BUILD_TESTS OFF)

# Build libraries.
string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Disable compiler warnings.
add_compile_options(
    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wno-everything>
    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-w>
    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W0>
)
option( BGFX_BUILD_EXAMPLES OFF)
add_subdirectory(bgfx.cmake)
add_subdirectory(glm)
add_subdirectory(assimp)
add_subdirectory(imgui)
add_subdirectory(reactphysics3d)
add_subdirectory(ImGuizmo)
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_TESTS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
add_subdirectory(glfw)
add_subdirectory(spdlog)

add_definitions(-DBGFX_CONFIG_RENDERER_OPENGL_MIN_VERSION=43)
add_definitions(-DIMGUI_DISABLE_OBSOLETE_FUNCTIONS)

set(BGFX_LIBRARY_TYPE "STATIC")
set_target_properties(reactphysics3d PROPERTIES ENABLE_EXPORTS ON)
set_target_properties(reactphysics3d PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
# Puts a stop to the endlessly irritating practise postfixing 'd' onto debug libraries.
set_target_properties(assimp PROPERTIES DEBUG_POSTFIX "")
set_target_properties(glfw PROPERTIES DEBUG_POSTFIX "")
set_target_properties(reactphysics3d PROPERTIES DEBUG_POSTFIX "")

# Ignore warnings from library headers.
target_ignore_header_warnings(assimp INTERFACE)
target_ignore_header_warnings(reactphysics3d INTERFACE)
target_ignore_header_warnings(glm INTERFACE)
target_ignore_header_warnings(glfw INTERFACE)
target_ignore_header_warnings(imgui INTERFACE)
target_ignore_header_warnings(imguizmo INTERFACE)
target_ignore_header_warnings(bimg INTERFACE)
target_ignore_header_warnings(spdlog INTERFACE)
target_ignore_header_warnings(bgfx INTERFACE)
target_ignore_header_warnings(bx INTERFACE)
target_ignore_header_warnings(bimg INTERFACE)
#Need Alloca for msvc
