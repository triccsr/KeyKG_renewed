add_library(CsrHLLoader HLType.h CsrHLLoader.cpp CsrHLLoader.h)
target_link_libraries(CsrHLLoader PRIVATE AbstractHLLoader OpenFile)
target_link_libraries(CsrHLLoader PUBLIC ArrayOnHeap)
target_include_directories(CsrHLLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})