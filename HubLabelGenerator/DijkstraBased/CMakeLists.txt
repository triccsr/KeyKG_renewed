target_sources(HubLabelGenerator PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/DijkstraBasedAbstract.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/DijkstraBasedAbstract.cpp")
target_include_directories(HubLabelGenerator PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")