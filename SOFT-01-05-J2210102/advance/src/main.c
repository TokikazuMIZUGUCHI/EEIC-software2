#include <stdio.h>
#include <stdlib.h>
#include <assert.h> // for assert()
#include <unistd.h> // for sleep()
#include <string.h> // for memset()
#include "city.h"
#include "map.h"
#include "solve.h"

int main(int argc, char**argv)
{
    // const による定数定義
    const int width = 70;
    const int height = 40;
    const int max_cities = 100;
    
    Map map = init_map(width, height);
    
    if (argc != 2){
	fprintf(stderr, "Usage: %s <city file>\n", argv[0]);
	exit(1);
    }
    int n = 1;
    City *city = load_cities(argv[1],&n);
    assert( n > 1 && n <= max_cities); // さすがに都市数100は厳しいので
    // 町の初期配置を表示
    plot_cities(map, city, n, NULL);
    sleep(1);

    // 訪れる順序を記録する配列を設定
    int *route = (int*)calloc(n, sizeof(int));
    int *ansroute = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++){
        ansroute[i] = i;
    }
    // 訪れた町を記録するフラグ
    int *visited = (int*)calloc(n, sizeof(int));
    int trial = 0; //初期配置の個数
    double one = 0;
    double two = 0;
    double three = 0;
    double four = 0;
    double five = 0;
    double ten = 0;
    double hund = 0;
    /*double twohund = 0;
    double threehund = 0;
    double fourhund = 0;
    double fivehund = 0;
    double thousand = 0;
    double fivethousand = 0;*/
    double e = 0;
    double d = simmulated_annealing(city,n,route,visited,ansroute); //初期配置一回目
    trial = 1;
    one = d;
    for (int i = 0; i < 99 ; i++){
        e = simmulated_annealing(city,n,route,visited, ansroute); //初期配置二回目以降
        trial ++;
        if (d > e){
            d = e;
        }
        //printf("%lf\n", d);

        
        if (trial == 2){
            two = d;
        }
        if (trial == 3){
            three = d;
        }
        if (trial == 4){
            four = d;
        }
        if (trial == 5){
            five = d;
        }
        if (trial == 10){
            ten = d;
        }
        if (trial == 100){
            hund = d;
        }
        /*
        if (trial == 200){
            twohund = d;
        }
        if (trial == 300){
            threehund = d;
        }
        if (trial == 400){
            fourhund = d;
        }
        if (trial == 500){
            fivehund = d;
        }
        if (trial == 1000){
            thousand = d;
        }
        if (trial == 5000){
            fivethousand = d;
        }*/
    }
    plot_cities(map, city, n, ansroute);
    printf("<Simulated Annealing>\n");
    printf("初期解1:  %f\n", one);
    printf("初期解2:  %f\n", two);
    printf("初期解3:  %f\n", three);
    printf("初期解4:  %f\n", four);
    printf("初期解5: %f\n", five);
    printf("初期解10: %f\n", ten);
    printf("初期解100: %f\n", hund);
    /*
    printf("初期解300: %f\n", threehund);
    printf("初期解400: %f\n", fourhund);
    printf("初期解500: %f\n", fivehund);
    printf("初期解1000: %f\n", thousand);
    printf("初期解5000: %f\n", fivethousand);*/
    printf("total distance = %f\n", d);
    printf("初期解 %d 個\n", trial);
    for (int i = 0 ; i < n ; i++){
	printf("%d -> ", ansroute[i]);
    }
    printf("0\n");

    // 動的確保した環境ではfreeをする
    free(route);
    free(ansroute);
    free(visited);
    free(city);

    /*int n2 = 1;
    City *city2 = load_cities(argv[1],&n2);
    assert( n2 > 1 && n2 <= max_cities); // さすがに都市数100は厳しいので

    // 町の初期配置を表示
    plot_cities(map, city, n2, NULL);
    sleep(1);

    // 訪れる順序を記録する配列を設定
    int *route2 = (int*)calloc(n2, sizeof(int));
    int *ansroute2 = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++){
        ansroute2[i] = i;
    }
    // 訪れた町を記録するフラグ
    int *visited2 = (int*)calloc(n2, sizeof(int));
    trial = 0; //初期配置の個数

    double e2 = 0;
    double d2 = solve(city2,n,route2,visited2, ansroute2); //初期配置一回目
    trial = 1;
    one = d2;
    for (int i = 0; i < 4999 ; i++){
        e2 = solve(city2,n,route2,visited2, ansroute2); //初期配置二回目以降
        trial ++;
        if (d2 > e2){
            d2 = e2;
        }
        //printf("%lf\n", d);

        
        if (trial == 5){
            five = d2;
        }
        if (trial == 10){
            ten = d2;
        }
        if (trial == 100){
            hund = d2;
        }
        if (trial == 200){
            twohund = d2;
        }
        if (trial == 300){
            threehund = d2;
        }
        if (trial == 400){
            fourhund = d2;
        }
        if (trial == 500){
            fivehund = d2;
        }
        if (trial == 1000){
            thousand = d2;
        }
        if (trial == 5000){
            fivethousand = d2;
        }
    }
    plot_cities(map, city, n, ansroute2);
    printf("<Hill Climbing>\n");
    printf("初期解1:  %f\n", one);
    printf("初期解5: %f\n", five);
    printf("初期解10: %f\n", ten);
    printf("初期解200: %f\n", twohund);
    printf("初期解300: %f\n", threehund);
    printf("初期解400: %f\n", fourhund);
    printf("初期解500: %f\n", fivehund);
    printf("初期解1000: %f\n", thousand);
    printf("初期解5000: %f\n", fivethousand);
    printf("total distance = %f\n", d2);
    printf("初期解 %d 個\n", trial);
    for (int i = 0 ; i < n ; i++){
	printf("%d -> ", ansroute2[i]);
    }
    printf("0\n");

    // 動的確保した環境ではfreeをする
    free(route2);
    free(ansroute2);
    free(visited2);
    free(city);
    
    */return 0;
}

