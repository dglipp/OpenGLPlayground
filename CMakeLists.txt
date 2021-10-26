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

# targeting SOIL2
include_directories(${CMAKE_SOURCE_DIR}/lib/SOIL2/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/SOIL2/lib)

# EXECUTABLES
file(GLOB SOURCES "source/*.cpp")
file(GLOB WINDOWTEST "test/WindowTest.cpp")
file(GLOB CLEARCOLOR "test/ClearColor.cpp")
file(GLOB FRAGMENT "test/Fragment.cpp")
file(GLOB TRIANGLE "test/Triangle.cpp")
file(GLOB FRAGMENTINTERPOL "test/FragmentInterpolation.cpp")
file(GLOB DATATOGPU "test/DataToGPU.cpp")
file(GLOB INSTANCING "test/Instancing.cpp")
file(GLOB MULTIPLEOBJ "test/MultipleObjects.cpp")
file(GLOB ORBIT "test/Orbit.cpp")
file(GLOB TEXTURE "test/Texture.cpp")
file(GLOB IDXTORUS "test/Bubacow.cpp")

add_executable(windowtest ${SOURCES} ${WINDOWTEST})
target_link_libraries(windowtest soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(clearcolor ${SOURCES} ${CLEARCOLOR})
target_link_libraries(clearcolor soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)


add_executable(triangle ${SOURCES} ${TRIANGLE})
target_link_libraries(triangle soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(fragmentInterpol ${SOURCES} ${FRAGMENTINTERPOL})
target_link_libraries(fragmentInterpol soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(dataToGPU ${SOURCES} ${DATATOGPU})
target_link_libraries(dataToGPU soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(fragment ${SOURCES} ${FRAGMENT})
target_link_libraries(fragment soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(Instancing ${SOURCES} ${INSTANCING})
target_link_libraries(Instancing soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(MultipleObj ${SOURCES} ${MULTIPLEOBJ})
target_link_libraries(MultipleObj soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(Orbit ${SOURCES} ${ORBIT})
target_link_libraries(Orbit soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(Texture ${SOURCES} ${TEXTURE})
target_link_libraries(Texture soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

add_executable(Bubacow ${SOURCES} ${IDXTORUS})
target_link_libraries(Bubacow soil2 OpenGL::GL glfw3 GLEW dl X11 pthread)

set_target_properties(windowtest clearcolor fragment triangle fragmentInterpol dataToGPU Instancing MultipleObj Orbit Texture Bubacow
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test"
)