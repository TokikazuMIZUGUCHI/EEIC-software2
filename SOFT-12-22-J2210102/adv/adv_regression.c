#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "optimize.h"
#include "func.h"

int main(const int argc, const char **argv){
    FILE *fp;
    fp = fopen("data.csv", "r");
    Sample data[100];
    int n = 0;
    char buff[1000];
    while (fgets(buff, 1000, fp) && n < 100) {
        char *p;
        buff[strlen(buff) - 1] = '\0';
        p = strtok(buff, ",");
        double lati = strtod(p, NULL);
        p = strtok(NULL, ",");
        double alt = strtod(p, NULL);
        p = strtok(NULL, "\0");
        double temp = strtod(p, NULL);
        data[n].lati = lati;
        data[n].alt = alt;
        data[n].temp = temp; 
        n++;
    }
    const double alpha = (argc == 2) ? atof(argv[1]) : 0.000001;
    const int dim = f_dimension();
    double *x = malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++) {
        x[i] = 0;
    }

    printf("alpha = %f\n", alpha);

    const double iter = optimize(alpha, dim, x,  f_gradient, *f_value, data, n);

    printf("number of iterations = %f\n", iter);
    printf("a: %f, b: %f c: %f\n", x[0], x[1], x[2]);
    FILE *fp_test;
    fp_test = fopen("test.csv", "r");
    Sample test[100];
    int m = 0;
    char buf[1000];
    while (fgets(buf, 1000, fp_test) && m < 100) {
        char *p;
        buf[strlen(buf) - 1] = '\0';
        p = strtok(buf, ",");
        double lati = strtod(p, NULL);
        p = strtok(NULL, ",");
        double alt = strtod(p, NULL);
        p = strtok(NULL, "\0");
        double temp = strtod(p, NULL);
        test[m].lati = lati;
        test[m].alt = alt;
        test[m].temp = temp; 
        m++;
    }
    double sum = 0;
    double avl = 0;
    for (int i; i < m; i++){
        sum +=  x[0] * test[i].lati + x[1] * test[i].alt + x[2];
    }
    avl = sum / m;
    sum = 0;
    double zansa = 0;
    double sqsum = 0;
    for (int j = 0; j < m; j++){
        zansa += pow((test[j].temp - (x[0] * test[j].lati + x[1] * test[j].alt + x[2])),2);
        sqsum += pow((test[j].temp - avl),2);
    }
    double R2 = 0;
    R2 = 1 - zansa / sqsum;

    free(x);
    printf("coefficient of determination: %f\n", R2); //0.924331

    int i;
    qsort(data, n, sizeof(Sample), comp_alt);
    qsort(test, m, sizeof(Sample), comp_alt);

    printf("+------------------------------------------------------+\n");
    printf("Sample data (n=%d)\n", n);
    for (i = 0; i < n; i++){
        printf("%9.4f | %9.4f | %9.4f\n", data[i].lati, data[i].alt, data[i].temp);
    }
    printf("+------------------------------------------------------+\n");
    printf("Test data (n=%d)\n", m);
    for (i = 0; i < m; i++){
        printf("%9.4f | %9.4f | %9.4f\n", test[i].lati, test[i].alt, test[i].temp);
    }

    return 0;
}