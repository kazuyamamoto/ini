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
 * @brief 空の Ini オブジェクトを作成する。
 * @return 空の Ini オブジェクト。失敗時は NULL を返す。
 */
Ini* ini_new(void);

/**
 * @brief INI ファイルを読んで、 Ini オブジェクトを作成する。
 * @param[in,out] file オープン済みの INI ファイル。
 * @return INI ファイルの内容を持つ Ini オブジェクト。失敗時は NULL を返す。
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
 * @brief 指定したセクションとキーから値を取得する。
 * @param[in] ini 値を取得したい Ini オブジェクト。
 * @param[in] section 値を取得したいセクション。
 * @param[in] name 値を取得したい名前。
 * @return セクションと名前で指定された値。
 * 不要になった場合は free() すること。
 * 存在しない場合は NULL 。
 */
char* ini_get(const Ini* ini, const char* section, const char* name);

/**
 * @brief 指定したセクションと名前で値を設定する。
 */
int ini_put(const Ini* ini, const char* section, const char* key, const char* value);

#endif	/* INI_H */
