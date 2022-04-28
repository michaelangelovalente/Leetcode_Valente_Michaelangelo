#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
    ---------
    Algorithm used to solve the problem: Kruskal's Algorithm
        - We first sort

    ----------
    DS used for support: Union-Find / Disjoint set --> we need to implement find(a), union(a,b), 
    makeset(size) (makeset() will take the Size/number of vertices. In the problem this is the pointsSize variable )
    We use union-find by rank with path compression.

    (Note: remb=ember that the union by rank optmization
    is used to optimize the quick-union version of union by rank, this
    is due to the quick-find version having a time complexity of O(1) already )

        We use 2 auxiliary/support arrays: 
        -One will suport 'group name' -> this array will contain the parentVertex as the value, and
        meanwhile the position is the Vertex name/value

        -The second will support the rank of the group 
        example:
             [0]
            /   \
           [1]  [2]
          /
        [3]
    Arr_root -->  [0] [0] [0] [1]  <---- parent  ( root is Arr[idx]==idx )
             idx:  0   1   2   3   <--- vrtx names

                                                      ( Height/rank at root is 0, therefore rank at height n is n-1 )
    Arr_rank -->  [2] [N] [N] [N]  <---- rank/height  ( we only consider the heigh of the root of each group. In this case, the root of the group has vertex name '0' with height )
             idx:  0   1   2   3   <--- vrtx names

    

*/
struct rankUnionFind {
    int *root;
    int *height;
};

/**makeset()*/
struct rankUnionFind *makeset(int size){
    struct rankUnionFind *disjointSet = calloc( 1, sizeof(struct rankUnionFind));
    disjointSet->root = calloc(size,sizeof(int));
    disjointSet->height = calloc(size,sizeof(int));
    return disjointSet;
}

/**find(a) returns the ID of the group in which node a belongs to*/
int find( int a, struct rankUnionFind *data){
    // need to add path compression!
    if( a == data->root[a]){
        return a;
    }
    return data->root[a] = find(data->root[a], data);
}

/**
 * union(a,b) merge the groups of a and b.
 * If they already belong to the same group, we do not do anything, and return false (edge was not added).
 * otherwise true(edge was added)
 ***/
bool q_unionbyRank( int a, int b){

    return false;
}

void print_disjS( struct rankUnionFind *ds, int size){
    printf("root: ");
    int j = 0;
    for( int i = 0; i < size; i++){
        printf("[%d]");
    }
}
/*------------------------------------*/
/**manhattan distance <- |xi - xj| + |yi - yj|*/
int manhDist( int *a, int *b ){
    return abs( b[1] - a[1] ) + abs( b[0] - a[0] );
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    
    return 0;
}

int main(int argc, char *argv[]){

    /*
    int points[][2] = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    /*int points[][2] = {{3,12},{-2,5},{-4,1}};*/
    /*
    int sizeArr = sizeof( points)/ sizeof(points[0]);
    
    for( int i = 0; i < sizeArr; i++ ){
        for(int j = i; j < sizeArr; j++){
            if( i != j ){
                printf("EDGE:%d -> %d -- Weight:%d\n", i, j, manhDist( points[i], points[j]  ));
            }
            
        }
        printf("\n\n");
    }*/

    struct rankUnionFind *new_DS = makeset(7);
    int arr[] = { 0, 0, 0, 1, 3, 5, 5};
    int size = sizeof( arr )/sizeof(arr[0]);
    for( int i = 0; i < size; i++){
        new_DS->root[i] = arr[i];
    }
    printf("Before path compression:");
    for( int j = 0; j < size; j++){
        printf("[%d]", new_DS->root[j]);
    }
    printf("\n");
    for( int j = 0; j < size; j++ ){
        printf("vertex(%d) -> root(%d) \n", j,find(j, new_DS)  );
    }

    printf("\nAfter path compression:");

    for( int j = 0; j < size; j++){
        printf("[%d]", new_DS->root[j]);
    }
    printf("\n");
    for( int j = 0; j < size; j++ ){
        printf("vertex(%d) -> root(%d) \n", j,find(j, new_DS)  );
    }
    



}