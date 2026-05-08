cmake_minimum_required(VERSION 3.16)
project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 20)

add_executable(hello_triangle_app src/main.cpp src/glad.c)

target_include_directories(hello_triangle_app PRIVATE include /opt/homebrew/include)

target_link_directories(hello_triangle_app PRIVATE /opt/homebrew/lib)

target_link_libraries(hello_triangle_app glfw "-framework OpenGL")