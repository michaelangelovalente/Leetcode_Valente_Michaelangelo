#include <stdio.h>
#include <stdlib.h>

void print_array( int *arr, int size){
    for( int i = 0; i < size; i++) printf("[%d]", arr[i]);
    printf("\n");
}
int square( int a){
    return a*a;
}

int* sortedSquares(int* nums, int numsSize, int* returnSize){
    int *result = calloc( numsSize, sizeof( int ));
    int left = 0, right = numsSize-1;
    

    for( int i = numsSize-1; i >= 0; i--){
        if( square( nums[ left]) > square( nums[right ])){
            result[i] = square( nums[ left++]);
        }else{
            result[i] = square( nums[ right--]);
        }
    }

    return result;
}



int main(){
    int nums[] = {-4,-1,0,3,10}, size = sizeof(nums)/sizeof(nums[0]);
    printf("Original: ");
    print_array( nums, size );
    int *new = sortedSquares( nums, size, &size );

    printf("Result: ");
    print_array( new, size);

    
}