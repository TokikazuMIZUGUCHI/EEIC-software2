#include <stdio.h>

typedef struct student {
    int id;
    char name[100];
    int age;
    double height;
    double weight;
} Student;

typedef struct tagged_student1 {
    int id;
    char name[100];
    int age;
    double height;
    double weight;
    char tag;
} TStudent1;

typedef struct tagged_student2 {
    char tag;
    int id;
    char name[100];
    int age;
    double height;
    double weight;
} TStudent2;

int main (int argc, char**argv){
    Student s_begin;
    Student s1;
    TStudent1 s2;
    TStudent2 s3;
    TStudent2 s_end;
  
    /* 以下に各構造体の先頭アドレスを表示するプログラムを書く */
    /* Hint: printf で %p フォーマットを指定する*/
    /* 逆順に表示（s_end, s3, s2, s1, s_begin の順）*/
    
    // do_something!!
    
    /* 以下には各構造体のサイズをsizeof演算子で計算し、表示する */
    /* printf 表示には%zu を用いる*/
    
    // do_something!!

    printf("student: %p, %zu\n", &s1, sizeof(s1));
    printf("\n");
    printf("id: %p, %zu\n", &s1.id, sizeof(s1.id));
    printf("name: %p, %zu\n", &s1.name, sizeof(s1.name));
    printf("age: %p, %zu\n", &s1.age, sizeof(s1.age));
    printf("height: %p, %zu\n", &s1.height, sizeof(s1.height));
    printf("weight: %p, %zu\n", &s1.weight, sizeof(s1.weight));
    printf("\n");
    printf("tagged_student1: %p, %zu\n", &s2, sizeof(s2));
    printf("\n");
    printf("id: %p, %zu\n", &s2.id, sizeof(s2.id));
    printf("name: %p, %zu\n", &s2.name, sizeof(s2.name));
    printf("age: %p, %zu\n", &s2.age, sizeof(s2.age));
    printf("height: %p, %zu\n", &s2.height, sizeof(s2.height));
    printf("weight: %p, %zu\n", &s2.weight, sizeof(s2.weight));
    printf("tag: %p, %zu\n", &s2.tag, sizeof(s2.tag));
    printf("\n");
    printf("tagged_student2: %p, %zu\n", &s3, sizeof(s3));
    printf("\n");
    printf("tag: %p, %zu\n", &s3.tag, sizeof(s3.tag));
    printf("id: %p, %zu\n", &s3.id, sizeof(s3.id));
    printf("name: %p, %zu\n", &s3.name, sizeof(s3.name));
    printf("age: %p, %zu\n", &s3.age, sizeof(s3.age));
    printf("height: %p, %zu\n", &s3.height, sizeof(s3.height));
    printf("weight: %p, %zu\n", &s3.weight, sizeof(s3.weight));
    printf("\n");
    
    return 0;
}