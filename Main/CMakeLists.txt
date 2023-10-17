add_subdirectory(HLLoaders)
add_subdirectory(WeightedGraph)
add_subdirectory(Utils)
add_subdirectory(HLGenerators)
add_subdirectory(Types)
add_subdirectory(KeyKG)
configure_file(config.h.in config.h)

add_executable(Main main.cpp
)
target_include_directories(Main PUBLIC "${PROJECT_BINARY_DIR}/Main")
target_link_libraries(Main PRIVATE HLGenerators HLLoaders RandomGraph)