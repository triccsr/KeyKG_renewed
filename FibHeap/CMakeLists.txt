add_library(FibHeap FibHeap.h)
set_target_properties(FibHeap PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(FibHeap INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})