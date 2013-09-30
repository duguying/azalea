project(iChat)

# varibility
set(SRC_LIST ichat.c)
set(LOG_LIST log/log.c)

# main executation
add_executable(iChat ${SRC_LIST})
# solid library
add_library(log SHARED ${LOG_LIST})
# dynamic library


# library directory
include_directories(build)

# main target
target_link_libraries(iChat pthread dl log)

cmake_minimum_required(VERSION 2.8)
