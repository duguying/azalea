project(iChat)

#############################################
# varibility
set(SRC_LIST ichat.c)
set(LOG_LIST log/log.c)
set(LOG_TEST log/test.c)
set(TCPER_LIST tcper/tcper.c)
set(MYSQL_VER dbs/mysql/version.c)
set(MYDRV_LIST dbs/mysql/mysql_driver.c)
set(MYSQLDRV_TEST dbs/mysql/mysql_test.c)

#############################################
# include directories
include_directories("/usr/include/mysql")
# library directory
include_directories("build")
# link directories
link_directories("/usr/lib/mysql")

#############################################
# main executation
add_executable(iChat ${SRC_LIST})
# tcp tester
add_executable(tcper ${TCPER_LIST})
# mysql version test
add_executable(my_ver ${MYSQL_VER})
# solid library, static library
add_library(log STATIC ${LOG_LIST})
# log test
add_executable(logtest ${LOG_TEST})
# mysql extension test
add_executable(mysqldrv_test ${MYSQLDRV_TEST})

# dynamic libraries
# mysql driver extension
add_library(mysql_drv SHARED ${MYDRV_LIST})

#############################################
# target link libraries
target_link_libraries(iChat pthread dl log)	# here, static has no difference with shared
target_link_libraries(tcper pthread)
target_link_libraries(my_ver mysqlclient)
target_link_libraries(mysql_drv mysqlclient)
target_link_libraries(mysqldrv_test mysql_drv)

#############################################
# cmake configuration
cmake_minimum_required(VERSION 2.8)
