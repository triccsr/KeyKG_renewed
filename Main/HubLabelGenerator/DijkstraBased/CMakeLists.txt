target_sources(HubLabelGenerator PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/DijkstraBasedAbstract.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/DijkstraBasedAbstract.cpp"
)
add_subdirectory(PLL)
add_subdirectory(SHL)
target_include_directories(HubLabelGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})