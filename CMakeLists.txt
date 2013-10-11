project(iChat)

# varibility
set(SRC_LIST ichat.c)
set(LOG_LIST log/log.c)
set(LOG_TEST log/test.c)
set(TCPER_LIST tcper/tcper.c)
set(MYSQL_VER dbs/mysql/version.c)

#include directories
include_directories("/usr/include/mysql")
LINK_DIRECTORIES("/usr/lib/mysql")

# main executation
add_executable(iChat ${SRC_LIST})
# tcp tester
add_executable(tcper ${TCPER_LIST})
# mysql version test
add_executable(my_ver ${MYSQL_VER})
# solid library
add_library(log SHARED ${LOG_LIST})
# log test
add_executable(logtest ${LOG_TEST})
# dynamic library


# library directory
include_directories(build)

# target link libraries
target_link_libraries(iChat pthread dl log)
target_link_libraries(tcper pthread)
target_link_libraries(my_ver mysqlclient)

# cmake configuration
cmake_minimum_required(VERSION 2.8)
