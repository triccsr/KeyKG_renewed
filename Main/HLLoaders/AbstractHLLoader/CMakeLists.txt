add_library(AbstractHLLoader AbstractHLLoader.h)
target_include_directories(AbstractHLLoader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AbstractHLLoader PUBLIC WeightedGraph ArrayOnHeap DhlType HLType)