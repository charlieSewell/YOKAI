project(imgui)

add_library(imgui STATIC)

target_sources(imgui PRIVATE
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        )

target_compile_options(imgui PRIVATE -fPIC)

target_include_directories(imgui PUBLIC . imgui)
target_link_libraries(imgui PRIVATE glfw glew ${APP_SERVICES_LIBRARY} ${COCOA_LIBRARY})
