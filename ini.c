/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "sutil.h"
#include "section.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

/* INI */
struct Ini {
	size_t nsections;
	Section **sections;
};

static Ini *ini_add_section(Ini *ini, Section *section);

Ini* ini_new(void)
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}

	ini->nsections = 0;
	ini->sections = NULL;
	return ini;
}

Ini *ini_parse(const char* data, size_t* errline)
{
	Ini *ini;
	char *line;
	char *sectionname;
	Section* section;
	const char *next;

	if (data == NULL || errline == NULL) {
		return NULL;
	}

	if ((ini = ini_new()) == NULL) {
		return NULL;
	}

	if ((line = sgetline(data, &next)) == NULL) {
		return ini;
	}

	/* 最初はセクションが来る */
	if ((sectionname = parse_sectionname(line)) == NULL) {
		free(line);
		goto ERROR;
	}
	free(line);

	if ((section = section_new(sectionname)) == NULL) {
	   goto ERROR;
	}
	ini_add_section(ini, section);

	return ini;

ERROR:
	ini_delete(ini);
	return NULL;
}

void ini_delete(Ini *ini)
{
	int i;
	for (i = 0; i < ini->nsections; i++) {
		section_delete(ini->sections[i]);
	}
	free(ini);
}

char *ini_get(const Ini *ini, const char *section, const char *name)
{
	if (ini == NULL || section == NULL || name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	/* TODO: implement */

	return NULL;
}

/* Ini オブエジェクトにセクションオブジェクトを追加する */
static Ini* ini_add_section(Ini *ini, Section *section)
{
	if (ini->nsections) {
		Section **tmp;
		if ((tmp = realloc(ini->sections, sizeof(Section*) * (ini->nsections + 1))) == NULL) {
			return NULL;
		} else {
			ini->sections[ini->nsections] = section;
			ini->nsections++;
			return ini;
		}
	} else {
		if ((ini->sections = malloc(sizeof section)) == NULL) {
			return NULL;
		} else {
			ini->nsections = 1;
			ini->sections[0] = section;
			return ini;
		}
	}
}
