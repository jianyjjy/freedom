cmake_minimum_required (VERSION 2.6)
project (playlistMgr)

set (SRC PlaylistManager.cpp)
LIST(APPEND SRC RenditionGroups.cpp)
LIST(APPEND SRC VariantPlaylist.cpp)

include_directories(.)
include_directories(../hlsPlaylist)
include_directories(../playlistFactory)
include_directories(../UrlMonitor)

add_library(playlistMgr SHARED ${SRC})