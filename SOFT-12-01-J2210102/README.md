
# ライフゲーム -Week1課題1,2,3 
 Week1の課題1,2,3を1つのファイル**mylife3.c**にまとめた。
 
# Features
以下の関数新たに用いた。

void init_cell_rand()  
* コマンドライン引数がなかった場合に生きているセルがおよそ10分の1となるようにする関数  

void init_cell_for_file(char *file)  
* ファイル名を指定して読み込む関数  

void print_cells(FILE *fp)  
void print_cells_hund(FILE *fp_hund) （100世代ごとの例外処理）   
* cell[n][m] = 1を'#'に cell[n][m] = 0 を' 'としてファイルに出力する関数   

int count_adjacent_cells(int i, int j)
* 着目するセルの周辺の生きたセルをカウントする関数

void update_cells()  
* ライフゲームのルールに基づいて2次元配列の状態を更新する

bool check_extention_rle(const char *filename)  
bool check_extention_lif(const char *filename)  
* 入力ファイルの拡張子を判別する関数


# Requirement
以下のようにinclude及びdefineする
 ```
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define height 40
#define width 70
 ```

 
# Usage

以下のようにコンパイルする
```bash
gcc -o mylifegame -Wall mylife3.c
```
そして以下のように実行する
```
./mylifegame gosperglidergun.lif
```
出力は以下である('#'の色は赤)
```
Generation = 2, Rate: 0.013929
+----------------------------------------------------------------------+
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                        #                                             |
|                       # #                                            |
|             ##       # ##          ##                                |
|            # #      ## ##          ##                                |
|  ##       #      ### # ##                                            |
|  ##       #  #  #  #  # #                                            |
|           #      ##    #                                             |
|            # #                                                       |
|             ##                                                       |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
|                                                                      |
+----------------------------------------------------------------------+
```

