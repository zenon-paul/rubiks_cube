# rubik's cube solver / simulator

## このリポジトリの説明
* rubiks_cube_lib
  * ライブラリの本体とインクルードファイルが入っています。ライブラリの機能を使うためにはこれをダウンロードする必要があります。
* project
  * .cpp のファイルはソースファイルであり、機能を提供するための関数の実体が定義されています。.h のファイルはインクルードファイルです。
  また、demonstrartion.cpp は本ライブラリを使用したプログラムの例です。また、csvファイルとテキストファイルは、demonstrartion.cpp に
  よって読み込まれるファイルの一例です。
## 機能概要

本プログラムはルービックキューブを解きシミュレーションを実行するライブラリです。これは主に以下の機能を提供します。ルービックキューブの表示にはopenGLを使用しています。

* テキストファイルまたまcsvファイルからルービックキューブの状態を取り込み、その状態のルービックキューブに対し最適な解を与える。

* 3Dオブジェクトとしてルービックキューブを生成し、それに対し任意の操作を実行する。

## 準備

本プログラムの動作環境は以下の通りです。
* windows 10 / 11
* visual studio 2019
* nupengl.core.0.1.0.1/glm.0.9.9.800 を導入済み

### 具体的に、ダウンロードから使用までの流れを紹介します。

* runiks_cube_libを任意のフォルダー内にダウンロードしてください。
* visual studio を立ち上げプロジェクトを作成します。
* インクルードファイルの設定
  * ソリューションエクスプローラー> ヘッダーファイル> 追加> 既存の項目 からダウンロードしたrubiks_cube_lib\include\にある3つの
  ヘッダーファイルを指定します。
  * プロジェクト>　...のプロパティ> C/C++ > 全般 >追加のインクルードディレクトリ　にパスを指定します。
* ライブラリファイルの設定
  * プロジェクト>　...のプロパティ>　リンカー> 入力> 追加の依存ファイル　にダウンロードしたrubiks_cube_lib\lib\にあるライブラリファイルを
  指定します。
  * プロジェクト>　...のプロパティ> リンカー > 全般 >追加のライブラリディレクトリ　にパスを指定します。
* nupengl.core.0.1.0.1/glm.0.9.9.800 を導入します。（プロジェクト> NuGetパッケージの管理 から簡単に導入できます。）

## 関数一覧
