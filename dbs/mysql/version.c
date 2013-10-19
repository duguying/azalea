/// @file version.c
/// @brief mysql version show
/// @author Rex Lee duguying2008@gmail.com
/// @version 
/// @date 2013-10-19
#include <my_global.h>
#include <mysql.h>

int main(int argc, char **argv)
{
  printf("MySQL client version: %s\n", mysql_get_client_info());
}

