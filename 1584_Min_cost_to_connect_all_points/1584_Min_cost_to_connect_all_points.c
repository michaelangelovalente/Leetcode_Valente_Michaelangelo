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
    -------------------------------- --------------------------------- -----------------------
    |-------- Solution Algorithm and Data structures used with a quick explanation ----------|
    --------------------------------- --------------------------------- ----------------------
    (1) Algorithm used to solve the problem: Kruskal's Algorithm

    ----------
    (2) DS used for support: Union-Find / Disjoint set, this will then
    be used to create ( store the edges ) our MST Tree.

    Implementation: 
    We need to implement the operations: find(a), union(a,b), 
    makeset(size) (makeset() will take the Size/number of vertices. 

    (In the leetcode problem this is the pointsSize variable )

    We will also use union-find by rank with path compression.

    (Note: rembember that the union by rank optmization
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

    

    (3) We then QuickSort the edges by weight/key.
    ( A better implementation, and more complex solution, can be 
    done by using a priority queue DS, we store our edge, using manhattan distance as the key/weight value, and 
    extract n ( number of vertices) edges, we then add the key values of the edges extracted, 
    and obtain the solution.)
    ------ 
*/

struct edge{
    int vrtx_x, vrtx_y;
    int weight;
};

/** ----------------- Prototypes -----------------------*/
// ------- QuickSort prototypes------ //
void QuickSort( struct edge **array, int size );
void procedureQuickSort( struct edge **array, int i, int f );
//auxiliary functions
int getKey(struct edge *e);
void swap(struct edge **e1, struct edge **e2 );
int partition( struct edge **array, int i, int j );

// -------------------------------------------------- //
// ------- Union-Find (by rank) DS prototypes ------ //
struct rankUnionFind;
struct rankUnionFind *makeset(int size);
int find( int a, struct rankUnionFind *data);
bool q_unionbyRank( struct rankUnionFind *ds, int a, int b);

void print_disjS( struct rankUnionFind *ds, int size);

// -------------------- The leetcode solution Prototypes ---------------------- //
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize);

int manhDist( int *a, int *b );
struct edge *new_edge( int x, int y, int key );

/***** Quick-Sort */
void QuickSort( struct edge **array, int size ){
    procedureQuickSort( array, 0, size );
    return;
}

void procedureQuickSort( struct edge **array, int i, int f ){
    if( f-i > 1 ){
        int m = partition( array, i, f );
        procedureQuickSort( array, i, m );
        procedureQuickSort( array, m+1, f );
    }
    return;
}




/*** Auxiliary functions ***/
int partition( struct edge **array, int i, int j ){
    int pivot = getKey(array[i]);
    int left = i, right = j;
    while( left < right ){
        do{
        right--;
        }while( getKey(array[right]) > pivot );

        do{
            left++;
        }while( left < right && getKey(array[left]) <= pivot );

        if( left < right ){
            swap( &(array[left]), &(array[right]) );
        }
    }

    swap( &(array[i]) , &(array[right]) );

    return right;
}

void swap(struct edge **e1, struct edge **e2 ){
    struct edge *tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
}

int getKey(struct edge *e){
    return e->weight;
}

/***** Union-Find (quickUnion by rank variation) Data Structure */
struct rankUnionFind {
    int *root;
    int *height;
};

/**makeset()*/
struct rankUnionFind *makeset(int size){
    struct rankUnionFind *disjointSet = calloc( 1, sizeof(struct rankUnionFind));
    disjointSet->root = calloc(size,sizeof(int));
    disjointSet->height = calloc(size,sizeof(int));
    // The set is initally full of 'size' disconnected components of height 0;
    for(int i = 0; i < size; i++){
        disjointSet->root[i] = i;
    }
    return disjointSet;
}

/**find(a) returns the ID of the group in which node a belongs to*/
int find( int a, struct rankUnionFind *data){
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
bool q_unionbyRank( struct rankUnionFind *ds, int a, int b){
    int root_a = find( a, ds) , root_b = find(b, ds);
    if( root_a == root_b ){
        return false;
    }
    if( ds->height[root_a] > ds->height[root_b]){
        //root_a is the new root of root_b 
        //height of a does not change.
        ds->root[root_b] = root_a;

    }else if( ds->height[root_a] < ds->height[root_b]){
        //root_b is the new root of root_a
        //height of b does not change
        ds->root[root_a] = root_b;


    }else{//height of root_a and root_b are the same --> height of root_a ( new root) is now old height + 1 
        ds->root[root_b] = root_a;
        ds->height[root_a] = ds->height[root_a] + 1;
        
    }
    return true;
}



void print_disjS( struct rankUnionFind *ds, int size){
    printf("root: ");
    for( int i = 0; i < size; i++){
        printf("[%d]", ds->root[i]);
    }
    printf("\n");
    printf("      ");
    for( int i = 0; i < size; i++){
        printf(" %d ", i);
    }
    printf("\n");
    printf("height: ");
    for( int i = 0; i < size ; i++){
        printf("[%d]", ds->height[i]);
    }
    printf("\n");
}




/*-------------------  The leetcode Solution  -----------------*/
/**manhattan distance <- |xi - xj| + |yi - yj|*/

void printArrayE( struct edge **array, int size ){
    for( int i = 0; i < size; i++){
        printf("(%d, %d)  |",array[i]->vrtx_x , array[i]->vrtx_y );
    }
    printf("\n");
    for( int i = 0; i < size; i++){
        printf("key[%d] |", getKey( array[i]));
    }
    printf("\n");
}
int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    // ((pointsSize-1) * ( pointsSize-1 +1 ))/2; --> sum of first n ( == edges ) numbers --> number of unique edges;
    int arraySize = ((pointsSize-1) * ( pointsSize ))/2;
    struct edge **arrayE = calloc( arraySize , sizeof( struct edge *));
    int numOfEls = 0; // find a better solution.
    for( int i = 0; i < pointsSize; i++ ){ // need to fix indexes of allocation!
        for( int j = i+1; j < pointsSize; j++ ){
            arrayE[numOfEls++] = new_edge( i,j, manhDist( points[i], points[j] ) );
        }
    }
    QuickSort( arrayE, arraySize );
    //We make space for a disjointset of size n ( number of vertices)
    struct rankUnionFind *uf = makeset( pointsSize );
    
    bool connected;
    // Max number of edges is n-1, where n is the number of vertices 
    int max_num_e = 0;
    //Final weight
    int final_w = 0;
    for( int i = 0; max_num_e < pointsSize-1; i++   ){
            connected = q_unionbyRank( uf, arrayE[i]->vrtx_x, arrayE[i]->vrtx_y );
            if( connected ){
                final_w += arrayE[i]->weight;
                max_num_e++;
            }
    }

    //freeing unused memory
    for( int i =0 ; i < arraySize; i++ ){
        free(arrayE[i] );
    }
    free(arrayE);

    free(uf->root);
    free(uf->height);
    free(uf);
    return final_w;
}

int manhDist( int *a, int *b ){
    return   abs( a[0] - b[0] ) + abs( a[1] - b[1]  );
}

struct edge *new_edge( int x, int y, int key ){
    struct edge *new = calloc( 1, sizeof( struct edge ));
    new->vrtx_x = x;
    new->vrtx_y = y;
    new->weight = key;
    return new;
}


int main(int argc, char *argv[]){

    
    int points[][2] = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    /*int points[][2] = {{3,12},{-2,5},{-4,1}};*/
    
    int sizeArr = sizeof( points)/ sizeof(points[0]);
    int **ptr_points = calloc( sizeArr, sizeof( int *));
    for( int i = 0; i < sizeArr; i++ ){
        ptr_points[i] = calloc( 2, sizeof(int));
        ptr_points[i][0] = points[i][0];
        ptr_points[i][1] = points[i][1];
        
        for(int j = i+1; j < sizeArr; j++){
            printf("EDGE:%d -> %d -- Weight:%d\n", i, j, manhDist( points[i], points[j]  ));
        }
        printf("\n");
    }

    printf("--------------------------------\n");
    int colSize = 2;
    int tmp = minCostConnectPoints( ptr_points, sizeArr, &colSize );

    printf("Result: %d", tmp);
    /*
    int arr[] = { 24, 8, 31, 16, 17, 40, 29, 23, 27};
    int size = sizeof(arr)/sizeof(arr[0]);

    struct edge **arrayE = calloc( size, sizeof( struct edge *));
    for( int i = 0; i < size; i++ ){
        arrayE[i] = new_edge( i,i, arr[i] );
    }

    printArrayE( arrayE, size );
    printf("\nAfter partition\n");

    printf("returned pivot:%d\n",partition( arrayE, 0, size));
    printArrayE( arrayE, size );

    printf("\nAfter sort\n");
    QuickSort( arrayE, size);
    printArrayE( arrayE, size );
    */
}