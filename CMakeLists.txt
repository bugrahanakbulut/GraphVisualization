cmake_minimum_required(VERSION 3.19)
project(GraphVisualization)

set(CMAKE_CXX_STANDARD 20)

add_executable(GraphVisualization src/main.cpp src/DataStructures/Graph/Graph.h src/Utils/Utils.h src/Utils/Constants.h src/DataStructures/Graph/VisualGraph/VisualGraph.h src/Utils/Resources.h src/DataStructures/Graph/GraphEdge.h src/DataStructures/Graph/GraphNode.h src/DataStructures/Graph/VisualGraph/VisualGraphNode.h src/DataStructures/Graph/VisualGraph/VisualGraphEdge.h src/DataStructures/Heap/MinHeap.h)

include_directories(headers c:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML REQUIRED system window graphics)


if (SFML_FOUND )
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(GraphVisualization ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
