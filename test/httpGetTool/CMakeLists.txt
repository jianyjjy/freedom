cmake_minimum_required (VERSION 2.6)
project (httpGetTool)

include_directories(../../httpGet ../../include)
add_executable(httpGetTool testmain.cpp)


target_link_libraries(httpGetTool httpGet)
target_link_libraries(httpGetTool curl)
