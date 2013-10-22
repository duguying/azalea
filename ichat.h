/// @file ichat.h
/// @brief Core head
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>

#define BUF_LEN 1000 //buffer length
//#define PPB_LEN 1017 //pipe buffer length 1016+1 !TODO this should be sizeof(Msg)+1
#define PORT 6666 //port
#define ECF 0 //Empty Char Fill

typedef struct Msg{//10016
	int to;//4
	int to_id;//4
	int from;//4 from user skt
	int from_id;//4
	char message[BUF_LEN];//size 10000
} Msg;
