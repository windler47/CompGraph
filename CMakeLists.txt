cmake_minimum_required(VERSION 3.17)
project(ComputerGraphicsNew)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(glfw)

include_directories(SYSTEM glfw/include)
include_directories(SYSTEM glm)

set(SOURCE_FILES main.cpp)

add_executable(ComputerGraphicsNew ${SOURCE_FILES})
target_link_libraries(ComputerGraphicsNew glfw ${GLFW_LIBRARIES})