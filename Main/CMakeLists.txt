add_executable(Main main.cpp)
add_subdirectory(HubLabel)
add_subdirectory(WeightedGraph)
target_link_libraries(Main PUBLIC HubLabel WeightedGraph)