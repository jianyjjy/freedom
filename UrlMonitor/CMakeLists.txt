cmake_minimum_required (VERSION 2.6)
project (urlMonitor)

set (SRC UrlMonitor.cpp)
LIST(APPEND SRC MonitorMgr.cpp)
LIST(APPEND SRC TaskHandler.cpp)

include_directories(. ../include)

add_library(urlMonitor SHARED ${SRC})