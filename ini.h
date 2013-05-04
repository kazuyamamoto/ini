/**
 * @file ini.h
 * @brief INIファイルアクセスヘッダ。
 */

#ifndef INI_H
#define INI_H

/**
 * @brief INI データを表す。
 */
struct Ini;
typedef struct Ini Ini;

/**
 * @brief 空の Ini オブジェクトを作成する。
 * @return 空の Ini オブジェクト。
 * 不要になった場合は ini_delete() でメモリを解放すること。
 * 失敗時は NULL を返し errno を設定する。
 */
Ini* ini_new(void);

/**
 * @brief INI データを解釈して、 Ini オブジェクトを作成する。
 * @param[in] data 解釈する対象となる INI データ。
 * @return INI ファイルの内容を持つ Ini オブジェクト。
 * 不要になった場合は ini_delete() でメモリを解放すること。
 * 失敗時は NULL を返し errno を設定する。
 */
Ini* ini_parse(const char* data);

/**
 * @brief Ini オブジェクトに割り当てられたメモリを解放する。
 */
void ini_delete(Ini* ini);

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

#endif	/* INI_H */
