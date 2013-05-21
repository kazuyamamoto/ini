/**
 * @file test_key.c
 * @brief key.c のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "key.h"
#include <stdlib.h>

void test_key_parse(void)
{
	Key *key = key_parse("Name=Value");
	PCU_ASSERT_PTR_NOT_NULL(key);
	PCU_ASSERT_STRING_EQUAL("Name", key_get_name(key));
	PCU_ASSERT_STRING_EQUAL("Value", key_get_value(key));
	key_delete(key);
}

void test_key_parse_null(void)
{
	Key *key = key_parse(NULL);
	PCU_ASSERT_PTR_NULL(key);
}

PCU_Suite *test_key_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_key_parse_null),
		PCU_TEST(test_key_parse),
	};
	static PCU_Suite suite = {
		"test_key", tests, sizeof tests / sizeof tests[0]
	};
	return &suite;
}
