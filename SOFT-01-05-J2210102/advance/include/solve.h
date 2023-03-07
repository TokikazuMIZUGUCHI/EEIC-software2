#pragma once
#include "city.h"


double solve(const City *city, int n, int *route, int *visited, int *ansroute);
double total_distance(const City *city, int n, int *route);
void swap_route(int i, int j, int *route);
void shuffle(int array[], int size);
double simmulated_annealing(const City *city, int n, int *route, int *visited, int *ansroute);
//double genetic(const City *city, int n, int *route, int *visited);
//int exists(const int n, const int count, int array[]);
