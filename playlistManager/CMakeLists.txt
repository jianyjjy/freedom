cmake_minimum_required (VERSION 2.6)
project (playlistMgr)

set (SRC PlaylistManager.cpp)

include_directories(. ../hlsPlaylist ../playlistFactory)

add_library(playlistMgr SHARED ${SRC})