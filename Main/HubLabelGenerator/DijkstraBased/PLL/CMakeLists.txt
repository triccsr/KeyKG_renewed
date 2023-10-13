target_sources(HubLabelGenerator PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/PLL.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/PLL.h"
)
target_include_directories(HubLabelGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})