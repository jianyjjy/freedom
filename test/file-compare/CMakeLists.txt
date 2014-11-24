cmake_minimum_required (VERSION 2.6)
project (filecomparetool)

include_directories(../../fileCompare ../../include)
add_executable(filecomparetool unittest.cpp)


target_link_libraries(filecomparetool filecompare)