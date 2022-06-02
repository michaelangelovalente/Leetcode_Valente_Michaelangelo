#include <stdio.h>
#include <stdlib.h>

void print_arr( int *arr, int size ){
    for(int i = 0; i < size; i++){
        printf("[%d]", arr[i]);
    }
    printf("\n");
    return;
}

int min( int a, int b ){
    return a<b?a:b;
}

int minCostClimbingStairs(int* cost, int costSize){
    int *memo = calloc( costSize, sizeof( int ));
    memo[0] = cost[0];
    memo[1] = cost[1];
    for( int i = 2; i < costSize; i++){
        memo[i] = cost[i] + min(memo[i-1],memo[i-2]);
    }
    
    print_arr( memo, costSize );
    return min( memo[costSize-2], memo[costSize-1]);
}

int main( int argc, char *argv[] ){
    int cost[] = {1,100,1,1,1,100,1,1,100,1};
    //int cost[] = {10,15,20 };
    int size = sizeof( cost ) / sizeof( cost[0]);
    printf("Result: %d\n", minCostClimbingStairs( cost, size ));
}