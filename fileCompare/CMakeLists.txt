cmake_minimum_required (VERSION 2.6)
project (filecompare)

set (FC_SRC CompareFile.cpp)

add_library(filecompare SHARED ${FC_SRC})