#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//solution is slightly slow --> m*logn. There is a way to get log(m*n)

void print_arr( int *arr, int size);
void print_matrix( int **matrix, int size_r, int size_c );


void print_matrix( int **matrix, int size_r, int size_c ){
    for( int i = 0; i < size_r; i++){
        print_arr( matrix[i], size_c);
    }
}
void print_arr( int *arr, int size){
    for( int i = 0; i < size; i++) printf("[%02d]", arr[i]);
    printf("\n");
}

int binSearch( int *arr, int size, int target ){
    int begin=0, end = size-1;
    while( begin <= end ){
        int mid =(begin+end)/2;
        if( arr[mid]==target ) return mid;
        if( target < arr[mid] ){
            end = mid-1;
        }else if( target > arr[mid]){
            begin = mid+1;
        }
    }
    return -1;
}
bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target){
    for( int i = 0; i < matrixSize; i++){
        //printf("res: [%d]", binSearch( matrix[i], *matrixColSize, target) );
        if( binSearch( matrix[i], *matrixColSize, target) != -1 ){
            return true;
        }
    }
    return false;
}

int main(){
    int tmp[][4] = {{1,3,5,7},{10,11,16,20},{23,30,34,60}}, target = 3;
    int size_r = sizeof(tmp)/sizeof(tmp[0]);
    int size_c = sizeof(tmp[0])/sizeof(tmp[0][0]);
    int **matrix = calloc( size_r, sizeof(int *) );
    for( int i = 0; i < size_r; i++ ){
        matrix[i] = calloc( size_c, sizeof( int ));
        for( int j = 0; j < size_c; j++){
            matrix[i][j] = tmp[i][j];

        }
    }

    print_matrix( matrix, size_r, size_c );
    printf("---------------\n");
    bool found = searchMatrix( matrix, size_r, &size_c, 3);
    printf("Found:%d\n");

}
