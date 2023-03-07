#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define height 40
#define width 70
//#include "gol.h"


int cell[height][width];

//拡張子判別
bool check_extention_lif(const char *filename){
    const char *ext = strrchr(filename, '.');
    return strcmp(".lif", ext) == 0;
}

bool check_extention_rle(const char *filename){
    const char *ext = strrchr(filename, '.');
    return strcmp(".rle", ext) == 0;
}

void init_cell_rand(){
    int i, j;
    srand(time(NULL));

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cell[i][j] = 0;
        }
    }

    
    for (int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j ++) {
            if (rand() % 100 < 10) {
                cell[i][j] = 1;
            }
        }
    }
}

void init_cell_for_file(char *file) {
    FILE *fp;
    fp = fopen(file, "r");
    char *x = (char*)malloc(sizeof(char)*3);
    char *y = (char*)malloc(sizeof(char)*3);
    char str[257];
    char c;
    char d;

    if (fp == NULL) {
        printf("Error: can't open %s\n", file);
        exit(1);
    }

    else if (check_extention_lif(file)){
        fgets(str, 256, fp);
        while(fscanf(fp, "%s %s\n", x, y) != EOF){
            int x1, y1;
            x1 = atoi(x);
            y1 = atoi(y);
            cell[y1][x1] = 1;
        }
    }

    else if (check_extention_rle(file)){
        int num = 0;
        int i = 0;
        int j = 0;
        /*
        if ((d = fgetc(fp)) == '#'){
            fgets(str,256,fp);
        }*/
        fgets(str, 256, fp);
        while((c = fgetc(fp)) != EOF){
            if (c >= '0' && c <= '9'){
                int c1;
                c1 = c - '0';
                num = num * 10 + c1;
            }
            //*改行
            if (c == '$'){
                if (num == 0){
                    i += 1;
                    j = 0;
                    num = 0;
                }
                else{
                    i += num;
                    j = 0;
                    num = 0;
                }
            }
            //'b'
            if (c == 'b'){
                if (num == 0){
                    j += 1;
                    num = 0;
                }
                else{
                    j = j + num;
                    num = 0;
                }
            }
            //'o'
            if (c == 'o'){
                if (num == 0){
                    cell[i][j] = 1;
                    num = 0;
                    j += 1;
                }
                else {
                    int k = 0;
                    k = j + num;
                    for (; j < k; j++){
                        cell[i][j] = 1;
                    }
                    j = k;
                    num = 0;
                }
            }
            //'!'がきたらおわり
            if (c == '!'){
                break;
            }
            if (c == '\n') continue;
        }
        }
    fclose(fp);
    }



void print_cells(FILE *fp){
    int i, j;
    fprintf(fp, "+");
    for (int k = 0; k < width; k++){
          fprintf(fp, "-");
    }
    fprintf(fp, "+");
    fprintf(fp, "\n");
    for (i = 0; i < height; i++) {
        fprintf(fp, "|");
        for (j = 0; j < width; j++) {
            char c;
            if (cell[i][j] == 1){
                c = '#';
            }
            else{
                c = ' ';
            }
            fprintf(fp, "\x1b[31m");
            fputc(c, fp);
            fprintf(fp, "\x1b[0m");
        }
        fprintf(fp, "|");
        fputc('\n', fp);
    }
    fprintf(fp, "+");
    for (int k = 0; k < width; k++){
        fprintf(fp, "-");
    }
    fprintf(fp, "+");
    fprintf(fp, "\n");
    fflush(fp);
    
}

void print_cells_hund(FILE *fp_hund){
    int i, j;
    fprintf(fp_hund, "+");
    for (int k = 0; k < width; k++){
          fprintf(fp_hund, "-");
    }
    fprintf(fp_hund, "+");
    fprintf(fp_hund, "\n");
    for (i = 0; i < height; i++) {
        fprintf(fp_hund, "|");
        for (j = 0; j < width; j++) {
            char c;
            if (cell[i][j] == 1){
                c = '#';
            }
            else{
                c = ' ';
            }
            fputc(c, fp_hund);
        }
        fprintf(fp_hund, "|");
        fputc('\n', fp_hund);
    }
    fprintf(fp_hund, "+");
    for (int k = 0; k < width; k++){
        fprintf(fp_hund, "-");
    }
    fprintf(fp_hund, "+");
    fprintf(fp_hund, "\n");
    fflush(fp_hund);
}

int count_adjacent_cells(int i, int j)
{
    int alive = 0;
    int k, l;
    for (k = i - 1; k < i + 2; k++) {
        if (k < 0 || k >= height) continue;
        for (l = j - 1; l < j + 2; l++) {
            if (k == i && l == j) continue;
            if (l < 0 || l >= width) continue;
            alive += cell[k][l];
        }
    }
    return alive;
}

void update_cells(){
    int i = 0;
    int j = 0;
    int around = 0;
    int cell_next[height][width];
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cell_next[i][j] = 0;
            around = count_adjacent_cells(i, j);
            if (cell[i][j] == 1) {
                if (around == 2){
                    cell_next[i][j] = 1;
                }
                if (around == 3){
                    cell_next[i][j] = 1;
                }
                
            }
            else {
                if (around == 3) {
                    cell_next[i][j] = 1;
                }
            }
        }
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            cell[i][j] = cell_next[i][j];
        }
    }
}


int main(int argc, char **argv) {
    FILE *fp = stdout;
    int gen;
    FILE *fp_hund;
    char filepath[256];

    
    /* ファイルを引数にとるか、ない場合はデフォルトの初期値を使う */
    if ( argc > 2 ) {
        fprintf(stderr, "usage: %s [filename for init]\n", argv[0]);
        return EXIT_FAILURE;
    }
    else if (argc == 2) {
        init_cell_for_file(argv[1]);
    }
    else{
        init_cell_rand(); // デフォルトの初期値を使う
    }

    print_cells(fp); // 表示する
    sleep(1); // 1秒休止
    fprintf(fp,"\e[%dA",height+3);//height+3 の分、カーソルを上に戻す(壁2、表示部1)
    
    /* 世代を進める*/
    for (gen = 1 ;gen < 10000; gen++) {
        int count1 = 0;
        int count2 = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j ++) {
                count1 += cell[i][j];
                count2 += 1;
            }
        }
        
        printf("Generation = %d, Rate: %lf\n", gen, (double)count1 / (double)count2 );
        update_cells(); // セルを更新
        print_cells(fp);  // 表示する
        if (gen < 1000 && gen % 100 == 0){
            sprintf (filepath, "gen0%d.lif", gen);
            fp_hund = fopen(filepath, "a");
            print_cells_hund(fp_hund);
        }
        if (gen >= 1000 && gen % 100 == 0){
            sprintf (filepath, "gen%d.lif", gen);
            fp_hund = fopen(filepath, "a");
            print_cells_hund(fp_hund);
        }
        sleep(1); //1秒休止する
        fprintf(fp,"\e[%dA",height+3);//height+3 の分、カーソルを上に戻す(壁2、表示部1)
    }
    
    return EXIT_SUCCESS;
}