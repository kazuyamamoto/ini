/**
 * @file key.h
 * @brief INI ファイルのキー部分の処理のヘッダ
 */

#ifndef KEY_H
#define KEY_H

/** キーオブジェクト */
struct Key;
typedef struct Key Key;

/**
 * @brief キーとして解釈する。
 * @param[in] line 文字列
 * @return 解釈に成功した場合、キーのオブジェクトが返る。
 * 不要になったら key_delete() で解放すること。
 * 解釈に失敗した場合、 NULL が返る。
 */
Key *key_parse(const char *line);

/**
 * @brief キーオブジェクトを解放する。
 * @param[in,out] 解放されるキーオブジェクト
 */
void key_delete(Key *key);

/**
 * @brief 名前を取得する。
 */
const char *key_name(const Key *key);

/**
 * @brief 値を取得する。
 */
const char *key_value(const Key *key);

#endif /* KEY_H */
