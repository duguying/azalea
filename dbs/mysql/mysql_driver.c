#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

int mydrv_initial(char* link){
	//declare a connection
	MYSQL *conn;
	//create a connection
	conn = mysql_init(NULL);
	if (mysql_real_connect(conn, "127.0.0.1", "root", "lijun", NULL, 0, NULL, 0) == NULL) {
	      printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
	      exit(1);
  	}
	
	return 0;
}

/*
int mydrv_save(char* message){
}

int mydrv_get(char* key){
}
*/
