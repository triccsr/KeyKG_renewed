add_library(TestHLLoader TestHLLoader.cpp TestHLLoader.h)
target_link_libraries(TestHLLoader PRIVATE WeightedGraph AbstractHLLoader)
target_include_directories(TestHLLoader INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
