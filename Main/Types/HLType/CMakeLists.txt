add_library(HLType HLType.h)
set_target_properties(HLType PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(HLType INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})