cmake_minimum_required (VERSION 2.6)
project (taskSchedulerTest)

include_directories(../../taskScheduler .)
add_executable(taskSchedulerTest unittest.cpp)


target_link_libraries(taskSchedulerTest taskScheduler)

