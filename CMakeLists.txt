cmake_minimum_required(VERSION 3.11.0)

project(OpenGLPlayground VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

#header folder
include_directories(${CMAKE_SOURCE_DIR}/include)

#library folder
if (APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/lib/macos)
else ()
    link_directories(${CMAKE_SOURCE_DIR}/lib/linux)
endif()
find_package(OpenGL REQUIRED)

#wildcarding src folder for c++ files:
file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "src/tests/*.cpp")
file(GLOB IMGUI_SRC "include/VENDOR/IMGUI/*.cpp")

add_executable(testOGL ${SOURCES} ${IMGUI_SRC} ${TESTS})

target_link_libraries(testOGL OpenGL::GL glfw GLEW)

