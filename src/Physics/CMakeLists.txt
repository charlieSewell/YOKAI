project(physics)

add_library(physics STATIC 
    PhysicsSystem.hpp
    ReactMath.hpp
    CollisionBody.hpp
    RigidBody.hpp
    ResolutionFunctions.hpp
    PhysicsResolution.hpp
    Shapes/ReactBoxShape.hpp
    Shapes/ReactShape.hpp
    Shapes/ReactSphereShape.hpp
    Shapes/ReactTerrainShape.hpp
    #Need to reimpliment to work with librarys better
    #Shapes/ReactConcaveShape.hpp
    Shapes/ReactTerrainShape.hpp

    PhysicsSystem.cpp
    ReactMath.cpp
    CollisionBody.cpp
    RigidBody.cpp
    ResolutionFunctions.cpp
    PhysicsResolution.cpp
    Shapes/ReactBoxShape.cpp
    Shapes/ReactShape.cpp
    Shapes/ReactSphereShape.cpp
    Shapes/ReactTerrainShape.cpp
    #Shapes/ReactConcaveShape.cpp
    Shapes/ReactTerrainShape.cpp
    
)
set_target_properties(physics PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )

target_compile_options(physics PRIVATE
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


target_link_libraries(physics PUBLIC core reactphysics3d)
target_include_directories(physics PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:>  # <prefix>/include/mylib
)
