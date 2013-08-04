# 概要

INIファイルへのアクセスを行うコードです。
Cで書いています。

客先からサードパーティのライブラリ使用を禁止されているときに、
自前でライセンスを気にせずに使えるものを準備しておくことを目的にしています。

# 制限

今のところ下記の制限があります。

* INI ファイルの書き込みには対応していません。

# 使い方

cutil.c、cutil.h、ini.c、ini.h、key.c、key.h、section.c、section.h、sutil.c、sutil.hを
ご自分のプロジェクトに取り込んでビルドしてください。
簡単な使い方は下記のようになります。

	const char *data = "[section]\nname=value";
	Ini *ini = ini_parse(data);
	const char *value = ini_get(ini, "section", "name");
	puts(value);    /* value と表示される */
	ini_delete(ini);
