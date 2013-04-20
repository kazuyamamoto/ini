/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "futil.h"
#include <stdlib.h>
#include <stdio.h>

struct Ini {
};

Ini* ini_new()
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}

	return ini;
}

Ini* ini_read(FILE* file)
{
	Ini* ini = ini_new();
	if (ini == NULL) {
		return NULL;
	}

	// TODO: file read.

	return ini;
}

void ini_delete(Ini* ini)
{
	free(ini);
}

const char* ini_get(const Ini* ini, const char* section, const char* key)
{
	return NULL;
}
