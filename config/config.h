/// @file config.h
/// @brief configuration model head
/// @author Rex Lee duguying2008@gmail.com
/// @version 0.01
/// @date 2013-10-19
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/// @brief config_init config initial
///
/// @param config_file configuration file
///
/// @return 
int config_init(const char* config_file);

/// @brief config_get get the config value by key
///
/// @param conf config
/// @param key key
///
/// @return value
char* config_get(int conf, const char* key);

