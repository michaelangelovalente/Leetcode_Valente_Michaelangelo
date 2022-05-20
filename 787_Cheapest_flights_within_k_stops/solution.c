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

        for( int j = 0; j < n; j++ ){
            (*prev)[j] = (*curr)[j];
        }

    }

    if( (*prev)[dst] >= INF ) return -1;

    
    return (*prev)[dst];
}

