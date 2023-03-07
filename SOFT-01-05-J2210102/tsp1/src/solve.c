#include <stdio.h>
#include <stdlib.h>
#include "city.h"
#include "map.h"
#include "solve.h"
#include <assert.h>
double total_distance(const City *city, int n, int *route);
void swap_route(int i, int j, int *route);
void shuffle(int array[], int size) ;



double solve(const City *city, int n, int *route, int *visited, int *ansroute)
{
    // 以下はとりあえずダミー。ここに探索プログラムを実装する
    // 現状は町の番号順のルートを回っているだけ
    // 実際は再帰的に探索して、組み合わせが膨大になる。
    
    int i;
    int m = n - 1;
    int array[m];
 
    for (i = 0; i < m; i++) {
        array[i] = i + 1;
    }
    /*for (int i = 0; i < m; i++){
        printf("%d,", array[i]);
    }
    printf("\n");*/
    shuffle(array, m);
    /*for (int i = 0; i < m; i++){
        printf("%d,", array[i]);
    }
    printf("\n");*/
    route[0] = 0; // 循環した結果を避けるため、常に0番目からスタート
    visited[0] = 1;
    for (int i = 1 ; i < n ; i++){
        route[i] = array[i - 1];
    }
    

    
    // トータルの巡回距離を計算する
    // 実際には再帰の末尾で計算することになる
    /*double sum_d = 0;
    for (int i = 0 ; i < n ; i++){
	    const int c0 = route[i];
	    const int c1 = route[(i+1)%n]; // nは0に戻る
	    sum_d += distance(city[c0],city[c1]);
    }
    return sum_d;*/
    int flag = 0;
    int num = 0;
    int tmp_route[n];
    double tmp_distance = 0;
    double all_best = total_distance(city, n, ansroute);
    double best_score =  total_distance(city, n, route);
    double best_score1;
    double best_score2;
    while(1){

    for (int i = 1; i < n; i++){
        for (int j = i + 1; j < n; j++){
            for (int k = 0; k < n; k++){
                tmp_route[k] = route[k];
            }
            swap_route(i, j, tmp_route);
            tmp_distance = total_distance(city, n, tmp_route);
            if (tmp_distance < best_score){
                best_score = tmp_distance;
                for (int k = 0; k < n; k++){
                    route[k] = tmp_route[k];
                }
            }
        }
    }
    num++;
    /*for(int k = 0; k < n; k++){
    printf("%d,", route[k]);
}*/
    /*printf("\n");
    printf("%lf, %lf\n", best_score1, best_score2);*/
    if(num % 2 == 0){
        best_score1 = best_score;
    } 
    if(num % 2 == 1){
        best_score2 = best_score;
    }
    if(best_score1 == best_score2){
        flag++;
    }
    if(best_score1 != best_score2){
        flag = 0;
    }
    if(flag >= 5){
        if (all_best > best_score){
            all_best = best_score;
            for (int k = 0; k < n; k++){
                ansroute[k] = route[k];
            }
        }
        break;
    }
    }
    return all_best;
    //printf("\n");
}

    /*while(flag){
        for (int i = 1; i < n; i++){
            for (int j = 1; j < n; j++){
                swap_route(i, j, route);
                tmp_distance = total_distance(city, n, route);
                if (tmp_distance < best_score){
                    for (int k = 0; k < n; k++){
                        best_score = tmp_distance;
                        flag = 1;
                        if (best_score == total_distance(city, n, ans)){
                            flag = 0;
                        }
                        ans[k] = route[k];
                    }
                        
                    }
                }
            }
        }*/
    




double total_distance(const City *city, int n, int *route){
    double sum_d = 0;
    for (int i = 0 ; i < n ; i++){
        const int c0 = route[i];
        const int c1 = route[(i+1)%n]; // nは0に戻る
        sum_d += distance(city[c0],city[c1]);
    }
    return sum_d;
}

void swap_route(int i, int j, int *route){
    int tmp = route[i];
    route[i] = route[j];
    route[j] = tmp;
    return;
}

void shuffle(int array[], int n) {
    int i, j;
    int tmp;

    i = n - 1;

    while (i > 0) {
        
        j = rand() % (i + 1);


        tmp = array[j];
        array[j] = array[i];
        array[i] = tmp;


        i--;
    } 
}



