add_library(BC BC.cpp BC.h)

target_link_libraries(BC PUBLIC WeightedGraph)
target_include_directories(BC INTERFACE .)