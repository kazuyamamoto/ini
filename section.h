/**
 * @file section.h
 * @breif INI ファイルのセクション処理のヘッダ。
 */

#ifndef SECTION_H
#define SECTION_H

/**
 * @brief INIファイルのセクション部分
 */
struct Section;
typedef struct Section Section;

/**
 * @brief セクション名を解釈して取得する。
 * 例えば "[abc]" を解釈して "abc" を取得する。
 * @param[in] line 1行の文字列
 * @return 解釈して取り出したセクション名。失敗時には NULL が返る。
 */
char *parse_sectionname(const char *line);

/**
 * @brief セクションオブジェクトを初期化する
 * @param[in] name セクション名
 * @return セクションオブジェクト。失敗時には NULL が返る。
 */
Section *section_new(const char *name);

/**
 * @brief セクションオブジェクトを解放する。
 * @param[in,out] section 解放するセクションオブジェクト。
 */
void section_delete(Section *section);

#endif /* SECTION_H */
