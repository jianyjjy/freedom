cmake_minimum_required (VERSION 2.6)
project (httpGet)

set (HTTP_GET_SRC HTTPGet.cpp)

add_library(httpGet SHARED ${HTTP_GET_SRC})
