/**
 * @file section.c
 * @brief INI ファイルのセクション部分処理の実装。
 */

#include "section.h"
#include <stddef.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/* キー(あとでkey.hに移動) */
struct Key;
typedef struct Key Key;

struct Section {
	char *name;
	size_t nkeys;
	Key *keys;
};

char *parse_sectionname(const char *line)
{
	enum { BEFORE, OPEN, NAME, CLOSE, AFTER } state = BEFORE;
	char *sectionname = NULL;
	size_t num = 0;
	int i;

	assert(line);

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
				num = 1;
			} else if (state == NAME) {
				num++;
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

	if ((sectionname = malloc(num + 1)) == NULL) {
		return NULL;
	}
	memcpy(sectionname, line + 1, num);
	sectionname[num] = '\0';
	return sectionname;
}

/* セクションオブジェクトの初期化 */
Section *section_new(char *name)
{
	Section *section = malloc(sizeof *section);
	if (section == NULL) {
		return NULL;
	}

	section->name = name;
	section->nkeys = 0;
	section->keys = NULL;
	return section;
}

/* セクションオブジェクトの解放 */
void section_delete(Section *section)
{
	free(section->name);
	free(section);
	/* TODO: free keys */
}
