#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct condition {
    int width; // 見えている範囲の幅
    int height; // 見えている範囲の高さ
    double G; // 重力定数
    double dt; // シミュレーションの時間幅
    double cor; // 壁の反発係数
} Condition;

// 個々の物体を表す構造体
typedef struct object {
    double m;
    double x;
    double y;
    double prev_x;
    double prev_y; // 壁からの反発に使用
    double vx;
    double vy;
    double prev_vx;
    double prev_vy;
    int fusion;
} Object;

void my_plot_objects(Object objs[], const size_t numobj, const double t, const Condition cond){
    int i,j;
    int space[cond.width][cond.height];

    for (i = 0; i < cond.width; i++){
        for (j = 0; j < cond.height; j++){
            space[i][j] = 0;
        }
    }
    for (i = 0; i < numobj; i++) {
        if (objs[i].fusion == 1){
            int x = cond.width / 2 + objs[i].x;
            int y = cond.height / 2 + objs[i].y;
            if (x < 0 || x >= cond.width)  continue;
            if (y < 0 || y >= cond.height) continue;
            space[x][y] = 1;
        }
    }

    int x, y;
    printf("+");
    for (int j = 0; j < cond.width; j++){
        printf("-");
    }
    printf("+");
    printf("\n");
    for (y = 0; y < cond.height; y++) {
        printf("|");
        for (x = 0; x < cond.width; x++)
            if (space[x][y] == 1){
                printf("o");
            }
            else{
                printf(" ");
            }
        printf("|");
        printf("\n");
    }
    printf("+");
    for (int j = 0; j < cond.width; j++){
        printf("-");
    }
    printf("+");
    printf("\n");
    printf("t = %f                                  \n", t);
    for (i = 0; i < numobj; i++){
        printf("objs[%d].x = %f, objs[%d].y = %f\n", i, objs[i].x, i, objs[i].y);
    }
    
}

void my_update_positions(Object objs[], const size_t numobj, const Condition cond){
    for (int i = 0; i < numobj; i++){
        objs[i].prev_x = objs[i].x;
        objs[i].prev_y = objs[i].y;
        objs[i].x += objs[i].vx * cond.dt;
        objs[i].y += objs[i].vy * cond.dt;
    }
}

void my_update_velocities(Object objs[], const size_t numobj, const Condition cond){
    int i = 0;
    int j = 0;
    double a_x;
    double a_y;
    for (i = 0; i < numobj; i++){
        a_x = 0;
        a_y = 0;
        if (objs[i].fusion == 0){
            continue;
        }
        for (j = 0; j < numobj; j++){
            if (j == i || objs[j].fusion == 0){
                continue;
            }
            else{
                double xdistance = objs[j].x - objs[i].x;
                double ydistance = objs[j].y - objs[i].y;
                double distance = sqrt(xdistance*xdistance + ydistance*ydistance);
                if (distance < 2.0){
                    objs[i].vx = (objs[i].vx * objs[i].m + objs[j].vx * objs[j].m) / (objs[i].m + objs[j].m);
                    objs[i].vy = (objs[i].vy * objs[i].m + objs[j].vy * objs[j].m) / (objs[i].m + objs[j].m);
                    objs[j].fusion = 0;
                    objs[i].m = objs[i].m + objs[j].m;
                }
                a_x += cond.G * objs[j].m * xdistance / pow(distance, 3);
                a_y += cond.G * objs[j].m * ydistance / pow(distance, 3);
            }
        }
        objs[i].prev_vx = objs[i].vx;
        objs[i].prev_vy = objs[i].vy;
        objs[i].vx += a_x * cond.dt;
        objs[i].vy += a_y * cond.dt;
    }
}

void my_bounce(Object objs[], const size_t numobj, const Condition cond){
    for (int i = 0; i < numobj; i++){
        if (objs[i].m == 0){
            continue;
        }
        while(1){
        int flag1 = 0;
        

        if (objs[i].prev_y > -1 * cond.height/2){
            if (objs[i].y <= -1* cond.height /2){
                objs[i].y = fabs(objs[i].y + cond.height / 2) - cond.height / 2;
                objs[i].vy = -1*cond.cor * objs[i].prev_vy;
                flag1 = 1;
            }
        }
        else if (objs[i].prev_y < -1 * cond.height/2){
            if (objs[i].y >= -1 * cond.height /2){
                objs[i].y = - fabs(objs[i].y + cond.height / 2) - cond.height / 2;
                objs[i].vy = -1*cond.cor * objs[i].prev_vy;
                flag1 = 1;
            }
        }
        if (objs[i].prev_y >= cond.height/2){
            if (objs[i].y < cond.height /2){
                objs[i].y = fabs(objs[i].y - cond.height / 2) + cond.height / 2;
                objs[i].vy = -1*cond.cor * objs[i].prev_vy;
                flag1 = 1;
            }
        }
        else if (objs[i].prev_y < cond.height/2){
            if (objs[i].y >= cond.height /2){
                objs[i].y = -1 * fabs(objs[i].y - cond.height / 2) + cond.height / 2;
                objs[i].vy = -1*cond.cor * objs[i].prev_vy;
                flag1 = 1;
            }
        }
        else{

        }
        
        if (flag1 == 0){
            break;
        }
        }

        while(1){
        int flag2 = 0;
        if (objs[i].prev_x >= -1 * cond.width/2){
            if (objs[i].x < -1 * cond.width /2){
                objs[i].x = fabs(objs[i].x + cond.width / 2) - cond.width / 2;
                objs[i].vx = -1*cond.cor * objs[i].prev_vx;
                flag2 = 1;
            }
        }
        else if (objs[i].prev_x< -1 * cond.width/2){
            if (objs[i]. x>= -1 * cond.width /2){
                objs[i].x = - fabs(objs[i].x + cond.width / 2) - cond.width / 2;
                objs[i].vx = -1*cond.cor * objs[i].prev_vx;
                flag2 = 1;
            }
        }
        if (objs[i].prev_x >= cond.width/2){
            if (objs[i].x < cond.width /2){
                objs[i].x = fabs(objs[i].x - cond.width / 2) + cond.width / 2;
                objs[i].vx = -1*cond.cor * objs[i].prev_vx;
                flag2 = 1;
            }
        }
        else if (objs[i].prev_x < cond.width/2){
            if (objs[i].x >= cond.width /2){
                objs[i].x = -1 * fabs(objs[i].x - cond.width / 2) + cond.width / 2;
                objs[i].vx = -1*cond.cor * objs[i].prev_vx;
                flag2 = 1;
            }
        }

        if (flag2 == 0)
            break;
        }

        }

    }  

int main(int argc, char **argv) {
    const Condition cond =
        {
            .width  = 75,
            .height = 40,
            .G = 1.0,
            .dt = 1.0,
            .cor = 0.8
        };
    
    size_t objnum = 3;
    Object objects[objnum];
    
    // objects[1] は巨大な物体を画面外に... 地球のようなものを想定
    objects[0] = (Object){ .m = 60.0, .x = 0, .y = -19.9, .vx = 2.0, .vy = 2.0, .prev_vx = 2.0, .prev_vy = 2.0, .fusion = 1};
    objects[1] = (Object){ .m = 100000.0, .x = 0, .y = 10000.0, .vx = 0.0, .vy = 0.0, .prev_vx = 0.0, .prev_vy = 0.0, .fusion = 1};
    objects[2] = (Object){ .m = 60.0, .x = 10, .y = -19.9, .vx = 2.0, .vy = 2.0, .prev_vx = 2.0, .prev_vy = 2.0, .fusion = 1};
    // シミュレーション. ループは整数で回しつつ、実数時間も更新する
    const double stop_time = 400;
    double t = 0;
    for (size_t i = 0 ; t <= stop_time ; i++){
        t = i * cond.dt;
        my_update_velocities(objects, objnum, cond);
        my_update_positions(objects, objnum, cond);
        my_bounce(objects, objnum, cond); // 壁があると仮定した場合に壁を跨いでいたら反射させる
        
        // 表示の座標系は width/2, height/2 のピクセル位置が原点となるようにする
        my_plot_objects(objects, objnum, t, cond);
        
        usleep(200 * 10000); // 200 x 1000us = 200 ms ずつ停止
        printf("\e[%dA", cond.height+3);// 壁とパラメータ表示分で3行
    }
    return EXIT_SUCCESS;
}

// 実習: 以下に my_ で始まる関数を実装する
// 最終的に phisics2.h 内の事前に用意された関数プロトタイプをコメントアウト