#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>
void pow_mat(long mat1[][2], long num, long ans[][2]);
void mul_mat(long mat1[][2], long mat2[][2], long ans[][2]);

int main(int argc, char **argv) {
    int num; 
    num = atoi( argv[1] );
    assert(num <= 90);
    if (argc == 1){
        printf("Please specify a number\n");
    }

    if(argc > 2){
        printf("Please specify only one number\n");
    }

    if (argc == 2){
        if (num == 0){
            printf("fibo(0) = 0\n");
        }
        if (num == 1){
            printf("fibo(1) = 1\n");
        }
        if (num > 1){
            long tmp[2][2];
            tmp[0][0] = tmp[0][1] = tmp[1][0] = 1 , tmp[1][1] = 0;
            long ans[2][2];
            pow_mat(tmp, num - 1, ans);
            printf("fibo(%d) = %ld\n", num, ans[0][0]);
        }
        
    }
}

void mul_mat(long mat1[][2], long mat2[][2], long ans[][2]) {
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
        ans[i][j] = 0;
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        ans[i][j] += mat1[i][k] * mat2[k][j];
      }
    }
  }
  return;
}

void pow_mat(long mat1[][2], long num, long ans[][2]) {
  if ((num % 2 == 0) && (num != 2)) {
    long tmp[2][2];
    pow_mat(mat1, num / 2, tmp);
    pow_mat(tmp, 2, ans);
  }
  if ((num % 2 == 1) && (num != 1)) {
    long tmp1[2][2];
    long tmp2[2][2];
    pow_mat(mat1, num / 2, tmp1);
    pow_mat(tmp1, 2, tmp2);

    mul_mat(mat1, tmp2, ans);
  }
  if (num == 1) {
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ans[i][j] = mat1[i][j];
      }
    };
  }
  if (num == 2) {
    mul_mat(mat1, mat1, ans);
    return;
  }
  return;
}