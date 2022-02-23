#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

typedef struct array{
    int *A;
    int maxSize;
    int currSize;
}Array;

Array *new_array( int size ){
    struct array *dynamicA = calloc( 1, sizeof( struct array));
    dynamicA->A = calloc( size, sizeof( int ) );
    dynamicA->maxSize = size;
    dynamicA->currSize = 0;
}


void append( struct array *dynamicA, int n){
    if( dynamicA->currSize >= dynamicA->maxSize ){
        dynamicA->maxSize *= 2;
        dynamicA->A = realloc( dynamicA->A, sizeof(int) * dynamicA->maxSize );
    }
    dynamicA->A[dynamicA->currSize++] = n;
    return;
}


int get( struct array *dynA, int idx ){
    return dynA->A[idx];
}

Array *copy( Array *array ){
    Array *new = new_array( array->currSize );
    for( int i = 0; i < array->currSize; i++){
        new[i] = array[i];
    }
    return new;
}

int pop( Array *arr ){
    arr->currSize--;
    return arr->A[arr->currSize];
}
void printArr( Array *array ){
    for(int i = 0; i < array->currSize; i++){
        printf("[%d]", get(array, i));
    }
    putchar('\n');
}


void dfs( int **graph, int numberOfadjVert, Array *curr, int start, int end, Array **result, int *maxSizeResults, int *currSizeResults ){
    for( int i = 0; i < numberOfadjVert; i++){
        int throw;
        /*start from graph[start][0...n-1]*/
        if( graph[start-1][i] == end ){
            Array *tmp_cpy = copy( curr );
            append( tmp_cpy, graph[start-1][i]);
            if( *currSizeResults >= *maxSizeResults  ){
                (*currSizeResults) *= 2;
                result = realloc( result,  (*currSizeResults) * sizeof( Array * ) );
            }
            result[ (*currSizeResults)++ ] = tmp_cpy;
        }else{
            append( curr, graph[start-1][i]);
            dfs( graph, numberOfadjVert, curr, graph[start-1][i], end, result, maxSizeResults, currSizeResults );
            throw = pop( curr );
        }
    }
    return;    
}


Array** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes){
    int maxSizeResults = 10;
    int currResultsSize = 0;
    Array **ret = calloc( maxSizeResults, sizeof( Array *) );
    Array *curr = new_array( maxSizeResults );
    append( curr, 0);
    dfs( graph, graphSize, curr, 1, graphSize-1, ret, &maxSizeResults, &currResultsSize );
    return ret;
}

/*
*graphColSize: 2
* returnSize: 0
** returnColumnSizes: Cannot access memory at address 0x0
Local Variables
graph: 0x603000000010
graphSize: 4
graphColSize: 0x602000000010
returnSize: 0x7ffc20d79910
returnColumnSizes: 0x7ffc20d79a10
*/

int main(){
    /*[[4,3,1],[3,2,4],[3],[4],[]]*/
    int arr[][3] = {{4,3,1},{3,2,4},{3},{4}};
    int sizes[] = { 3, 3, 1, 1};
    int n_of_arrs = sizeof( arr)/sizeof( arr[0]);
    Array **arrays = calloc( n_of_arrs, sizeof( Array * ) );
    for( int i = 0; i < n_of_arrs; i++ ){
        int tmp = sizeof( arr[0] )/sizeof( arr[0][0] );
        arrays[i] = new_array( tmp );
        for( int j = 0; j < sizes[i]; j++ ){
            append( arrays[i], arr[i][j] );
        }
    }

    int **graph = calloc( n_of_arrs, sizeof( int * ) ) ;

    for( int i = 0; i < n_of_arrs; i++ ){
        graph[i] = calloc( sizes[i],  sizeof( int ) );
        for( int j = 0; j < sizes[i]; j++){
            graph[i][j] = arr[i][j];
        }
    }

    
    int returnSize = 0;
    int **returnColSizes;
    Array **results = allPathsSourceTarget( graph, n_of_arrs, sizes, &returnSize, returnColSizes );
    for( int i = 0; i < returnSize; i++ ){
        printArr( results[i] );
    }
    return 0;


    /*Array *curr = new_array( 2 );
    append( curr, 0);
    
    printArr( curr );*/
}