cmake_minimum_required(VERSION 3.9)
project(opengl_imgui_playground)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(opengl_imgui_playground
        main.cpp
        extern/imgui/imgui.cpp
        extern/imgui/imgui.h
        extern/imgui/imgui_draw.cpp
        extern/imgui/imgui_internal.h
        extern/imgui/imconfig.h
        extern/imgui/stb_textedit.h
        extern/imgui/stb_truetype.h
        extern/imgui/stb_rect_pack.h
        extern/imgui/examples/libs/gl3w/GL/gl3w.c
        extern/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.cpp
        extern/imgui/examples/opengl3_example/imgui_impl_glfw_gl3.h
        )

include_directories(
        extern/imgui
        extern/imgui/examples/opengl3_example
        extern/imgui/examples/libs/gl3w
        ${OPENGL_INCLUDE_DIR}
        ${GLFW_INCLUDE_PATH}
        )

target_link_libraries(opengl_imgui_playground
        ${OPENGL_gl_LIBRARY} # Koska gl3w.c tämän halusi
        glfw
        )

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
    message(STATUS "dir='${dir}'")
endforeach()
