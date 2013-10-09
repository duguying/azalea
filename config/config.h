#include <stdio.h>
#include <stdlib.h>

//config initial
int config_init(const char* config_file);

//get the config value by key
char* config_get(const char* key);

//set config
int config_set(const char* key, const char* value);
