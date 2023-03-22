# rubik's cube solver / simulator

## このリポジトリの説明
* rubiks_cube_lib
  * ライブラリの本体とインクルードファイルが入っています。ライブラリの機能を使うためにはこれをダウンロードする必要があります。
* project
  * .cpp のファイルはソースファイルであり、機能を提供するための関数の実体が定義されています。.h のファイルはインクルードファイルです。
  また、demonstrartion.cpp は本ライブラリを使用したプログラムの例です。また、csvファイルとテキストファイルは、demonstrartion.cpp に
  よって読み込まれるファイルの一例です。
## 機能概要

本プログラムはルービックキューブを解きシミュレーションを実行するライブラリです。これは主に以下の機能を提供します。

* テキストファイルまたまcsvファイルからルービックキューブの状態を取り込み、その状態のルービックキューブに対し最適な解を与える。

* 3Dオブジェクトとしてルービックキューブを生成し、それに対し任意の操作を実行する。

ルービックキューブの表示にはopenGLを使用しています。

## 準備

本ライブラリの動作環境は以下の通りです。
* windows 10 / 11
* visual studio 2019
* nupengl.core.0.1.0.1/glm.0.9.9.800 を導入済み

### 具体的に、ダウンロードから使用までの流れを紹介します。

* runiks_cube_libを任意のフォルダー内にダウンロードしてください。
* visual studio を立ち上げプロジェクトを作成します。
* インクルードファイルの設定
  * ソリューションエクスプローラー> ヘッダーファイル> 追加> 既存の項目 からダウンロードしたrubiks_cube_lib\include\にある3つの
  ヘッダーファイルを指定します
  * プロジェクト>　...のプロパティ> C/C++ > 全般 >追加のインクルードディレクトリ　にパスを指定します。
* ライブラリファイルの設定
  * プロジェクト>　...のプロパティ>　リンカー> 入力> 追加の依存ファイル　にダウンロードしたrubiks_cube_lib\lib\にあるライブラリファイルを
  指定します。
  * プロジェクト>　...のプロパティ> リンカー > 全般 >追加のライブラリディレクトリ　にパスを指定します。
* nupengl.core.0.1.0.1/glm.0.9.9.800 を導入します。（プロジェクト> NuGetパッケージの管理 から簡単に導入できます。）
## 使い方
ここでは大まかな使い方を説明します。
### ルービックキューブの生成
ルービックキューブを解くにしても、表示するにしても第一に実体を定義することが必要です。
```
d_state state;
```
これで実体を定義し、
```
init_cube_state(&state);
```
これでルービックキューブとして実体を登録します。
以後、
```
get_state_value_address();
```
で、登録した実体のアドレスを得ることができます。

しかし、この状態では、実体の中に有効な値が入っていないため、以下のようにして初期化します。
また、初期化の方法は3種類あります。
```
make_solved_state(get_state_value_address());
```
1. そろった状態のルービックキューブをつくります。
```
read_csv_file(&ss, "ファイル名");
```
2. csvファイルから、面の色の状態のデータを取り込み、その状態にあるルービックキューブをつくります。
```
make_solved_state(get_state_value_address());
read_text_file(&ss,"ファイル名");
```
3. そろった状態のルービックキューブを作った後、テキストファイルからルービックキューブに対する操作を読み込んでいます。そして、それらの操作によって崩されたルービックキューブをつくります。

＊csvファイル、テキストファイルの入力方式については、下で説明します。

### ルービックキューブを解くための準備
ルービックキューブに対して、解の探索を開始すると、その結果として解法の手数、操作のリストを得ることができます。
```
int m_c = 0;
init_motion_count(&m_c);
```
これは、手数を入れる変数を定義し、登録しています。
以後、
```
get_motion_count_address();
```
で、登録した実体のアドレスを得ることができます。

```
int m_l[BUFFER_SIZE] = { 0 };
init_motion_list(m_l);
```
これは、操作のリストとなる実体を定義し、登録しています。
以後、
```
get_motion_list_address();
```
で、登録した実体のアドレスを得ることができます。

変数とリストを登録しておくことで、解の探索終了後、勝手にデータがそこに入れられます。
```
init_motion();
init_transfer_table();
init_prune_table();
```
これは、探索アルゴリズムが内部的に使用するテーブルを生成しています。これらの処理は、探索開始前に一度だけ行えばよいものです。
```
search(*get_state_value_address());
```
探索開始です。

### ルービックキューブの表示/キーボード入力
ルービックキューブを3D空間上に生成するのに必要な情報は、ルービックキューブ生成時に定義したd_state型の実体と面の色に関する情報です。
```
double color[6][3] = {
		{0.0,1.0,0.0},
		{1.0,1.0,0.0},
		{0.0,0.5,1.0},
		{1.0,1.0,1.0},
		{1.0,0.5,0.0},
		{1.0,0.0,0.0}
	};
```
このような配列を作っておきます。
```
init_shuffled_cube(*get_state_value_address(), color);
init_corner(get_state_value_address());
init_edge(get_state_value_address());
init_axises();
```
```
init_shuffled_cube(*get_state_value_address(), color);
```
によって現在d_state型に入っているキューブの状態と、色のデータから3Dデータを生成し、
```
init_corner(get_state_value_address());
init_edge(get_state_value_address());
init_axises();
```
で座標などを設定しています。
```
graphic(argc, argv);
```
描画開始です。特にこの関数を呼び出すとプログラム終了までmain関数に戻れないため、気を付けてください。
またこの関数を呼ぶと、キーボードによるリアルタイムで様々な操作が可能になります。


## 目的別関数一覧

未完（まだまだ書きます。）


