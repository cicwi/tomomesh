cmake_minimum_required(VERSION 3.0.0)

project(meshprojection)
add_subdirectory("ext/pybind11")

link_directories(
    "~/.local/lib/"
)

include_directories(
    "ext/assimp/include/"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wfatal-errors -Werror -Wextra -g -O3")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)

set(BINDING_NAME "tomomesh")

set(
    BINDING_SOURCES
    "bind_to_py.cpp"
    "load_triangles_from_obj.cpp"
)

set(
    LIB_NAMES
    "assimp"
)

pybind11_add_module(${BINDING_NAME} ${BINDING_SOURCES})
target_link_libraries(${BINDING_NAME} PRIVATE ${LIB_NAMES})
