cmake_minimum_required(VERSION 3.11.0)

project(OpenGLPlayground VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# headers folder
include_directories(${CMAKE_SOURCE_DIR}/include)
find_package(OpenGL REQUIRED)

# wildcarding src folder for c++ files:
file(GLOB SOURCES "source/*.cpp")
file(GLOB TESTS "test/*.cpp")

# building GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("lib/glfw-3.3.2")

# targeting GLEW
include_directories(${CMAKE_SOURCE_DIR}/lib/glew-2.1.0/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/glew-2.1.0/lib)

add_executable(testOGL ${SOURCES} ${TESTS})
target_link_libraries(testOGL OpenGL::GL glfw GLEW)
