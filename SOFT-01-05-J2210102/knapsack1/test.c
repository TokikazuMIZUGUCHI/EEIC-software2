#include <stdio.h>
#include <stdlib.h>
//#include "item.h"

int main(int argc, char *argv[]){

    int number = atoi(argv[1]);
    int seed = atoi(argv[2]);


    FILE *fp = fopen("data/itemset", "wb");
    if ( fp == NULL ){
	fprintf(stderr," cannot open file.\n");
	return EXIT_FAILURE;  
    }

    srand(seed);
    double value[number];
    double weight[number];
    for (int i = 0 ; i < number ; i++){
        value[i] = 0.1 * (rand() % 200);
        weight[i] = 0.1 * (rand() % 200 + 1);
    }

    fwrite(&number, sizeof(int), 1, fp);
    // dポインタを先頭にからsize個のdoubleデータを出力
    fwrite(value,sizeof(double),number,fp);
    fwrite(weight,sizeof(double),number,fp);
    fclose(fp);
    //*list = (Itemset){.number = number, .item = item};
    //return list;
}
