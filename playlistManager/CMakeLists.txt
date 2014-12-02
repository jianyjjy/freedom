cmake_minimum_required (VERSION 2.6)
project (playlistMgr)

set (SRC PlaylistManager.cpp)
LIST(APPEND SRC RenditionGroups.cpp)
LIST(APPEND SRC VariantPlaylist.cpp)

include_directories(.)
include_directories(../playlistFactory)
include_directories(../taskScheduler)
include_directories(../fileCompare)
include_directories(../curlcpp/include)
include_directories(../curlcpp/src)

add_library(playlistMgr SHARED ${SRC})