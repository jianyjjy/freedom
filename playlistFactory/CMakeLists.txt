cmake_minimum_required (VERSION 2.6)
project (playlistFactory)

set (PF_SRC PlaylistFactory.cpp)

include_directories(. ../hlsPlaylist)

add_library(playlistFactory SHARED ${PF_SRC})