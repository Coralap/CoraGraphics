cmake_minimum_required(VERSION 3.10)
project(CoraGraphics)

set(CMAKE_CXX_STANDARD 17)

# Add GLAD (make sure glad.c is in src/, and glad headers are in include/)
add_library(glad src/glad.c)
target_include_directories(glad PUBLIC include/)

# Add your main executable
add_executable(CoraGraphics src/main.cpp)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Download and build GLFW automatically
include(FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8   # latest stable release as of now
)
FetchContent_MakeAvailable(glfw)

# Link everything
target_link_libraries(CoraGraphics PRIVATE glfw OpenGL::GL glad)
