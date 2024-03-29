project(core)

add_library(core STATIC
	  Engine/EventManager.hpp
    Engine/EventManager.cpp
    Engine/GameObject.cpp
    Engine/GameObject.hpp
    Engine/GameObjectManager.cpp
    Engine/GameObjectManager.hpp
    Engine/InputManagerGLFW.cpp
    Engine/InputManagerGLFW.hpp
    Engine/JSONTypes.cpp
    Engine/JSONTypes.hpp
    Engine/Component.hpp
    Memory/ConcurrentQueue.hpp
    Resource/AssetProxy.hpp
    Resource/AssetStorage.hpp
    Transform.cpp
    Transform.hpp
    Camera.hpp
    Camera.cpp
    Time.hpp

)

target_compile_options(core PRIVATE
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

target_link_libraries(core PUBLIC glfw glm imgui imguizmo spdlog::spdlog nlohmann_json::nlohmann_json)
target_include_directories(core PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)
