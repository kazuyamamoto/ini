INIファイルへのアクセス。

Cで書いています。

客先からサードパーティのライブラリ使用を禁止されているときに、
自前でライセンスを気にせずに使えるものを準備しておくことを目的にしています。

今のところ、

* INI ファイルの改行コードは LF しか対応していません。
* INI　ファイル内のコメントには対応していません。
* INI ファイルの書き込みには対応していません。(ダンプ的なものがいる？)
