/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "sutil.h"
#include "cutil.h"
#include "section.h"
#include "key.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

/* INI オブジェクト */
struct Ini {
	size_t nsections;
	Section **sections;
};

/* Ini オブジェクトにセクションオブジェクトを追加する */
static int ini_add_section(Ini *ini, Section *section)
{
	Section **tmp;

	assert(ini != NULL);
	assert(section != NULL);

	if ((tmp = realloc(ini->sections, sizeof(Section*) * (ini->nsections + 1))) == NULL) {
		return -1;
	}

	ini->sections = tmp;
	ini->sections[ini->nsections] = section;
	ini->nsections++;

	return 0;
}

static Section *ini_search_section(const Ini *ini, const char* section_name)
{
	size_t i;

	assert(ini != NULL);
	assert(section_name != NULL);

	for (i = 0; i < ini->nsections; i++) {
		if (strcmp(section_get_name(ini->sections[i]), section_name) == 0) {
			return ini->sections[i];
		}
	}

	return NULL;
}

/* 空行かどうか */
static int isblankstr(const char* s)
{
	assert(s != NULL);

	while (*s != '\0') {
		if (!isspacetab(*s)) {
			return 0;
		}
		s++;
	}

	return 1;
}

Ini *ini_new(void)
{
	Ini* ini = malloc(sizeof *ini);
	if (ini == NULL) {
		return NULL;
	}

	ini->nsections = 0;
	ini->sections = NULL;
	return ini;
}

/* 最初のセクションの解釈 */
static Section *ini_parse_first_section(Ini *ini, const char **data)
{
	char *line = sgetline(data);
	Section *section = section_parse(line);
	free(line);

	if (section == NULL) {
		return NULL;
	}

	if (ini_add_section(ini, section)) {
		section_delete(section);
		return NULL;
	}

	return section;
}

Ini *ini_parse(const char *d)
{
	Ini *ini;
	char *line;
	Section *section;
	Key *key;
	const char *data = d;

	if (data == NULL)
		return NULL;

	if ((ini = ini_new()) == NULL)
		return NULL;

	if ((section = ini_parse_first_section(ini, &data)) == NULL)
		return ini;

	while ((line = sgetline(&data)) != NULL) {

		if ((key = key_parse(line)) != NULL) {
			free(line);
			if (section_add_key(section, key)) {
				key_delete(key);
				return ini;
			}
			continue;
		}

		if ((section = section_parse(line)) != NULL) {
			free(line);
			if (ini_add_section(ini, section)) {
				section_delete(section);
				return ini;
			}
			continue;
		}

		free(line);
	}

	return ini;
}

void ini_delete(Ini *ini)
{
	size_t i;

	if (ini == NULL) {
		return;
	}

	for (i = 0; i < ini->nsections; i++) {
		section_delete(ini->sections[i]);
	}
	free(ini);
}

const char *ini_get(const Ini *ini, const char *section_name, const char *key_name)
{
	Section *section;
	Key *key;

	if (ini == NULL || section_name == NULL || key_name == NULL) {
		errno = EINVAL;
		return NULL;
	}

	if ((section = ini_search_section(ini, section_name)) == NULL) {
		return NULL;
	}

	if ((key = section_search_key(section, key_name)) == NULL) {
		return NULL;
	}

	return key_get_value(key);
}
