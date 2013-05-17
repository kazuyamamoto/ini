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
 */
char *parse_sectionname(const char *line);

/**
 * @brief セクションオブジェクトを初期化する
 */
Section *section_new(char *name);

/**
 * @brief セクションオブジェクトを解放する。
 */
void section_delete(Section *section);

#endif /* SECTION_H */
