cmake_minimum_required(VERSION 3.11.0)

project(OpenGLPlayground VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# headers folder
include_directories(${CMAKE_SOURCE_DIR}/include)
find_package(OpenGL REQUIRED)

# targeting GLFW
include_directories(${CMAKE_SOURCE_DIR}/lib/glfw-3.3.4/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/glfw-3.3.4/lib)

# targeting GLEW
include_directories(${CMAKE_SOURCE_DIR}/lib/glew-2.1.0/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/glew-2.1.0/lib)

file(GLOB SOURCES "source/*.cpp")
file(GLOB WINDOWTEST "test/WindowTest.cpp")
file(GLOB CLEARCOLOR "test/ClearColor.cpp")
file(GLOB FRAGMENT "test/Fragment.cpp")

add_executable(windowtest ${SOURCES} ${WINDOWTEST})
target_link_libraries(windowtest OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(clearcolor ${SOURCES} ${CLEARCOLOR})
target_link_libraries(clearcolor OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(fragment ${SOURCES} ${FRAGMENT})
target_link_libraries(fragment OpenGL::GL glfw3 GLEW dl X11 pthread)


set_target_properties(windowtest clearcolor
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)