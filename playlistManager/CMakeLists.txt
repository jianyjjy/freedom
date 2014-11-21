cmake_minimum_required (VERSION 2.6)
project (playlistMgr)

set (SRC PlaylistManager.cpp)
LIST(APPEND SRC RenditionGroups.cpp)
LIST(APPEND SRC VariantPlaylist.cpp)

include_directories(. ../hlsPlaylist ../playlistFactory)

add_library(playlistMgr SHARED ${SRC})