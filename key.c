/**
 * @file key.c
 * @brief INIファイルのキー処理の実装。
 */

#include "key.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/* キーは名前と値のペア */
struct Key {
	char *name;
	char *value;
};

Key *key_parse(const char *s)
{
	enum { BEFORE, NAME, AFTER_NAME, EQUAL, AFTER_EQUAL, VALUE, AFTER } state = BEFORE;
	size_t name_pos, name_len = 0;
	size_t value_pos, value_len = 0;
	size_t i;
	Key *key;

	if (s == NULL) {
		return NULL;
	}

	/* 名前の始点と長さ、値の始点と長さを求める */
	for (i = 0; i < strlen(s); i++) {
		if (isalnum((int)s[i])) {
			if (state == BEFORE) {
				state = NAME;
				name_pos = i;
				name_len = 1;
			} else if (state == EQUAL || state == AFTER_EQUAL) {
				state = VALUE;
				value_pos = i;
				value_len = 1;
			} else if (state == NAME) {
				name_len++;
			} else if (state == VALUE) {
				value_len++;
			} else {
				return NULL;
			}
		} else if (isblank((int)s[i])) {
			if (state == NAME) {
				state = AFTER_NAME;
			} else if (state == EQUAL) {
				state = AFTER_EQUAL;
			} else if (state == VALUE) {
				state = AFTER;
			} else {
				return NULL;
			}
		} else if (s[i] == '=') {
			if (state == NAME || state == AFTER_NAME) {
				state = EQUAL;
			} else {
				return NULL;
			}
		}
	}

	/* 中途半端に終わっていないことを確認 */
	if (state != VALUE && state != AFTER)  {
		return NULL;
	}

	if ((key = malloc(sizeof *key)) == NULL) {
		return NULL;
	}

	/* 名前の割り当て */
	if ((key->name = malloc(name_len + 1)) == NULL) {
		key_delete(key);
		return NULL;
	}
	memcpy(key->name, s + name_pos, name_len);
	key->name[name_len] = '\0';

	/* 値の割り当て */
	if ((key->value = malloc(value_len + 1)) == NULL) {
		key_delete(key);
		return NULL;
	}
	memcpy(key->value, s + value_pos, value_len);
	key->value[value_len] = '\0';

	return key;
}

void key_delete(Key *key)
{
	if (key == NULL) {
		return;
	}

	if (key->name) {
		free(key->name);
	}

	if (key->value) {
		free(key->value);
	}

	free(key);
}

const char *key_name(const Key *key)
{
	return key->name;
}

const char *key_value(const Key *key)
{
	return key->value;
}
