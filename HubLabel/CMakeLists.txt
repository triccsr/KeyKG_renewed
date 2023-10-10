add_library(HubLabel
        HubLabel.cpp
        HubLabel.h
        HLType.h)
add_subdirectory(BC)

target_link_libraries(HubLabel PRIVATE BC)

target_include_directories(HubLabel INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})