# Set cmake minimum version.
cmake_minimum_required(VERSION 3.16)
if(APPLE)
    set(CMAKE_MACOSX_RPATH ON)
endif(APPLE)
# Set the project details.
set(PROJECT_NAME YOKAI)
project(${PROJECT_NAME} LANGUAGES CXX)

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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_BINARY_DIR}/lib)

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        v3.8 # or use release tag, eg. v3.8
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_TAG v3.10.4)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# Define the Library.
add_library(${PROJECT_NAME} SHARED)

# Define the executable.
add_executable(run_tests tests/main_tests.cpp)


# Set C++ standard.
set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )

# Find dependencies.
# find_package(OpenGLRenderer REQUIRED COMPONENTS OpenGLRenderer)
find_package(OpenGL REQUIRED)
# Build 3rd Party Libraries
add_subdirectory(lib)

# Define source files.
add_subdirectory(src)

# Define Tests
add_subdirectory(tests)

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
target_compile_options(${PROJECT_NAME} PUBLIC
        # Clang
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:
        -Weverything -fcolor-diagnostics
        # Disable specific warnings.
        -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
        -Wno-deprecated-declarations -Wno-exit-time-destructors
        -Wno-switch-enum -Wno-weak-vtables -Wno-global-constructors>
        # GCC
        $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic -fdiagnostics-color=always>
        # Visual Studio
        $<$<CXX_COMPILER_ID:MSVC>:/W4>
        # Enable the clang sanitizer.
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )

# Link against the clang sanitizer.
target_link_options(${PROJECT_NAME} PUBLIC
        $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang>,$<PLATFORM_ID:${SANITIZER_OS}>>:${SANITIZER_FLAGS}>
        )
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE 1)
# Include and link against dependencies.
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL glfw glew assimp glm reactphysics3d spdlog::spdlog imgui imguizmo nlohmann_json::nlohmann_json${CMAKE_DL_LIBS})

target_link_libraries(run_tests PUBLIC YOKAI CppUTest CppUTestExt ${CMAKE_DL_LIBS})

target_include_directories(run_tests PUBLIC ${CppUTest_SOURCE_DIR}/include)
