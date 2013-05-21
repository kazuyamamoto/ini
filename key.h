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
 * @brief 文字列を解釈して、キーのオブジェクトを取得する。
 * @param[in] s 文字列
 * @return 解釈に成功した場合、キーのオブジェクトが返る。
 * 不要になったら key_delete() で解放すること。
 * 解釈に失敗した場合、 NULL が返る。
 */
Key *key_parse(const char *s);

/**
 * @brief キーオブジェクトを解放する。
 * @param[in,out] 解放されるキーオブジェクト
 */
void key_delete(Key *key);

/**
 * @brief 名前を取得する。
 * @param[in] key 名前を取得するキーオブジェクト
 * @return キーの名前部分。不要になっても free() しないこと。
 */
const char *key_get_name(const Key *key);

/**
 * @brief 値を取得する。
 * @param[in] key 値を取得するキーオブジェクト
 * @return キーの値部分。不要になっても free() しないこと。
 */
const char *key_get_value(const Key *key);

#endif /* KEY_H */
