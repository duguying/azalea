project(Azalea)

# set(NDK true)
# set compilers
# SET(CMAKE_C_COMPILER gcc)

############################################################
# gdb Debug support
set(TEST true)
set(CMAKE_BUILD_TYPE "Debug")

if(UNIX)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -ggdb")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -s -DNDEBUG")
elseif(WIN32)
	add_definitions("-D_CRT_SECURE_NO_DEPRECATE")
endif(UNIX)

# root directory
set(SRC_DIR "src/")
set(TEST_DIR "tests/")
# output directory
set(EXECUTABLE_OUTPUT_PATH bin)
set(LIBRARY_OUTPUT_PATH lib)

# show log on screen
add_definitions(-D_SCR_LOG_)
link_directories("${PROJECT_BINARY_DIR}/lib")
include_directories("src")

#############################################################
message("===    Build Core    ===")
# main excutable
if(COMMAND cmake_policy)
	cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

set(SRC_LIST ${SRC_DIR}/core/ichat.c)
# add_executable(ichat ${SRC_LIST})
# target_link_libraries(ichat dl apis net pool)

#############################################################
# APIS
message("===    Build APIS Linrary    ===")

if(UNIX)
	set(
		APIS_LIST
		${SRC_DIR}/apis/thread.c
		${SRC_DIR}/apis/sock.c
		${SRC_DIR}/apis/process.c
		${SRC_DIR}/apis/file.c
		${SRC_DIR}/apis/ds.c
		${SRC_DIR}/apis/hashtable.c 
		${SRC_DIR}/apis/stack.c
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
		${SRC_DIR}/apis/file.c
		${SRC_DIR}/apis/ds.c
		${SRC_DIR}/apis/hashtable.c 
		${SRC_DIR}/apis/stack.c
	)
	add_library(apis STATIC ${APIS_LIST})
	target_link_libraries(apis ws2_32)
endif(UNIX)
#############################################################

# client
if(UNIX)
	set(CLIENT_LIST ${SRC_DIR}/client/client.c)
	add_executable(client ${CLIENT_LIST})
	target_link_libraries(client apis net)
elseif(WIN32)
	set(CLIENT_LIST ${SRC_DIR}/client/client.c)
	add_executable(client ${CLIENT_LIST})
	target_link_libraries(client apis net)
endif(UNIX)
#############################################################

#config library
set(CONF_LIST ${SRC_DIR}/core/config.c)
#log library
set(LOG_LIST ${SRC_DIR}/core/log.c)

#create-master-and-worker-process library
set(PROCWM_LIST ${SRC_DIR}/process/procinit.c)
add_library(procinit STATIC ${PROCWM_LIST})
target_link_libraries(procinit apis)

#pool library
if(UNIX)
	set(POOL_LIST 
		${SRC_DIR}/pool/pool.c
	)
	add_library(pool STATIC ${POOL_LIST})
	target_link_libraries(pool net)
elseif(WIN32)
	set(POOL_LIST 
		${SRC_DIR}/pool/pool.c
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
		${SRC_DIR}/net/message.c
	)
	add_library(net STATIC ${NET_LIST})
	target_link_libraries(net apis)
elseif(WIN32)
	set(NET_LIST 
		${SRC_DIR}/net/message.c
	)
	add_library(net STATIC ${NET_LIST})
	target_link_libraries(net apis)
endif(UNIX)

##############################################################################

if(TEST)
	ENABLE_TESTING()
	include(tests/CMakeLists.txt)
endif(TEST)

##############################################################################
# installation
INSTALL(PROGRAMS build/bin/ichat DESTINATION /usr/local/azalea/bin)
INSTALL(PROGRAMS build/bin/client DESTINATION /usr/local/azalea/bin)
##############################################################################
# cmake configuration
cmake_minimum_required(VERSION 2.8)
