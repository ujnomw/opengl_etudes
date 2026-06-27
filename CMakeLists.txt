cmake_minimum_required(VERSION 3.16)
project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 23)

add_executable(hello_triangle_app 
                                    src/main.cpp 
                                    src/glad.c
                                    src/stb_image.cpp
                                    )

target_include_directories(hello_triangle_app
                           PRIVATE include 
                           /opt/homebrew/include
                           ${CMAKE_SOURCE_DIR}/include/glm-1.0.3
                           )

target_link_directories(hello_triangle_app PRIVATE /opt/homebrew/lib)

target_link_libraries(hello_triangle_app glfw "-framework OpenGL")

add_custom_command(
    TARGET hello_triangle_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:hello_triangle_app>/assets
)
