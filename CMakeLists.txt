project(iChat)

# set compilers
# SET(CMAKE_C_COMPILER gcc)
# SET(CMAKE_C_COMPILER clang)
#############################################
# gdb Debug support
set(TEST true)
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -ggdb -pg")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -s -DNDEBUG")

# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# show log on screen
add_definitions(-D_SCR_LOG_)
#############################################
# source directories varibility
set(SRC_LIST ${SRC_DIR}/ichat.c)
set(LOG_LIST ${SRC_DIR}/log/log.c)
set(TCPER_LIST ${SRC_DIR}/tcper/tcper.c)
set(MYDRV_LIST ${SRC_DIR}/dbs/mysql/mysql_driver.c)
set(CONF_LIST ${SRC_DIR}/config/config.c)
set(POOL_LIST ${SRC_DIR}/pool/pool.c)
set(PARSER_LIST ${SRC_DIR}/parser/parser.c)
# Tests
set(CONFIG_TEST ${TEST_DIR}test_conf.c)
set(LOG_TEST ${TEST_DIR}test_log.c)
set(MYSQL_VER ${TEST_DIR}test_mysql.c)
set(MYSQLDRV_TEST ${TEST_DIR}test_mysqldrv.c)
set(SQLITE_TEST ${TEST_DIR}test_sqlite.c)
set(HASH_LIST ${TEST_DIR}test_hashtable.c)
set(TEST_STACK_LIST ${TEST_DIR}test_stack.c)
set(TEST_POOL_LIST ${TEST_DIR}test_pool.c)
# Data Struct
set(
	DS_LIST 
	${SRC_DIR}/ds/ds.c
	${SRC_DIR}/ds/hashtable.c 
	${SRC_DIR}/ds/stack.c
)
#############################################
# include directories
include_directories("/usr/include/mysql")
# library directory
include_directories("build/lib")
include_directories("include")
include_directories("src")
# link directories
link_directories("/usr/lib/mysql")
#############################################
#############################################
if(WIN32)
	message("In Windows System!")
elseif(UNIX)
	message("In Unix System!")
	message("dmalloc tools will be used...")
	set(CFLAGS "-DDMALLOC -DDMALLOC_FUNC_CHECK")
	# add_executable(ichat ${SRC_LIST})
	# target_link_libraries(ichat pthread dl log pool ds)
	add_executable(tcper ${TCPER_LIST}) # tcp tester
	target_link_libraries(tcper pthread)
	add_library(mysql_drv SHARED ${MYDRV_LIST})
	target_link_libraries(mysql_drv mysqlclient)
	message("Tests will be build!")
	if(TEST)
		add_executable(test_mysql ${MYSQL_VER})
		add_executable(test_mysqldrv ${MYSQLDRV_TEST}) 
		add_executable(test_sqlite ${SQLITE_TEST})
		target_link_libraries(test_mysql mysqlclient)
		target_link_libraries(test_mysqldrv mysql_drv)
		target_link_libraries(test_sqlite sqlite3)
	endif(TEST)
	
elseif(APPLE)
	message("In Mac System!")
elseif(CI)
	message("In Travis CI System!")
endif(WIN32)

#############################################
# tests
if(TEST)
	add_executable(test_log ${LOG_TEST}) # log test
	add_executable(test_conf ${CONFIG_TEST}) # config test
	add_executable(test_hashtable ${HASH_LIST})
	add_executable(test_stack ${TEST_STACK_LIST})
	target_link_libraries(test_log log)
	target_link_libraries(test_conf config)
	target_link_libraries(test_hashtable ds)
	target_link_libraries(test_stack ds)
	# target_link_libraries(test_pool pool)
endif()
# solid library, static library
add_library(log STATIC ${LOG_LIST})
add_library(config STATIC ${CONF_LIST})
add_library(parser STATIC ${PARSER_LIST})
add_library(ds STATIC ${DS_LIST})
# add_library(pool STATIC ${POOL_LIST})
# dmalloc support
if(NOT CI)
	target_link_libraries(ds dmalloc)
	target_link_libraries(log dmalloc)
	target_link_libraries(config dmalloc)
	add_definitions(-D_DMALLOC_)
endif()
#############################################
if(TEST)
	ENABLE_TESTING()
	ADD_TEST(T_CONF "./bin/test_conf")
	ADD_TEST(T_HT "./bin/test_hashtable")
	ADD_TEST(T_LOG "./bin/test_log")
	ADD_TEST(T_MYSQL "./bin/test_mysql")
	ADD_TEST(T_SQLITE "./bin/test_sqlite")
	ADD_TEST(T_STACK "./bin/test_stack")
endif()
# installation
#############################################
INSTALL(PROGRAMS build/bin/ichat DESTINATION /usr/local/azalea/bin)
INSTALL(PROGRAMS build/bin/tcper DESTINATION /usr/local/azalea/bin)
INSTALL(PROGRAMS build/lib/libmysql_drv.so DESTINATION /usr/local/azalea/lib)
#############################################
# cmake configuration
cmake_minimum_required(VERSION 2.8)
