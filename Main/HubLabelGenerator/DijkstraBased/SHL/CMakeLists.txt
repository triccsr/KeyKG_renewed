target_sources(HubLabelGenerator PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/SHL.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/SHL.h"
)
add_subdirectory(BC)
target_include_directories(HubLabelGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})