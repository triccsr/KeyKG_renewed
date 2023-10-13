add_executable(Main main.cpp
        Run.cpp
        Run.h)
add_subdirectory(HLLoaders)
add_subdirectory(WeightedGraph)
add_subdirectory(Utils)
add_subdirectory(HubLabelGenerator)
target_link_libraries(Main PRIVATE HubLabelGenerator HLLoaders)