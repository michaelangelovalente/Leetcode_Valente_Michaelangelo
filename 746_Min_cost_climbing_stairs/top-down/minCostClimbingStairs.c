#include <stdio.h>
#include <stdlib.h>



int min( int a, int b ){
    return a<b?a:b;
}

int minCost_util( int *cost, int *memo, int i ){
    if( i <= 1){
        return 0;
    }
    if( memo[i] == -1 ){
        memo[i] = min( minCost_util( cost, memo, i-1) + cost[ i - 1], minCost_util( cost, memo, i-2 ) + cost[i-2] );
    }
    return memo[i];
}
int minCostClimbingStairs(int* cost, int costSize){
    int *memo = calloc( costSize+1, sizeof( int ));
    for( int i = 2; i < costSize+1; i++){
        memo[i] = -1;
    }
    return minCost_util( cost, memo, costSize );
}
