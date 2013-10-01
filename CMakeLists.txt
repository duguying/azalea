project(iChat)

# varibility
set(SRC_LIST ichat.c)
set(LOG_LIST log/log.c)
set(LOG_TEST log/test.c)
set(TCPER_LIST tcper/tcper.c)

# main executation
add_executable(iChat ${SRC_LIST})
add_executable(tcper ${TCPER_LIST})
# solid library
add_library(log SHARED ${LOG_LIST})
add_executable(logtest ${LOG_TEST})
# dynamic library


# library directory
include_directories(build)

# target link libraries
target_link_libraries(iChat pthread dl log)
target_link_libraries(tcper pthread)

# cmake configuration
cmake_minimum_required(VERSION 2.8)
