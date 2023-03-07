#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp = fopen("helloworld.txt", "rb");
    float *x = (float*)malloc(sizeof(float)*4);
    if ( fp == NULL ){
	fprintf(stderr," cannot open file.\n");
	return EXIT_FAILURE;  
    }
    fread(x, 8, 4, fp) ;
    fclose(fp);
    for (int i = 0; i < 4; i++){
        printf("%.150f\n", x[i]);
    }
}