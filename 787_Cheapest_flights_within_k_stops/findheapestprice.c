/**
 * @file findheapestprice.c
 * 
 * @author michaelangelovalente
 * @brief 
 * @version 0.1
 * @date 2022-05-20
 *  
 * @copyright Copyright (c) 2022
 * 
 * There are n cities connected by some number of flights. 
 * You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.
 * 
 * You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
 * 
 * 
 *  Example:
 *      Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
 *      Output: 700
 *      Explanation:
 *      The graph is shown above.
 *      The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
 *      Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (INT_MAX - (INT_MAX/2))


void swap( int **a, int **b );
void printarr( int *a, int size);


int findCheapestPrice(int n, int** flights, int flightsSize, int* flightsColSize, int src, int dst, int k){
    //2 arrays with previous weights and current weights
    int *array1 = calloc(n , sizeof(int));
    int *array2 = calloc( n, sizeof( int ));
    int **curr = &(array1);
    int **prev = &(array2);
    
    // initialize array with INF and 0 at array position 0 ( for both arrays )
    for( int i = 0; i < n; i++){
        if( i == src ){
            array1[i] = array2[i] = 0;
        }else{
            array1[i] = array2[i] = INF;
        }
    }
    
    for( int i =0; i <= k; i++ ){
        printf("--------------\n");
        printf("curr: ");
        printarr( *curr, n );
        printf("prev: ");
        printarr( *prev, n );
        printf("\n");
        for( int j= 0;j< flightsSize; j++ ){
            // vrtx0->vrtx1
            int currDist = (*prev)[ flights[j][1] ]; // current weight( vrtx1 )
            int nextDist = abs( (*prev)[ flights[j][0] ] + flights[j][2] ) ; // curr weight( vrtx0 ) + new_weight_to( vrtx 1)
            if( nextDist < currDist ){ 
                if( (*curr)[ flights[j][1] ] > nextDist ){
                    (*curr)[ flights[j][1] ] = nextDist;
                }
                
            }
        }

        printf("curr: ");
        printarr( *curr, n );
        printf("prev: ");
        printarr( *prev, n );
        printf("\n");

        for( int j = 0; j < n; j++ ){
            (*prev)[j] = (*curr)[j];
        }
        
        //swap( curr, prev );
        printf("\n");
        printf("curr: ");
        printarr( *curr, n );
        printf("prev: ");
        printarr( *prev, n );
        printf("\n");

    }

    if( (*prev)[dst] >= INF ) return -1;

    
    return (*prev)[dst];
}


void swap( int **a, int **b ){
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

void printarr( int *a, int size){

    for( int i = 0; i < size; i++){
        printf("[%d]", a[i]);
    }
    printf("\n");

    return;
} 


int main( int argc, char *argv[] ){

    /**
     * @brief 
     *
     * 
     * 
        7
        {{0,3,7},{4,5,3},{6,4,8},{2,0,10},{6,5,6},{1,2,2},{2,5,9},{2,6,8},{3,6,3},{4,0,10},{4,6,8},{5,2,6},{1,4,3},{4,1,6},{0,5,10},{3,1,5},{4,3,1},{5,4,10},{0,1,6}}
        2
        4
        1
     * 
     * 
     */
    int  n = 7; // number of airports
    int tmp[][3] = {{0,3,7},{4,5,3},{6,4,8},{2,0,10},{6,5,6},{1,2,2},{2,5,9},{2,6,8},{3,6,3},{4,0,10},{4,6,8},{5,2,6},{1,4,3},{4,1,6},{0,5,10},{3,1,5},{4,3,1},{5,4,10},{0,1,6}};
    int flightsSize = sizeof( tmp ) / sizeof( tmp[0] );
    int **flights = calloc( flightsSize, sizeof( int *) );
    for( int i = 0; i < flightsSize; i++){
        flights[i] = calloc(3 , sizeof(int));
        flights[i][0] = tmp[i][0];
        flights[i][1] = tmp[i][1];
        flights[i][2] = tmp[i][2];
    }
    int src = 2; // source
    int dst = 4; // dst
    int k = 1; // at most k airports --> k+1 iteration of Bellman Ford
    

    
    int flightsColSize = 3;
    //printf("%d \n- %d\n",a , b);

    /*
    int tester1[] = { 1 ,2, 3, 4};
    int tester2[] = { 5, 6, 7, 8};
    printarr( tester1, 4);
    printarr( tester2, 4);
    swap( &tester1, &tester2);
    printf("\n");
    printarr( tester1, 4);
    printarr( tester2, 4);
    */
    int test =  findCheapestPrice(n, flights, flightsSize, &flightsColSize, src, dst, k);
    printf("Min cost:%d", test);
}