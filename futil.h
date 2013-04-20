/**
 * @file futil.h
 * @brief ファイルアクセスユーティリティヘッダ。
 */

#ifndef FUTIL_H
#define FUTIL_H

#include <stdio.h>
#include <stddef.h>

/**
 * @brief ファイルを最後まで読み取る。
 * @param[in,out] fp   オープン済みのファイル。
 * @param[out]    size 読み取ったサイズ。異常終了の場合変更されない。
 * @return 読み取ったデータ。不要になったら free() すること。
 * 読み取るデータが無い場合 NULL を返す。
 * 異常終了の場合 NULL を返し、 errno を設定する。
 */
void* freadall(FILE* fp, size_t* size);

/**
 * @brief ファイルから1行読む。
 * @param[in,out] fp オープン済みのファイル。
 * @return "\0"で終端する1行分の文字列。
 * 行が改行のみ場合は空文字列。
 * どちらの場合も不要になったら free() すること。
 * ファイルの終端で読み取るデータが無い場合は NULL を返す。
 * 異常終了の場合 NULL を返し errno を設定する。
 * ただしファイルアクセスのエラーが発生した場合、 errno を設定しない。
 * ferror() で確認すること。
 */
char* freadline(FILE* fp);

#endif /* FUTIL_H */
