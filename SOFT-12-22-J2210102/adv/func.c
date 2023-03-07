#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "func.h"

int f_dimension()
{
    return 3;
}

double f_value(const double x[], Sample data[], int n){   
    double E = 0;
    for (int i = 0; i < n; i ++) {
        E += pow((data[i].temp - (x[0] * data[i].lati + x[1] * data[i].alt + x[2])), 2);
    }
    return E;
}

void f_gradient(const double x[], double g[], Sample data[], int n){   
    g[0] = 0;
    g[1] = 0;
    g[2] = 0;
    for (int i = 0; i < n; i ++) {
        g[0] += -2 * (data[i].temp - (x[0] * data[i].lati + x[1] * data[i].alt + x[2]));
        g[1] += -2 * (data[i].temp - (x[0] * data[i].lati + x[1] * data[i].alt + x[2])) * data[i].alt;
        g[2] += -2 * (data[i].temp - (x[0] * data[i].lati + x[1] * data[i].alt + x[2])) * data[i].temp;
    }
}

int comp_alt(const void *n1, const void *n2){
    if (((Sample *)n1) -> alt > ((Sample *)n2) -> alt ){
      return -1;
    }
    else if (((Sample *)n1) -> alt < ((Sample *)n2) -> alt ){
      return 1;
    }
    else{
      return 0;
    }
}

