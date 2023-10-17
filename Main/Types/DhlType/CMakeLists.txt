add_library(DhlType DhlType.h)
set_target_properties(DhlType PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(DhlType PUBLIC HLType)
target_include_directories(DhlType INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})