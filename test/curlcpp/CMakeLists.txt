cmake_minimum_required (VERSION 2.6)
project (curlcpptest)

include_directories(../../curlcpp ../../include)

set (SRCS CurlCppTest.cpp)
LIST(APPEND SRCS unittest.cpp)


add_executable(curlcpptest ${SRCS})


target_link_libraries(curlcpptest curlcpp)