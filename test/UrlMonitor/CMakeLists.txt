cmake_minimum_required (VERSION 2.6)
project (UrlMonitorTest)

include_directories(../../UrlMonitor ../../include .)
add_executable(UrlMonitorTest unittest.cpp)


target_link_libraries(UrlMonitorTest urlMonitor)

