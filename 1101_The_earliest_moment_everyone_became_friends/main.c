#include <stdio.h>
#include <stdlib.h>
#include "qsort.h"


int main(){
    int logs[][3] = { {20190101,0,1}, { 20190104,3,4 } , { 20190107,2,3 },{ 20190211,1,5},{ 20190224,2,4 },{ 20190301,0,3 },{ 20190312,1,2},{ 20190322,4,5} };
    /*int logs[][] = */
    /*logs = [[],[],[],[],[],[],[],[]], n = 6*/
    
    int **logs_ptr;
    logs_ptr = malloc( (sizeof(logs)/sizeof(logs[0])) *  sizeof( int * )  );
    for( int i = 0; i < (sizeof( logs )/ sizeof( logs[0])); i++ ){ 
        int n = sizeof( logs[0] ) / sizeof( logs[0][0] );
        logs_ptr[i] = calloc(  n , sizeof( int ) );
        
        for( int j = 0 ; j < n; j++ ){
            logs_ptr[i][j] = logs[i][j];
        }
    }
    print_2d_arr( logs_ptr, (sizeof( logs ) / sizeof( logs[0])), 3 );
    
    
    printf("sorted: ");
    qsort_2d( logs_ptr, 0, (sizeof(logs)/sizeof(logs[0]))  - 1 );
    print_2d_arr( logs_ptr, (sizeof( logs ) / sizeof( logs[0])), 3 );
}