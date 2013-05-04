/**
 * @file sutil.h
 * @brief 文字列処理ユーティリティヘッダ。
 */

#ifndef SUTIL_H
#define SUTIL_H

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

#endif	/* SUTIL_H */
