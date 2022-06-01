#include <stdio.h>
#include <stdlib.h>


void print( int *arr, int size ){
    for( int i = 0; i < size; i++){
        printf("[%d]", arr[i]);
    }
    printf("\n");
}

int max( int a , int b ){
    return a > b ? a : b;
}

int rob(int* nums, int numsSize){

    if( numsSize == 1){
        return nums[0];
    }

    int *memo = calloc( numsSize, sizeof( int ));
    memo[0] = nums[0];
    memo[1] = max( nums[1], nums[0]);
    for( int i = 2; i < numsSize; i++ ){
        memo[i] = max( memo[ i-2 ] + nums[i],  memo[ i-1 ] );
    }
    //print( memo, numsSize );
    return memo[numsSize-1];
}


int main(){
    int a[] = {2, 7, 9, 3, 1};
    int size = sizeof( a  )/sizeof( a[0] );
    int result = rob( a, size );
    printf("Result: %d\n", result);
}