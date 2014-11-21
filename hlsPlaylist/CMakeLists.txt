cmake_minimum_required (VERSION 2.6)
project (hlsPlaylist)

set (HLSPL_SRC MasterPlaylist.cpp)
LIST(APPEND HLSPL_SRC MediaPlaylist.cpp)
LIST(APPEND HLSPL_SRC IFramePlaylist.cpp)

include_directories(.)

add_library(hlsPlaylist SHARED ${HLSPL_SRC})