cmake_minimum_required (VERSION 2.6)
project (playlistMgrtool)

include_directories(.  ../../playlistFactory ../../playlistManager )
add_executable(playlistMgrtool unittest.cpp)


target_link_libraries(playlistMgrtool playlistMgr)
target_link_libraries(playlistMgrtool playlistFactory)
target_link_libraries(playlistMgrtool taskScheduler)
target_link_libraries(playlistMgrtool curlcpp)