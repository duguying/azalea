/// @file ichat.h
/// @brief Core head
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>

#define BUF_LEN 1000 //buffer length
#define ID_LEN 20 //username and etc name
#define PPB_LEN sizeof(Msg)/sizeof(char) //pipe buffer
#define PORT 6666 //port
#define ECF 0 //Empty Char Fill

typedef struct Msg{
	int to;
	int to_id;
	int from;// from user skt
	int from_id;
	char message[BUF_LEN];
} Msg;
