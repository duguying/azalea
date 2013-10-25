project(iChat)

#############################################
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
#############################################
# source directories varibility
set(SRC_LIST ichat.c)
set(LOG_LIST log/log.c)
set(LOG_TEST log/test.c)
set(TCPER_LIST tcper/tcper.c)
set(MYSQL_VER dbs/mysql/version.c)
set(MYDRV_LIST dbs/mysql/mysql_driver.c)
set(MYSQLDRV_TEST dbs/mysql/mysql_test.c)
set(CONF_LIST config/config.c)
set(POOL_LIST pool/pool.c)
set(PARSER_LIST parser/parser.c)
set(HASHTABLE_LIST pool/hashtable.c)
set(SQLITE_TEST dbs/sqlite3/sqlite_test.c)

#############################################
# include directories
include_directories("/usr/include/mysql")
# library directory
include_directories("build/lib")
include_directories("build/arc")
# link directories
link_directories("/usr/lib/mysql")

#############################################
# main executation
add_executable(iChat ${SRC_LIST})
# test tools
#add_executable(tcper ${TCPER_LIST}) # tcp tester
#add_executable(my_ver ${MYSQL_VER}) # mysql version test
#add_executable(mysqldrv_test ${MYSQLDRV_TEST}) # mysql extension test
#add_executable(logtest ${LOG_TEST}) # log test
#add_executable(sqlitetest ${SQLITE_TEST}) # sqlite3 test
# solid library, static library
add_library(log STATIC ${LOG_LIST})
add_library(config STATIC ${CONF_LIST})
add_library(pool STATIC ${POOL_LIST})
add_library(parser STATIC ${PARSER_LIST})
add_library(hashtable STATIC ${HASHTABLE_LIST})
#dynamic libraries
#add_library(mysql_drv SHARED ${MYDRV_LIST}) # mysql driver extension

#############################################
# target link libraries
target_link_libraries(iChat pthread dl log pool hashtable)	# here, static has no difference with shared
#target_link_libraries(tcper pthread)
#target_link_libraries(my_ver mysqlclient)
#target_link_libraries(mysql_drv mysqlclient)
#target_link_libraries(mysqldrv_test mysql_drv)
#target_link_libraries(sqlitetest sqlite3)
target_link_libraries(pool hashtable)

#############################################
# set targets directories
set_target_properties(iChat PROPERTIES RUNTIME_OUTPUT_DIRECTORY ".")

#############################################
# cmake configuration
cmake_minimum_required(VERSION 2.8)
