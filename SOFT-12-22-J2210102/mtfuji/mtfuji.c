#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "optimize.h"
#include "func.h"

int main(const int argc, const char **argv){
    FILE *fp;
    fp = fopen("data.csv", "r");
    Sample data[100];
    int n = 0;
    char buff[1000];
    while (fgets(buff, 1000, fp) && n < 100) {
        char *name;
        char *p;
        buff[strlen(buff) - 1] = '\0';
        name = strtok(buff, ",");
        p = strtok(NULL, ",");
        double alt = strtod(p, NULL);
        p = strtok(NULL, "\0");
        double temp = strtod(p, NULL);
        data[n].alt = alt;
        data[n].temp = temp;
        strcpy(data[n].name, name); 
        n++;
    }
    const double alpha = (argc == 2) ? atof(argv[1]) : 0.0001;
    const int dim = f_dimension();
    double *x = malloc(dim * sizeof(double));
    for (int i = 0; i < dim; i++) {
        x[i] = 0;
    }

    printf("alpha = %f\n", alpha);

    const int iter = optimize(alpha, dim, x, f_gradient, f_value, data, n);

    printf("number of iterations = %d\n", iter);
    printf("a: %f, b: %f\n", x[0], x[1]);
    double Fuji = x[0] * 3.776 + x[1] ;   
    printf("The average temperature on top of Mt. Fuji in July is %lf ℃\n", Fuji);
    free(x);

    qsort(data, n, sizeof(Sample), comp_alt);
    printf("+------------------------------------------------------+\n");
    printf("Sample data (n=%d)\n", n);
    for (int i = 0; i < n; i++){
        printf("%15s | %8.4f | %8.4f\n", data[i].name, data[i].alt, data[i].temp);
    }

    return 0;
}