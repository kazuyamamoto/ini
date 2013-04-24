/**
 * @file sutil.h
 * @brief 文字列処理ユーティリティヘッダ。
 */

#ifndef SUTIL_H
#define SUTIL_H

/**
 * @brief 1行を取得する。
 * @param[in] s 1行を取得したい文字列。
 * @param[out] next 取得した行の次のポインタが格納される。
 * @return 取得した1行。 \0 で終端する。
 * 不要になった場合 free() すること。
 * 取得に失敗した場合は NULL が返り errno が設定される。
 * next は変更されない。
 */
char *sgetline(const char* s, char** next);

#endif	/* SUTIL_H */
