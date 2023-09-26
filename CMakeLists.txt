cmake_minimum_required(VERSION 3.10)
project(KeyKG)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_compile_options(-Wall -Wextra -Wconversion -Wshadow -fdiagnostics-color=always)

#add_executable(KeyKG main.cpp
#        FibHeap/FibHeap.h
#        Timer/Timer.cpp
#        Timer/Timer.h
#        WeightedGraph/WeightedGraph.cpp
#        WeightedGraph/WeightedGraph.h
#        WeightedGraph/WeightedOutEdge.h
#        WeightedGraph/WeightedOutEdge.cpp
#        WeightedGraph/WeightedOutEdge.cpp
#        RandomDouble/RandomDouble.cpp
#        RandomDouble/RandomDouble.h
#)

add_subdirectory(FibHeap)
add_subdirectory(RandomDouble)
add_subdirectory(Timer)
add_subdirectory(WeightedGraph)
add_subdirectory(HubLabel)

add_executable(KeyKG main.cpp)

target_link_libraries(KeyKG PUBLIC FibHeap RandomDouble Timer WeightedGraph)


target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}
)