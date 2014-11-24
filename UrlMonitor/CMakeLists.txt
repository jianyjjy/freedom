cmake_minimum_required (VERSION 2.6)
project (urlMonitor)

set (SRC UrlMonitor.cpp)
LIST(APPEND SRC MonitorMgr.cpp)

include_directories(.)

add_library(urlMonitor SHARED ${SRC})