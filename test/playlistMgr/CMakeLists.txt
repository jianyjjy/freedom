cmake_minimum_required (VERSION 2.6)
project (playlistMgrtool)

include_directories(. ../../hlsPlaylist ../../playlistFactory ../../playlistManager)
add_executable(playlistMgrtool unittest.cpp)


target_link_libraries(playlistMgrtool playlistMgr)
target_link_libraries(playlistMgrtool playlistFactory)
target_link_libraries(playlistMgrtool hlsPlaylist)
target_link_libraries(playlistMgrtool urlMonitor)
target_link_libraries(playlistMgrtool curlcpp)