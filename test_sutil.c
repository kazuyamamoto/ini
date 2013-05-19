/**
 * @file test_sutil.c
 * @brief sutil のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "sutil.h"
#include <stdlib.h>
#include <errno.h>

static int initialize(void)
{
	return 0;
}

static int cleanup(void)
{
	return 0;
}

static int setup(void)
{
	return 0;
}

static int teardown(void)
{
	return 0;
}

/* 引数 next が無いとき、エラーとなること */
static void test_sgetline_next_null(void)
{
	const char *data = "abc";
	char* line;

	line = sgetline(data, NULL);

	PCU_ASSERT_PTR_NULL(line);
	PCU_ASSERT_EQUAL(EINVAL, errno);
}

/* 引数 data が無いとき、エラーとなること */
static void test_sgetline_data_null(void)
{
	const char *next;
	char* line;

	line = sgetline(NULL, &next);

	PCU_ASSERT_PTR_NULL(line);
	PCU_ASSERT_EQUAL(EINVAL, errno);
}

/* 空文字列のとき、 NULL が返ること */
static void test_sgetline_empty(void)
{
	const char *data = "";
	const char *next;
	char* line;

	line = sgetline(data, &next);

	PCU_ASSERT_PTR_NULL(line);
}

/* data が1行のとき、1行を取得し、'\0' が返ること */
static void test_sgetline_oneline(void)
{
	const char *data = "abc";
	const char *next;
	char* line;

	line = sgetline(data, &next);

	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("abc", line);
	PCU_ASSERT_EQUAL('\0', *next);

	free(line);
}

/* data が複数行のとき、各行を取得できること */
static void test_sgetline_multilines(void)
{
	const char *data = "abc\ndef\nghi";
	const char *next;
	char* line;

	line = sgetline(data, &next);

	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("abc", line);

	free(line);
	data = next;
	line = sgetline(data, &next);

	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("def", line);

	free(line);
	data = next;
	line = sgetline(data, &next);

	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("ghi", line);

	free(line);

	PCU_ASSERT_EQUAL('\0', *next);
}

/* data が改行のみのとき、空文字列が返ること */
static void test_sgetline_emptylines(void)
{
	const char *data = "\n\n\n";
	const char *next;
	char* line;

	line = sgetline(data, &next);

	/* 1行め */
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("", line);

	free(line);
	data = next;
	line = sgetline(data, &next);

	/* 2行め */
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("", line);

	free(line);
	data = next;
	line = sgetline(data, &next);

	/* 3行め */
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("", line);

	free(line);
	data = next;
	line = sgetline(data, &next);

	PCU_ASSERT_PTR_NULL(line);
}

static void test_strclone_null(void)
{
	char* clone = strclone(NULL);
	PCU_ASSERT_PTR_NULL(clone);
}

static void test_strclone_empty(void)
{
	char* clone = strclone("");
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("", clone);
	free(clone);
}

static void test_strclone(void)
{
	char* clone = strclone("abc");
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("abc", clone);
	free(clone);
}

static void test_strnclone_null(void)
{
	char *clone = strnclone(NULL, 1);
	PCU_ASSERT_PTR_NULL(clone);
}

static void test_strnclone_empty(void)
{
	char* clone = strnclone("", 0);
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("", clone);
	free(clone);
}

static void test_strnclone(void)
{
	char* clone = strnclone("abc", 2);
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("ab", clone);
	free(clone);
}

PCU_Suite *test_sutil_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_sgetline_oneline),
		PCU_TEST(test_sgetline_empty),
		PCU_TEST(test_sgetline_data_null),
		PCU_TEST(test_sgetline_next_null),
		PCU_TEST(test_sgetline_multilines),
		PCU_TEST(test_sgetline_emptylines),
		PCU_TEST(test_strclone_null),
		PCU_TEST(test_strclone_empty),
		PCU_TEST(test_strclone),
		PCU_TEST(test_strnclone_null),
		PCU_TEST(test_strnclone_empty),
		PCU_TEST(test_strnclone),
	};
	static PCU_Suite suite = {
		"test_sutil", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}

