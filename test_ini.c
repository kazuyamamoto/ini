/**
 * @file test_ini.c
 * @brief ini.c のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "ini.h"
#include <stddef.h>

static void test_ini_get(void)
{
	Ini *ini;
	const char *value;

	ini = ini_parse("[section]\nname=value");
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value = ini_get(ini, "section", "name");
	PCU_ASSERT_PTR_NOT_NULL(value);
	PCU_ASSERT_STRING_EQUAL("value", value);

	ini_delete(ini);
}

static void test_ini_get_two_keys(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("[section]\nname1=value1\nname2=value2");
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_two_sections(void)
{
	Ini *ini;
	const char *value1, *value2, *value3;

	ini = ini_parse("[section1]\nname1=value1\n[section2]\nname2=value2\nname3=value3");

	value1 = ini_get(ini, "section1", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section2", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	value3 = ini_get(ini, "section2", "name3");
	PCU_ASSERT_PTR_NOT_NULL(value3);
	PCU_ASSERT_STRING_EQUAL("value3", value3);

	ini_delete(ini);
}

static void test_ini_get_ignore_empty_line(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("\n[section]\n\nname1=value1\n\nname2=value2");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_comment_line(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse(";comment1\n[section]\n;comment2\nname1=value1\n;comment3\n");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

PCU_Suite *test_ini_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_ini_get),
		PCU_TEST(test_ini_get_two_keys),
		PCU_TEST(test_ini_get_two_sections),
		PCU_TEST(test_ini_get_ignore_empty_line),
		PCU_TEST(test_ini_get_ignore_comment_line),
	};
	static PCU_Suite suite = {
		"test_ini", tests, sizeof tests / sizeof tests[0]
	};
	return &suite;
}
