#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"
#include "item.h"
#include "search.h"

// main関数
// プログラム使用例: ./knapsack 10 20
//  10個の品物を設定し、キャパ20 でナップサック問題をとく

int main (int argc, char **argv)
{
    /* 引数処理: ユーザ入力が正しくない場合は使い方を標準エラーに表示して終了 */
    if (argc != 3){
	fprintf(stderr, "usage: %s <the number of items (int)> <max capacity (double)>\n",argv[0]);
	exit(1);
    }
    
    // 個数の上限はあらかじめ定めておく
    const int max_items = 100;
    

    
    // 乱数シードを1にして、初期化 (ここは変更可能)
    const double W = load_double(argv[2]);
    assert( W >= 0.0 );
    Itemset *items = load_itemset(argv[1]);
    int n = items->number;
    assert(n <= max_items);  // assert で止める
    assert(n > 0);           // 0以下も抑止する
    printf("max capacity: W = %.f, # of items: %d\n", W, n);
    print_itemset(items);
    
    printf("max capacity: W = %.f, # of items: %d\n",W, n);
    
    
    // ソルバーで解く
    double total = solve(items, W);
    
    // 表示する
    printf("----\nbest solution:\n");
    printf("value: %4.1f\n",total);
    
    free_itemset(items);
    return 0;
}
