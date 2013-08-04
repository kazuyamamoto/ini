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

static void test_ini_get_cr(void)
{
	Ini *ini;
	const char *value;

	ini = ini_parse("[section]\rname=value");
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value = ini_get(ini, "section", "name");
	PCU_ASSERT_PTR_NOT_NULL(value);
	PCU_ASSERT_STRING_EQUAL("value", value);

	ini_delete(ini);
}

static void test_ini_get_crlf(void)
{
	Ini *ini;
	const char *value;

	ini = ini_parse("[section]\r\nname=value");
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

static void test_ini_get_two_keys_cr(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("[section]\rname1=value1\rname2=value2");
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_two_keys_crlf(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("[section]\r\nname1=value1\r\nname2=value2");
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_two_keys_cr_lf_crlf_mix(void)
{
	Ini *ini;
	const char *value1, *value2, *value3;

	ini = ini_parse("[section]\rname1=value1\nname2=value2\r\nname3=value3");
	PCU_ASSERT_PTR_NOT_NULL(ini);

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	value3 = ini_get(ini, "section", "name3");
	PCU_ASSERT_PTR_NOT_NULL(value3);
	PCU_ASSERT_STRING_EQUAL("value3", value3);

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

static void test_ini_get_ignore_empty_line_cr(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("\r[section]\r\rname1=value1\r\rname2=value2");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_empty_line_crlf(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("\r\n[section]\r\n\r\nname1=value1\r\n\r\nname2=value2");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_spacetab_line(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse(" \t\n[section]\n \t\nname1=value1\n \t\nname2=value2 \t\n");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_spacetab_line_cr(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse(" \t\r[section]\r \t\rname1=value1\r \t\rname2=value2 \t\r");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_spacetab_line_crlf(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse(" \t\r\n[section]\r\n \t\r\nname1=value1\r\n \t\r\nname2=value2 \t\r\n");

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

	ini = ini_parse(" ;comment1\n[section]\n\t;comment2\nname1=value1\n;comment3\nname2=value2\n;comment4");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_comment_line_cr(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse(" ;comment1\r[section]\r\t;comment2\rname1=value1\r;comment3\rname2=value2\r;comment4");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

static void test_ini_get_ignore_comment_line_crlf(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse(" ;comment1\r\n[section]\r\n\t;comment2\r\nname1=value1\r\n;comment3\r\nname2=value2\r\n;comment4");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NOT_NULL(value2);
	PCU_ASSERT_STRING_EQUAL("value2", value2);

	ini_delete(ini);
}

/* 空行でもコメントでもないが、無効な行がある場合 */
static void test_ini_get_unknown_line_before_first_section(void)
{
	Ini *ini;
	const char *value;

	ini = ini_parse("abc");

	value = ini_get(ini, "section", "name");
	PCU_ASSERT_PTR_NULL(value);

	ini_delete(ini);
}

/* 空行でもコメントでもないが、無効な行がある場合。
 * 読めるところまでは読む。 */
static void test_ini_get_unknown_line_after_first_section(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("[section]\nname1=value1\nabc\nname2=value2");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NULL(value2);

	ini_delete(ini);
}

static void test_ini_get_unknown_line_after_first_section_cr(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("[section]\rname1=value1\rabc\rname2=value2");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NULL(value2);

	ini_delete(ini);
}

static void test_ini_get_unknown_line_after_first_section_crlf(void)
{
	Ini *ini;
	const char *value1, *value2;

	ini = ini_parse("[section]\r\nname1=value1\r\nabc\r\nname2=value2");

	value1 = ini_get(ini, "section", "name1");
	PCU_ASSERT_PTR_NOT_NULL(value1);
	PCU_ASSERT_STRING_EQUAL("value1", value1);

	value2 = ini_get(ini, "section", "name2");
	PCU_ASSERT_PTR_NULL(value2);

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
		PCU_TEST(test_ini_get_ignore_spacetab_line),
		PCU_TEST(test_ini_get_unknown_line_before_first_section),
		PCU_TEST(test_ini_get_unknown_line_after_first_section),
		PCU_TEST(test_ini_get_cr),
		PCU_TEST(test_ini_get_two_keys_cr),
		PCU_TEST(test_ini_get_ignore_empty_line_cr),
		PCU_TEST(test_ini_get_ignore_spacetab_line_cr),
		PCU_TEST(test_ini_get_ignore_comment_line_cr),
		PCU_TEST(test_ini_get_unknown_line_after_first_section_cr),
		PCU_TEST(test_ini_get_crlf),
		PCU_TEST(test_ini_get_two_keys_crlf),
		PCU_TEST(test_ini_get_two_keys_cr_lf_crlf_mix),
		PCU_TEST(test_ini_get_ignore_empty_line_crlf),
		PCU_TEST(test_ini_get_ignore_spacetab_line_crlf),
		PCU_TEST(test_ini_get_ignore_comment_line_crlf),
		PCU_TEST(test_ini_get_unknown_line_after_first_section_crlf),
	};
	static PCU_Suite suite = {
		"test_ini", tests, sizeof tests / sizeof tests[0]
	};
	return &suite;
}
