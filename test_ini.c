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
	size_t errline;

	ini = ini_parse("[section]\nname=value", &errline);
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
	size_t errline;

	ini = ini_parse("[section]\nname1=value1\nname2=value2", &errline);
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
	const char *value1, *value2;
	size_t errline;

	ini = ini_parse("[section1]\nname1=value1\n[section2]\nname2=value2", &errline);

	value1 = ini_get(ini, "section1", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section2", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_empty_line(void)
{
	Ini *ini;
	const char *value1, *value2;
	size_t errline;

	ini = ini_parse("[section1]\nname1=value1\n[section2]\nname2=value2", &errline);

	ini_delete(ini);

	PCU_FAIL("TODO: implement");
}

PCU_Suite *test_ini_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_ini_get),
		PCU_TEST(test_ini_get_two_keys),
		PCU_TEST(test_ini_get_two_sections),
		PCU_TEST(test_ini_get_ignore_empty_line),
	};
	static PCU_Suite suite = {
		"test_ini", tests, sizeof tests / sizeof tests[0]
	};
	return &suite;
}
