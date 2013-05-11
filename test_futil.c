#include "PCUnit/PCUnit.h"
#include "futil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


static void test_freadall(void)
{
	FILE* file;
	char* data;
	const char* expected = "abc\ndef\nghi\n\njkl\n";

	file = fopen("sample1.txt", "r");
	PCU_ASSERT_PTR_NOT_NULL(file);

	data = freadall(file);
	fclose(file);
	PCU_ASSERT_PTR_NOT_NULL(data);

	if (strlen(expected) != strlen(data)) {
		free(data);
		PCU_FAIL("Unexpected size.");
	}
	free(data);
}

static void test_freadall_file_null()
{
	void* data;

	data = freadall(NULL);
	PCU_ASSERT_PTR_NULL(data);
	PCU_ASSERT_EQUAL(EINVAL, errno);
}

static void test_freadall_empty()
{
	FILE* file;
	char* data;

	file = fopen("empty.txt", "r");
	PCU_ASSERT_PTR_NOT_NULL(file);

	data = freadall(file);
	fclose(file);

	PCU_ASSERT_PTR_NULL(data);
}

static void test_freadline()
{
	FILE* file;
	char* line;
	char* expect[] = {
		"abc", "def", "ghi", "", "jkl"
	};
	int i = 0;

	file = fopen("sample1.txt", "r");
	PCU_ASSERT_PTR_NOT_NULL(file);

	while ((line = freadline(file)) != NULL) {
		PCU_ASSERT_STRING_EQUAL(expect[i++], line);
		free(line);
	}
	fclose(file);
}

static void test_freadline_empty()
{
	FILE* file;

	file = fopen("empty.txt", "r");
	PCU_ASSERT_PTR_NOT_NULL(file);

	PCU_ASSERT_PTR_NULL(freadline(file));
	fclose(file);
}

PCU_Suite *test_futil_suite(void)
{
	static PCU_Test tests[] = {
		PCU_TEST(test_freadall),
		PCU_TEST(test_freadall_file_null),
		PCU_TEST(test_freadall_empty),
		PCU_TEST(test_freadline),
		PCU_TEST(test_freadline_empty),
	};
	static PCU_Suite suite = {
		"test_futil", tests, sizeof tests / sizeof tests[0], setup, teardown, initialize, cleanup
	};
	return &suite;
}

