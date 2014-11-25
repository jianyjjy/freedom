cmake_minimum_required(VERSION 2.8)

set(CMAKE_SYSTEM_NAME Linux)

link_directories(/usr/local/lib)
include_directories(include)


set(CMAKE_CXX_FLAGS "-O0 -g3 -Wall -fPIC -std=c++0x -D_GLIBCXX_USE_NANOSLEEP")

add_subdirectory(fileCompare)
add_subdirectory(hlsPlaylist)
add_subdirectory(playlistFactory)
add_subdirectory(playlistManager)
add_subdirectory(UrlMonitor)
add_subdirectory(httpGet)

add_subdirectory(test/file-compare)
add_subdirectory(test/playlistParser)
add_subdirectory(test/playlistMgr)
add_subdirectory(test/httpGetTool)
