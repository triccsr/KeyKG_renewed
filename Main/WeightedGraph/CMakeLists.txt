add_library(WeightedGraph WeightedGraph.cpp WeightedGraph.h WeightedOutEdge.cpp WeightedOutEdge.h
        WeightedGraphDef.h
        WeightedEdge.h)
target_link_libraries(WeightedGraph PRIVATE RandomMT Timer OpenFile)
target_include_directories(WeightedGraph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})