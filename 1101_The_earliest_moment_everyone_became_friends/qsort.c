#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"





void print_2d_arr( int *arr[], int size1, int size2  ){
    for( int i = 0; i < size1;  i++ ){
        printf( "[");
        for( int j = 0; j < size2-1; j++ ){
            printf("%d, ", arr[i][j]);
        }
        printf("%d] ", arr[i][size2-1]);
    }
    printf("\n");
}


int getVal( int **arr, int idx ){
    return *(*(arr + idx));
}

void swap2d( int **a, int **b ){
    int *tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

int partition( int **arr, int low, int high ){
    int pivot = getVal(arr, high); 
    int i = low-1;
    for( int j = low; j <= high -1; j++ ){
        if( getVal( arr, j) <= pivot  ){
            i++;
            swap2d( (arr + i ), ( arr + j));
        }
    }
    swap2d( (arr + i +1 ), (arr + high));

    return i + 1 ;
}

void qsort_2d( int **array, int start, int end ){
    if( start < end){
        int partion_idx = partition( array, start, end );
        qsort_2d( array, start, partion_idx-1);
        qsort_2d( array, partion_idx+1, end );
    }
    return;
}



/* (QU ds )find without path compression*/
int find( int *parentArr, int a ){
    while( parentArr[a] != a){
        a = parentArr[a];
    }
    return a;
}

/*returns 1 if sets were merged otherwise 0*/
int unionq( int *parentArr, int *sizeArr, int a, int b){
    int parentof_a = find( parentArr ,a);
    int parentof_b = find( parentArr, b);
    if( parentof_a == parentof_b) return 0;
    /*size setA > setB --> Parent of A is now parent of B*/
    if(sizeArr[ parentof_a ] > sizeArr[parentof_b] ){
        parentArr[parentof_b] = parentof_a;
        sizeArr[parentof_b] += sizeArr[parentof_a];
    }else{
        parentArr[parentof_a] = parentof_b;
        sizeArr[parentof_a] += sizeArr[parentof_b];
    }
    return 1;
}



int earliestAcq(int** logs, int logsSize, int* logsColSize, int n){
    qsort_2d( logs, 0, logsSize-1 );
    
    /*makeset*/    
    int *parentArr = calloc( n , sizeof( int ) );
    int *sizeArr = calloc( n , sizeof( int ) ); 
    for( int i = 0; i < n; i++){
        parentArr[i] = i;
        sizeArr[i] = 1;
    }
    int j = 0;
    for( ; j < logsSize ; j++){
        n -= unionq( parentArr, sizeArr, logs[j][1], logs[j][2]  );
        if( n == 1){
            return logs[j][0];
        }
    }
    
    return -1;
}


/*
void swap( int *a, int *b ){
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
*/


/*int partition( int *arr, int low, int high ){
    int pivot = arr[high];
    int i = low-1;
    for( int j = low; j <= high -1; j++ ){
        if( arr[j] <= pivot  ){
            i++;
            swap( (arr + i ), ( arr + j));
        }
    }
    swap( (arr + i +1 ), (arr + high));

    return i + 1 ;
}*/

/*
void qsort( int *array, int start, int end ){
    if( start < end){
        int partion_idx = partition( array, start, end );
        qsort_2d( array, start, partion_idx-1);
        qsort_2d( array, partion_idx+1, end );
    }
}*/