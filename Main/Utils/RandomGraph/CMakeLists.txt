add_library(RandomGraph RandomGraph.cpp RandomGraph.h)
target_link_libraries(RandomGraph PRIVATE OpenFile RandomMT)
target_include_directories(RandomGraph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})