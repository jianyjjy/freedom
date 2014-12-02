cmake_minimum_required (VERSION 2.6)
project (taskScheduler)

set (SRC UrlMonitor.cpp)
LIST(APPEND SRC MonitorMgr.cpp)
LIST(APPEND SRC TaskHandler.cpp)
LIST(APPEND SRC Task.cpp)

include_directories(.)
include_directories(../playlistFactory)
include_directories(../playlistManager)
include_directories(../fileCompare)
include_directories(../curlcpp/include)
include_directories(../curlcpp/src)


add_library(taskScheduler SHARED ${SRC})