/**
 * @file sutil.h
 * @brief 文字列処理ユーティリティヘッダ。
 */

#ifndef SUTIL_H
#define SUTIL_H

#include <stddef.h>

/**
 * @brief 1行を取得する。
 * @param[in]  s    1行を取得したい文字列。
 * @param[out] next 取得した行の次の位置のポインタが格納される。
 * 次の行が無い場合、現在位置のポインタのままである。
 * @return 取得した1行。 \0 で終端する。
 * 行が改行のみのとき、空文字列が返る。
 * いずれも不要になった場合 free() すること。
 * 取得する文字列が無い場合は NULL が返る。
 * このとき next は変更されない。
 * 取得に失敗した場合は NULL が返り errno が設定される。
 * このとき next は変更されない。
 */
char *sgetline(const char* s, const char** next);

/**
 * @brief 文字列のクローンを作る。
 * @param[in] s 文字列
 * @return クローンされた文字列。
 * 不要になった場合 free() すること。
 * 失敗時には NULL が返り、　errno　が設定される。
 */
char* strclone(const char* s);

/**
 * @brief 文字列のクローンを作る。文字数を指定する。
 * @param[in] s 文字列
 * @param[in] len s からクローンを作る文字数。
 * @return クローンされた文字列。
 * 不要になった場合 free() すること。
 * 失敗時には NULL が返り、　errno　が設定される。
 */
char* strnclone(const char* s, size_t len);

#endif	/* SUTIL_H */
