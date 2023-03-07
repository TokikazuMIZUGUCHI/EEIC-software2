#ifndef OPTIMIZE_FUNC_H
#define OPTIMIZE_FUNC_H
typedef struct
{
    double lati;      // location name
    double alt;     // altitude (km)
    double temp;    // temperature (centigrade)
} Sample;

int f_dimension();
double f_value(const double x[], Sample data[], int n);
void f_gradient(const double x[], double g[], Sample data[], int n);
int comp_alt(const void *n1, const void *n2);

#endif