cmake_minimum_required(VERSION 3.21)
project(excentricite)

set(CMAKE_CXX_STANDARD 20)

add_executable(excentricite main.cpp disjointsets.h graph.h graph2img.h)


set(GRAPHVIZ_DIR "C:/Program Files/Graphviz")
file(GLOB GVC_LIBS "${GRAPHVIZ_DIR}/lib/*.lib")
target_link_libraries(${CMAKE_PROJECT_NAME} ${GVC_LIBS})
include_directories("${GRAPHVIZ_DIR}/include/graphviz")