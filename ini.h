/**
 * @file ini.h
 * @brief INIファイルアクセスヘッダ。
 */

#ifndef INI_H
#define INI_H

#include <stdio.h>

struct Ini;
typedef struct Ini Ini;

/**
 * @brief Ini オブジェクトを作成する。
 */
Ini* ini_new();

/**
 * @brief INI ファイルを読んで、 Ini オブジェクトを作成する。
 */
Ini* ini_read(FILE* file);

/**
 * @brief Ini オブジェクトに割り当てられたメモリを解放する。
 */
void ini_delete(Ini* ini);

/**
 * @brief Ini オブジェクトの内容をファイルに書き出す。
 */
int ini_write(const Ini* ini, FILE* file);

/**
 * @brief 指定したセクションとキーの値を取得する。
 */
const char* ini_get(const Ini* ini, const char* section, const char* key);

/**
 * @brief 指定したセクションとキーで値を設定する。
 */
int ini_put(const Ini* ini, const char* section, const char* key, const char* value);

#endif	/* INI_H */
