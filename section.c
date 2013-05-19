/**
 * @file section.c
 * @brief INI ファイルのセクション部分処理の実装。
 */

#include "key.h"
#include "section.h"
#include "sutil.h"
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct Section {
	char *name;
	size_t nkeys;
	Key **keys;
};

char *parse_section_name(const char *line)
{
	enum { BEFORE, OPEN, NAME, CLOSE, AFTER } state = BEFORE;
	char *section_name = NULL;
	size_t len = 0, i;

	if (line == NULL) {
		return NULL;
	}

	for (i = 0; i < strlen(line); i++) {
		if (line[i] == '[') {
			if (state == BEFORE) {
				state = OPEN;
			} else {
				return NULL;
			}
		} else if (isalnum((int)line[i])) {
			if (state == OPEN) {
				state = NAME;
				len = 1;
			} else if (state == NAME) {
				len++;
			} else {
				return NULL;
			}
		} else if (line[i] == ']') {
			if (state == NAME) {
				state = AFTER;
			} else {
				return NULL;
			}
		} else {
			return NULL;
		}
	}

	/* セクション名の取り出し */
	if ((section_name = malloc(len + 1)) == NULL) {
		return NULL;
	}
	memcpy(section_name, line + 1, len);
	section_name[len] = '\0';
	return section_name;
}

Section *section_new(const char *name)
{
	size_t len;
	char *section_name;
	Section *section;

	if (name == NULL) {
		return NULL;
	}

	if ((len = strlen(name)) == 0) {
		return NULL;
	}

	if ((section_name = strclone(name)) == NULL) {
		return NULL;
	}

	if ((section = malloc(sizeof *section)) == NULL) {
		return NULL;
	}

	section->name = section_name;
	section->nkeys = 0;
	section->keys = NULL;

	return section;
}

void section_delete(Section *section)
{
	size_t i;

	free(section->name);
	for (i = 0; i < section->nkeys; i++) {
		key_delete(section->keys[i]);
	}
	free(section->keys);
	free(section);
}
