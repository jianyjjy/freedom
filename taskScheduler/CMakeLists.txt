cmake_minimum_required (VERSION 2.6)
project (taskScheduler)

set (SRC UrlMonitor.cpp)
LIST(APPEND SRC MonitorMgr.cpp)
LIST(APPEND SRC TaskHandler.cpp)
LIST(APPEND SRC Task.cpp)


add_library(taskScheduler SHARED ${SRC})