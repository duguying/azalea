message("===    Build Tests    ===")

#build the tests

set(CONFIG_TEST 
	${TEST_DIR}test_conf.c
	${CONF_LIST}
)
add_executable(test_conf ${CONFIG_TEST})
target_link_libraries(test_conf core)
ADD_TEST(T_CONF "./bin/test_conf")

set(LOG_TEST 
	${TEST_DIR}test_log.c
	${LOG_LIST}
)
add_executable(test_log ${LOG_TEST})
target_link_libraries(test_log core)
ADD_TEST(T_LOG "./bin/test_log")

set(HASH_LIST ${TEST_DIR}test_hashtable.c)
add_executable(test_hashtable ${HASH_LIST})
target_link_libraries(test_hashtable apis)
ADD_TEST(T_HT "./bin/test_hashtable")

set(TEST_STACK_LIST ${TEST_DIR}test_stack.c)
add_executable(test_stack ${TEST_STACK_LIST})
target_link_libraries(test_stack apis)
ADD_TEST(T_STACK "./bin/test_stack")

set(TEST_POOL_LIST ${TEST_DIR}test_pool.c)
add_executable(test_pool ${TEST_POOL_LIST})
target_link_libraries(test_pool core apis)
ADD_TEST(T_POOL "./bin/test_pool")

set(TEST_PTH_LIST ${TEST_DIR}test_pth.c)
add_executable(test_pth ${TEST_PTH_LIST})
target_link_libraries(test_pth apis)
ADD_TEST(T_PTH "./bin/test_pth")

set(TEST_PTH_LIST ${TEST_DIR}test_file.c)
add_executable(test_file ${TEST_PTH_LIST})
target_link_libraries(test_file apis)
ADD_TEST(T_FILE "./bin/test_file")

set(TEST_SOCK_LIST ${TEST_DIR}test_sock.c)
add_executable(test_sock ${TEST_SOCK_LIST})
target_link_libraries(test_sock apis)
ADD_TEST(T_SOCK "./bin/test_sock")

set(TEST_NET_LIST ${TEST_DIR}test_net.c)
add_executable(test_net ${TEST_NET_LIST})
target_link_libraries(test_net core apis)
ADD_TEST(T_NET "./bin/test_net")

set(TEST_OTHERS_LIST ${TEST_DIR}test_others.c)
add_executable(test_others ${TEST_OTHERS_LIST})
ADD_TEST(T_OTHERS "./bin/test_others")


