project(iChat)

# set(NDK true)
# set compilers
# SET(CMAKE_C_COMPILER gcc)
# SET(CMAKE_C_COMPILER clang)
if(NDK)
	SET(CMAKE_C_COMPILER /usr/local/arm-linux-androideabi-4.6/arm-linux-androideabi/bin/gcc)
	set(CI true)
	message("Build in NDK environment for arm-linux-androideabi...")
endif(NDK)
############################################################
# gdb Debug support
set(TEST true)
set(CMAKE_BUILD_TYPE "Debug")
# set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -s -DNDEBUG")

# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# show log on screen
add_definitions(-D_SCR_LOG_)
link_directories("build/lib")

include_directories("include")
include_directories("src")
#############################################################
if(CI)
	message("In Travis CI System!")
endif(CI)
if(UNIX)
	message("In Unix System!")
	message("dmalloc tools will be used...")
	if(NOT CI)
		add_definitions(-D_DMALLOC_)
		set(CFLAGS "-DDMALLOC -DDMALLOC_FUNC_CHECK")
	endif()
	link_directories("/usr/lib/mysql")
	include_directories("/usr/include/mysql")
elseif(WIN32)
	message("In Windows System!")
	set(CI true)
	link_directories("C:/Program Files/MySQL/MySQL Connector C 6.1 6.1.2/lib/vs11")
	include_directories("C:/Program Files/MySQL/MySQL Connector C 6.1 6.1.2/include")
endif(UNIX)
#############################################################
# main excutable
set(SRC_LIST ${SRC_DIR}/ichat.c)
add_executable(ichat ${SRC_LIST})
target_link_libraries(ichat dl apis net log pool ds)

# client
if(UNIX)
	set(CLIENT_LIST ${SRC_DIR}/client/iclient.c)
	add_executable(iclient ${CLIENT_LIST})
	target_link_libraries(iclient apis net)
elseif(WIN32)
	set(CLIENT_LIST ${SRC_DIR}/client/iclient.c)
	add_executable(iclient ${CLIENT_LIST})
	target_link_libraries(iclient apis net)
endif(UNIX)
#############################################################
# APIS

if(UNIX)
	set(
		APIS_LIST
		${SRC_DIR}/apis/thread.c
		${SRC_DIR}/apis/sock.c
		${SRC_DIR}/apis/process.c
	)
	add_library(apis STATIC ${APIS_LIST})
	if(NDK)# if ndk, pthread is in core, needn't -lpthread
	else(NDK)
		target_link_libraries(apis pthread)
	endif(NDK)
elseif(WIN32)
	set(
		APIS_LIST
		${SRC_DIR}/apis/thread.c
		${SRC_DIR}/apis/sock.c
		${SRC_DIR}/apis/process.c
	)
	add_library(apis STATIC ${APIS_LIST})
	target_link_libraries(apis ws2_32)
endif(UNIX)

# Data Struct library
if(UNIX)
	set(
		DS_LIST 
		${SRC_DIR}/ds/ds.c
		${SRC_DIR}/ds/hashtable.c 
		${SRC_DIR}/ds/stack.c
	)
	add_library(ds STATIC ${DS_LIST})
	if(CI)
	else()
		target_link_libraries(ds dmalloc)
	endif(CI)
elseif(WIN32)
	set(
		DS_LIST 
		${SRC_DIR}/ds/ds.c
		${SRC_DIR}/ds/hashtable.c 
		${SRC_DIR}/ds/stack.c
	)
	add_library(ds STATIC ${DS_LIST})
endif(UNIX)

#config library
if(UNIX)
	set(CONF_LIST ${SRC_DIR}/config/config.c)
	add_library(config STATIC ${CONF_LIST})
	if(NOT CI)
		target_link_libraries(config dmalloc)
	endif()
elseif(WIN32)
	set(CONF_LIST ${SRC_DIR}/config/config.c)
	add_library(config STATIC ${CONF_LIST})
endif(UNIX)

#pool library
if(UNIX)
	set(POOL_LIST 
		${SRC_DIR}/pool/pool.c
		${SRC_DIR}/pool/shakehands.c
	)
	add_library(pool STATIC ${POOL_LIST})
	target_link_libraries(pool net)
elseif(WIN32)
	set(POOL_LIST 
		${SRC_DIR}/pool/pool.c
		${SRC_DIR}/pool/shakehands.c
	)
	add_library(pool STATIC ${POOL_LIST})
	target_link_libraries(pool net)
endif(UNIX)

#parser library
if(UNIX)
	set(PARSER_LIST 
		${SRC_DIR}/parser/parser.c
	)
	add_library(parser STATIC ${PARSER_LIST})
elseif(WIN32)
	set(PARSER_LIST 
		${SRC_DIR}/parser/parser.c
	)
	add_library(parser STATIC ${PARSER_LIST})
endif(UNIX)

#net library
if(UNIX)
	set(NET_LIST 
		${SRC_DIR}/net/net.c
		${SRC_DIR}/net/message.c
	)
	add_library(net STATIC ${NET_LIST})
	if(CI)
		target_link_libraries(net ds)
	else(CI)
		target_link_libraries(net dmalloc ds)
	endif(CI)
elseif(WIN32)
	set(NET_LIST 
		${SRC_DIR}/net/net.c
		${SRC_DIR}/net/message.c
	)
	add_library(net STATIC ${NET_LIST})
	target_link_libraries(net ds)
endif(UNIX)

#log library
if(UNIX)
	set(LOG_LIST ${SRC_DIR}/log/log.c)
	add_library(log STATIC ${LOG_LIST})
	if(NOT CI)
		target_link_libraries(log dmalloc)
	endif()
elseif(WIN32)
	set(LOG_LIST ${SRC_DIR}/log/log.c)
	add_library(log STATIC ${LOG_LIST})
endif(UNIX)

#client library
if(UNIX)
	set(CLILIB_LIST 
		${SRC_DIR}/client/client.c
	)
	add_library(client STATIC ${CLILIB_LIST})
	if(NOT CI)
		target_link_libraries(client dmalloc)
	endif()
elseif(WIN32)
	set(CLILIB_LIST 
		${SRC_DIR}/client/client.c
	)
	add_library(client STATIC ${CLILIB_LIST})
endif(UNIX)

############################################################################
#build the tests
if(TEST)
ENABLE_TESTING()

	set(CONFIG_TEST ${TEST_DIR}test_conf.c)
	add_executable(test_conf ${CONFIG_TEST})
	target_link_libraries(test_conf config)
	ADD_TEST(T_CONF "./bin/test_conf")

	set(LOG_TEST ${TEST_DIR}test_log.c)
	add_executable(test_log ${LOG_TEST})
	target_link_libraries(test_log log)
	ADD_TEST(T_LOG "./bin/test_log")

	set(HASH_LIST ${TEST_DIR}test_hashtable.c)
	add_executable(test_hashtable ${HASH_LIST})
	target_link_libraries(test_hashtable ds)
	ADD_TEST(T_HT "./bin/test_hashtable")

	set(TEST_STACK_LIST ${TEST_DIR}test_stack.c)
	add_executable(test_stack ${TEST_STACK_LIST})
	target_link_libraries(test_stack ds)
	ADD_TEST(T_STACK "./bin/test_stack")

	set(TEST_POOL_LIST ${TEST_DIR}test_pool.c)
	add_executable(test_pool ${TEST_POOL_LIST})
	target_link_libraries(test_pool pool ds)
	ADD_TEST(T_POOL "./bin/test_pool")

	set(TEST_PTH_LIST ${TEST_DIR}test_pth.c)
	add_executable(test_pth ${TEST_PTH_LIST})
	target_link_libraries(test_pth apis)
	ADD_TEST(T_PTH "./bin/test_pth")

	set(TEST_SOCK_LIST ${TEST_DIR}test_sock.c)
	add_executable(test_sock ${TEST_SOCK_LIST})
	target_link_libraries(test_sock apis)
	ADD_TEST(T_SOCK "./bin/test_sock")

	set(TEST_NET_LIST ${TEST_DIR}test_net.c)
	add_executable(test_net ${TEST_NET_LIST})
	target_link_libraries(test_net net)
	ADD_TEST(T_NET "./bin/test_net")

	set(TEST_OTHERS_LIST ${TEST_DIR}test_others.c)
	add_executable(test_others ${TEST_OTHERS_LIST})
	ADD_TEST(T_OTHERS "./bin/test_others")

endif(TEST)

##############################################################################
# installation
INSTALL(PROGRAMS build/bin/ichat DESTINATION /usr/local/azalea/bin)
INSTALL(PROGRAMS build/bin/client DESTINATION /usr/local/azalea/bin)
##############################################################################
# cmake configuration
cmake_minimum_required(VERSION 2.8)
