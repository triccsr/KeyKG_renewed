add_executable(Main main.cpp
        Run.cpp
        Run.h)
add_subdirectory(HubLabel)
add_subdirectory(WeightedGraph)
target_link_libraries(Main PUBLIC HubLabel WeightedGraph HubLabelGenerator)