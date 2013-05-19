/**
 * @file section.h
 * @breif INI ファイルのセクション処理のヘッダ。
 */

#ifndef SECTION_H
#define SECTION_H

/**
 * @brief INIファイルのセクション部分のオブジェクト
 */
struct Section;
typedef struct Section Section;

/**
 * @brief 文字列を解釈してセクションオブジェクト取得する。
 * 例えば "[abc]" を解釈して "abc" というセクション名のセクションオブジェクトを取得する。
 * @param[in] s 文字列
 * @return セクションオブジェクト。失敗時には NULL が返る。
 * 不要になった場合は section_delete() で解放すること。
 */
Section *section_parse(const char *s);

/**
 * @brief セクションオブジェクトを解放する。
 * @param[in,out] section 解放するセクションオブジェクト。
 */
void section_delete(Section *section);

/**
 * @brief セクション名を取得する。
 * @param[in] セクション名を取得するセクションオブジェクト。
 * @return セクション名
 */
const char *section_name(const Section *section);

#endif /* SECTION_H */
