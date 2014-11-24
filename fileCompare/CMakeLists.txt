cmake_minimum_required (VERSION 2.6)
project (filecompare)

set (FC_SRC CompareFile.cpp)
LIST(APPEND FC_SRC AddedLine.cpp)
LIST(APPEND FC_SRC DeletedLine.cpp)
LIST(APPEND FC_SRC ModifiedLine.cpp)

add_library(filecompare SHARED ${FC_SRC})