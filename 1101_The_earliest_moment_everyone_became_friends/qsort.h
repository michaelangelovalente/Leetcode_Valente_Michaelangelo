#ifndef QSORT
#define QSORT

void qsort_2d( int **array, int start, int end );

void printarr( int *arr, int size );

void print_2d_arr( int *arr[], int size1, int size2  );

void swap2d( int **a, int **b );

int partition( int **arr, int low, int high );

int getVal( int **arr, int idx );

#endif
