cmake_minimum_required (VERSION 2.6)
project (playlistFactory)

set (SRCS PlaylistFactory.cpp)
LIST(APPEND SRCS MasterPlaylist.cpp)
LIST(APPEND SRCS MediaPlaylist.cpp)
LIST(APPEND SRCS IFramePlaylist.cpp)
LIST(APPEND SRCS VariantsInfo.cpp)

include_directories(.)

add_library(playlistFactory SHARED ${SRCS})