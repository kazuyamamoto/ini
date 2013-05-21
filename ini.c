/**
 * @file ini.c
 * @brief INIファイルアクセス実装。
 */

#include "ini.h"
#include "sutil.h"
#include "section.h"
#include "key.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* INI オブジェクト */
struct Ini {
	size_t nsections;
	Section **sections;
};

/* Ini オブエジェクトにセクションオブジェクトを追加する */
static int ini_add_section(Ini *ini, Section *section)
{
	Section **tmp = realloc(ini->sections, sizeof(Section*) * (ini->nsections + 1));

	if (tmp == NULL) {
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

	for (i = 0; i < ini->nsections; i++) {
		if (strcmp(section_get_name(ini->sections[i]), section_name) == 0) {
			return ini->sections[i];
		}
	}

	return NULL;
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

Ini *ini_parse(const char *data, size_t *errline)
{
	Ini *ini;
	char *line;
	Section* section;
	const char *next;
	Key *key;

	if (data == NULL || errline == NULL) {
		return NULL;
	}

	if ((ini = ini_new()) == NULL) {
		return NULL;
	}

	/* セクションの解釈 */
	if ((line = sgetline(data, &next)) == NULL) {
		return ini;
	}

	section = section_parse(line);
	free(line);
	if (section == NULL) {
		goto ERROR_PROCESS;
	}

	/* キーの解釈 */
	data = next;
	if ((line = sgetline(data, &next)) == NULL) {
		section_delete(section);
		goto ERROR_PROCESS;
	}

	key = key_parse(line);
	free(line);
	if (key == NULL) {
		section_delete(section);
		goto ERROR_PROCESS;
	}

	if (section_add_key(section, key)) {
		// error
	}

	if (ini_add_section(ini, section)) {
		// error
	}

	return ini;

ERROR_PROCESS:
	ini_delete(ini);
	return NULL;
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
