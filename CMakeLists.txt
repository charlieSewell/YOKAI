enable_testing()
# Set cmake minimum version.
cmake_minimum_required(VERSION 3.22)

# Submodule update
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif(APPLE)
# Set the project details.
set(PROJECT_NAME YOKAI)
project(${PROJECT_NAME} LANGUAGES C CXX)

# If enabled, the post build symlink will copy instead.
option(CopyResources "CopyResources" ON)

# Clang sanitizer settings.
set(SANITIZER_OS "Darwin,Linux")
set(SANITIZER_FLAGS "-fsanitize=address,undefined,leak")

# Treat warnings as errors.
option(WarningsAsErrors "WarningsAsErrors" OFF)

# Disable in-source builds.
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

# Disable debug library postfix.
set(CMAKE_DEBUG_POSTFIX "")

# Set build type to debug by default.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add Linux flag.
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Set build output directories.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Define source files.
add_subdirectory(src)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${SHADERS})

# Build 3rd Party Libraries
add_subdirectory(lib)

# Include Tests
add_subdirectory(tests)

# Set C++ standard.
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )

# Remove the default warning level from MSVC.
if (MSVC)
    string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()

# Treat warnings as errors if enabled.
if (WarningsAsErrors)
    target_compile_options(${PROJECT_NAME} PUBLIC
            $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Werror>
            $<$<CXX_COMPILER_ID:MSVC>:/WX>
            )
endif()
# Set compile flags.
target_compile_options(${PROJECT_NAME} PRIVATE
    # Clang
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
    -Weverything -fcolor-diagnostics
    # Disable specific warnings.
    -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
    -Wno-deprecated-declarations -Wno-exit-time-destructors
    -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors -fPIC>
    # GCC
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always -fPIC>
    # Visual Studio
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /external:anglebrackets /external:W0>
    # Enable the clang sanitizer.
    $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
)
# Link against the clang sanitizer.
target_link_options(${PROJECT_NAME} PUBLIC
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )
# Include and link against dependencies.
target_link_libraries(${PROJECT_NAME} PUBLIC core graphics physics ${CMAKE_DL_LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)

set(SHADER_DIR ${CMAKE_BINARY_DIR}/shaders)
# target to force all shaders to recompile on the next build
# sometimes handy after changing included header files (.sh)
# since add_shader doesn't take those dependencies into account
add_custom_target(invalidate_shaders)

foreach(SHADER ${SHADERS})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    get_filename_component(SHADER_FILE ${SHADER} ABSOLUTE)
    # add_shader defaults to GLSL 120, 430 for compute
    # GLSL 1.30 is needed for switch statements but shaderc produces shader
    # binaries without any #version directive unless we request 4.00 or higher
    # this makes shader compilation fail with no error message
    # just use 4.30 for all shaders
    # default DX11 model is 5_0
    set(GLSL_VERSION 430)
    set(GLSL_COMPUTE_VERSION 430)
    set(DX_MODEL 5_0)

    # DX9/11 shaders can only be compiled on Windows
    set(SHADER_PLATFORMS glsl spirv)
    if(WIN32)
        set(SHADER_PLATFORMS ${SHADER_PLATFORMS} dx11)
    endif()

    if(SHADER_NAME MATCHES "^vs_")
        add_shader(${SHADER_FILE} VERTEX
            OUTPUT ${SHADER_DIR}
            GLSL_VERSION ${GLSL_VERSION}
            DX11_MODEL ${DX_MODEL}
            PLATFORMS ${SHADER_PLATFORMS})
    elseif(SHADER_NAME MATCHES "^fs_")
        add_shader(${SHADER_FILE} FRAGMENT
            OUTPUT ${SHADER_DIR}
            GLSL_VERSION ${GLSL_VERSION}
            DX11_MODEL ${DX_MODEL}
            PLATFORMS ${SHADER_PLATFORMS})
    elseif(SHADER_NAME MATCHES "^cs_")
        add_shader(${SHADER_FILE} COMPUTE
            OUTPUT ${SHADER_DIR}
            GLSL_VERSION ${GLSL_COMPUTE_VERSION}
            DX11_MODEL ${DX_MODEL}
            PLATFORMS ${SHADER_PLATFORMS})
    endif()
    add_custom_command(TARGET invalidate_shaders PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E touch ${SHADER_FILE})
endforeach()

# add_shader does this, do it manually for includes/varying.def.sc
source_group("Shader Files" FILES ${SHADERS})
install(DIRECTORY ${SHADER_DIR} DESTINATION build)