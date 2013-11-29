project(iChat)

#############################################
# gdb Debug support
set(TEST true)
set(CMAKE_BUILD_TYPE "Debug")  
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")  
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)
#############################################
# source directories varibility
set(SRC_LIST src/ichat.c)
set(LOG_LIST src/log/log.c)
set(TCPER_LIST src/tcper/tcper.c)
set(MYDRV_LIST src/dbs/mysql/mysql_driver.c)
set(CONF_LIST src/config/config.c)
set(POOL_LIST src/pool/pool.c)
set(PARSER_LIST src/parser/parser.c)
# Tests
set(CONFIG_TEST Tests/test_conf.c)
set(LOG_TEST Tests/test_log.c)
set(MYSQL_VER Tests/test_mysql.c)
set(MYSQLDRV_TEST Tests/test_mysqldrv.c)
set(SQLITE_TEST Tests/test_sqlite.c)
set(HASH_LIST Tests/test_hashtable.c)
set(TEST_STACK_LIST Tests/test_stack.c)
# Data Struct
set(
	DS_LIST 
	src/ds/hashtable.c 
	src/ds/stack.c
)
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
add_executable(ichat ${SRC_LIST})

# tools
add_executable(tcper ${TCPER_LIST}) # tcp tester

# tests
if(TEST)
	message("Tests will be build!")
	add_executable(test_mysql ${MYSQL_VER}) # mysql version test
	add_executable(test_mysqldrv ${MYSQLDRV_TEST}) # mysql extension test
	add_executable(test_log ${LOG_TEST}) # log test
	add_executable(test_sqlite ${SQLITE_TEST}) # sqlite3 test
	add_executable(test_conf ${CONFIG_TEST}) # config test
	add_executable(test_hashtable ${HASH_LIST})
	add_executable(test_stack ${TEST_STACK_LIST})
	target_link_libraries(test_mysql mysqlclient)
	target_link_libraries(test_mysqldrv mysql_drv)
	target_link_libraries(test_sqlite sqlite3)
	target_link_libraries(test_conf config)
	target_link_libraries(test_hashtable ds)
	target_link_libraries(test_stack ds)
endif()

# solid library, static library
add_library(log STATIC ${LOG_LIST})
add_library(config STATIC ${CONF_LIST})
add_library(pool STATIC ${POOL_LIST})
add_library(parser STATIC ${PARSER_LIST})
add_library(ds STATIC ${DS_LIST})
# dynamic libraries
add_library(mysql_drv SHARED ${MYDRV_LIST}) # mysql driver extension

#############################################
# target link libraries
target_link_libraries(ichat pthread dl log pool hashtable)	# here, static has no difference with shared
target_link_libraries(tcper pthread)
target_link_libraries(mysql_drv mysqlclient)
target_link_libraries(pool hashtable)

#############################################
# set targets directories
# set_target_properties(ichat PROPERTIES RUNTIME_OUTPUT_DIRECTORY ".")

#############################################
# cmake configuration
cmake_minimum_required(VERSION 2.6)
