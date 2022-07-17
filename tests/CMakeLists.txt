enable_testing()

# CppUTest
include(FetchContent)
FetchContent_Declare(
    CppUTest
    GIT_REPOSITORY https://github.com/cpputest/cpputest.git
    GIT_TAG        v4.0 # or use release tag, eg. v3.8
)
# Set this to ON if you want to have the CppUTests in your project as well.
set(TESTS OFF CACHE BOOL "Switch off CppUTest Test build")
FetchContent_MakeAvailable(CppUTest)

set(TestSource
    main_tests.cpp
    core_tests/transform_tests.cpp

)

# Define the Tests Executable
add_executable(YOKAI_tests ${TestSource})
#add_test(core_tests YOKAI_tests)
add_test(NAME core_tests
         COMMAND YOKAI_tests)
set_target_properties(YOKAI_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
target_compile_options(YOKAI_tests PRIVATE
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
        
target_link_libraries(YOKAI_tests PRIVATE YOKAI CppUTest CppUTestExt ${CMAKE_DL_LIBS})
target_include_directories(YOKAI_tests PUBLIC ${CppUTest_SOURCE_DIR}/include)

add_custom_command(TARGET YOKAI_tests POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/test_data ${CMAKE_CURRENT_BINARY_DIR}/test_data)