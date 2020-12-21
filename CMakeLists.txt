cmake_minimum_required(VERSION 3.17)
project(ComputerGraphicsNew)

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

include_directories(SYSTEM glm)
include_directories(SYSTEM stb)
include_directories(SYSTEM glfw/include)
include_directories(SYSTEM include)

set(SOURCE_FILES main.cpp glad.c helpers.cpp Shader.cpp GlObject.cpp Camera.cpp stb_image.cpp)
add_executable(ComputerGraphicsNew ${SOURCE_FILES})
target_link_libraries(ComputerGraphicsNew glfw ${GLFW_LIBRARIES})