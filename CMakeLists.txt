project(iChat)
set(SRC_LIST ichat.c)
add_executable(iChat ${SRC_LIST})
target_link_libraries(iChat pthread)
