add_library(KeyKG KeyKG.cpp KeyKG.h)
target_link_libraries(KeyKG PRIVATE WeightedGraph HLLoaders Timer ArrayOnHeap DhlType Timer OpenFile)
target_include_directories(KeyKG INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})