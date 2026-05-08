cmake_minimum_required(VERSION 3.16)
project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 20)

add_executable(app src/main.cpp src/glad.c)

target_include_directories(app PRIVATE include /opt/homebrew/include)

target_link_directories(app PRIVATE /opt/homebrew/lib)

target_link_libraries(app glfw "-framework OpenGL")