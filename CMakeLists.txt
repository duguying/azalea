project(iChat)

set(SRC_LIST ichat.c)
set(LOG_LIST log/log.c)

add_executable(iChat ${SRC_LIST})
add_library(log SHARED ${LOG_LIST})

include_directories(build)

target_link_libraries(iChat pthread dl)

cmake_minimum_required(VERSION 2.8)
