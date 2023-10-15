add_library(PLL PLL.cpp PLL.h)
target_link_libraries(PLL PUBLIC AbstractDijkstraBased)
target_include_directories(PLL PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})