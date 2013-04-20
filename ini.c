/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "futil.h"
#include <stdlib.h>

struct Ini {
};

Ini* ini_new()
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}
	return NULL;
}

void ini_delete(Ini* ini)
{
	free(ini);
}
