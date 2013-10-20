#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(void){
	sqlite3 *db;
	sqlite3_open("test.db", &db);
	return 0;
}
