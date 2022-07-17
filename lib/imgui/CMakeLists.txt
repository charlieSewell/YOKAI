project(imgui)

add_library(imgui STATIC)

target_sources(imgui PRIVATE
        imgui/imgui.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_demo.cpp
        )

target_compile_options(imgui PRIVATE -fPIC)

target_include_directories(imgui PUBLIC . imgui)
