add_library(GraphTypes GraphTypes.h)
set_target_properties(GraphTypes PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(GraphTypes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})