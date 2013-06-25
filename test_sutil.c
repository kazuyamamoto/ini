/**
 * @file test_sutil.c
 * @brief sutil のユニットテスト
 */

#include "PCUnit/PCUnit.h"
#include "sutil.h"
#include <stdlib.h>
#include <errno.h>

/* 引数 data が無いとき、エラーとなること */
static void test_sgetline_data_null(void)
{
	char* line;

	line = sgetline(NULL);
	PCU_ASSERT_PTR_NULL(line);
	PCU_ASSERT_EQUAL(EINVAL, errno);
}

/* 空文字列のとき、 NULL が返ること */
static void test_sgetline_empty(void)
{
	const char *data = "";
	char* line;

	line = sgetline(&data);
	PCU_ASSERT_PTR_NULL(line);
}


/* data が1行のとき、1行を取得し、'\0' が返ること */
static void test_sgetline_oneline(void)
{
	const char *data = "abc";
	char* line;

	line = sgetline(&data);
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("abc", line);
	free(line);

	PCU_ASSERT_EQUAL('\0', *data);

}

/* data が複数行のとき、各行を取得できること */
static void test_sgetline_multilines(void)
{
	const char *data = "abc\ndef\nghi";
	char* line;

	line = sgetline(&data);
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("abc", line);

	free(line);

	line = sgetline(&data);
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("def", line);

	free(line);

	line = sgetline(&data);
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("ghi", line);

	free(line);

	PCU_ASSERT_EQUAL('\0', *data);
}

/* data が改行のみのとき、空文字列が返ること */
static void test_sgetline_emptylines(void)
{
	const char *data = "\n\n\n";
	char* line;

	line = sgetline(&data);

	/* 1行め */
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("", line);

	free(line);
	line = sgetline(&data);

	/* 2行め */
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("", line);

	free(line);
	line = sgetline(&data);

	/* 3行め */
	PCU_ASSERT_PTR_NOT_NULL(line);
	PCU_ASSERT_STRING_EQUAL("", line);

	free(line);
	line = sgetline(&data);

	PCU_ASSERT_PTR_NULL(line);
}

static void test_sclone_null(void)
{
	char* clone = sclone(NULL);
	PCU_ASSERT_PTR_NULL(clone);
}

static void test_sclone_empty(void)
{
	char* clone = sclone("");
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("", clone);
	free(clone);
}

static void test_sclone(void)
{
	char* clone = sclone("abc");
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("abc", clone);
	free(clone);
}

static void test_snclone_null(void)
{
	char *clone = snclone(NULL, 1);
	PCU_ASSERT_PTR_NULL(clone);
}

static void test_snclone_empty(void)
{
	char* clone = snclone("", 0);
	PCU_ASSERT_PTR_NOT_NULL(clone);
	PCU_ASSERT_STRING_EQUAL("", clone);
	free(clone);
}

static void test_snclone(void)
{
	char* clone = snclone("abc", 2);
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
		PCU_TEST(test_sgetline_multilines),
		PCU_TEST(test_sgetline_emptylines),
		PCU_TEST(test_sclone_null),
		PCU_TEST(test_sclone_empty),
		PCU_TEST(test_sclone),
		PCU_TEST(test_snclone_null),
		PCU_TEST(test_snclone_empty),
		PCU_TEST(test_snclone),
	};
	static PCU_Suite suite = {
		"test_sutil", tests, sizeof tests / sizeof tests[0]
	};
	return &suite;
}

