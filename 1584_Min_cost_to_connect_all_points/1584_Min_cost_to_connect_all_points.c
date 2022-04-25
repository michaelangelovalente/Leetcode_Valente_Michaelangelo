#include <stdio.h>
#include <stdlib.h>
/**
 * @file 1584_Min_cost_to_connect_all_points.c
 * 
 * 
 * @author Michaelangelo Valente
 * @date 2022-04-25
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
 * 
    You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

    The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

    Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

    

    Example 1:


    Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
    Output: 20
    Explanation: 

    We can connect the points as shown above to get the minimum cost of 20.
    Notice that there is a unique path between every pair of points.

    ------- 

    Example 2:

    Input: points = [[3,12],[-2,5],[-4,1]]
    Output: 18
 * 
    ---------------------------------
    Algorithm used to solve the problem: Kruskal's Algorithm
    DS used for support: Union-Find (?)
 */



/**manhattan distance <- |xi - xj| + |yi - yj|*/
int manhDist( int *a, int *b ){
    return abs( b[1] - a[1] ) + abs( b[0] - a[0] );
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    
    return 0;
}

int main(int argc, char *argv[]){
    int points[][2] = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    /*int points[][2] = {{3,12},{-2,5},{-4,1}};*/
    int sizeArr = sizeof( points)/ sizeof(points[0]);
    
    for( int i = 0; i < sizeArr; i++ ){
        for(int j = i; j < sizeArr; j++){
            if( i != j ){
                printf("EDGE:%d -> %d -- Weight:%d\n", i, j, manhDist( points[i], points[j]  ));
            }
            
        }
        printf("\n\n");
    }
}