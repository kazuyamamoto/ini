/**
 * @file section.h
 * @breif INI ファイルのセクション処理のヘッダ。
 */

#ifndef SECTION_H
#define SECTION_H

#include "key.h"

/**
 * @brief INIファイルのセクション部分のオブジェクト
 */
struct Section;
typedef struct Section Section;

/**
 * @brief 文字列を解釈してセクションオブジェクト取得する。
 * 例えば "[abc]" を解釈して "abc" というセクション名のセクションオブジェクトを取得する。
 * @param[in] s 文字列
 * @return セクションオブジェクト。
 * 不要になった場合は section_delete() で解放すること。
 * 失敗した場合は　NULL　。
 */
Section *section_parse(const char *s);

/**
 * @brief セクションオブジェクトを解放する。
 * @param[in,out] section 解放するセクションオブジェクト
 */
void section_delete(Section *section);

/**
 * @brief セクション名を取得する。
 * @param[in] section セクション名を取得するセクションオブジェクト。
 * @return セクション名
 */
const char *section_name(const Section *section);

/**
 * @brief キーをセクションに追加する。
 * @param[in,out] section キーを追加するセクション
 * @param[in] key 追加するキー
 * @return 成功した場合は　0 、失敗した場合は 0 以外の値
 */
int section_add_key(Section *section, Key *key);

#endif /* SECTION_H */
