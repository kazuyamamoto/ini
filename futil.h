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
 * @return 読み取ったデータ。終端に'\0'を付加する。
 * 不要になったら free() すること。
 * 読み取るデータが無い場合 NULL を返す。
 * 異常終了の場合 NULL を返し、 errno を設定する。
 */
char* freadall(FILE* fp);

/**
 * @brief ファイルを1行(\nまで)読み取る。
 * @param[in,out] fp オープン済みのファイル。
 * @return "\0"で終端する1行分の文字列。
 * 行が改行のみ場合は空文字列。
 * どちらの場合も不要になったら free() すること。
 * ファイルの終端で読み取る場合 NULL を返す。
 * 異常終了の場合 NULL を返し、 errno を設定する。
 * ただしファイルアクセスのエラーが発生した場合、 errno を設定しない。
 * feof() 、 ferror() で確認すること。
 */
char* freadline(FILE* fp);

#endif /* FUTIL_H */
