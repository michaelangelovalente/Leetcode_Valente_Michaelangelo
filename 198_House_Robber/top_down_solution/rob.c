#include <stdio.h>
#include <stdlib.h>

void print_arr( int *arr, int size);
int max( int a, int b);
int rob(int* nums, int numsSize);
int dp( int i, int *nums, int *memo);

int main( int argc, char *argv[] ){
    int nums[] = { 1, 2, 3, 1};
    int size = sizeof( nums )/sizeof( nums[0]);
    printf("result:%d\n", rob( nums, size) );
    return 0;
}

void print_arr( int *arr, int size){
    for( int i = 0; i < size; i++){
        printf("[%d]", arr[i]);
    }
    printf("\n");
    return;
}

int max( int a, int b){
    return a>b? a:b;
}

int rob(int* nums, int numsSize){
    int *memo = calloc( numsSize, sizeof( int ));
    for( int i = 0; i < numsSize; i++)memo[i] = -1;
    int result = dp( numsSize-1, nums, memo);
    print_arr( memo, numsSize );
    
    return result;
}

int dp( int i, int *nums, int *memo){
        if( i == 0) return memo[0] = nums[0];
        if( i == 1) return memo[1] = max( nums[0], nums[1] );
        if( memo[i] == -1 ){
            memo[i] = max( dp( i-1, nums, memo),  dp(i-2, nums, memo) + nums[i] );
        }
        return memo[i];
}