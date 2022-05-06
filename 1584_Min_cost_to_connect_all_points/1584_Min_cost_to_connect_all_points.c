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

    

    Quick sort the edges by weight ( A better implementation, that might be more complexy, could be 
    done by using a priority queue DS, We store our edge, using manhattan distance as the key value, and 
    extract n ( number of vertices) edges, we then add the key values of the edges extracted, and obtain the solution.)
    ------ 
*/

/** ----------------- Prototypes -----------------------*/


// ------- Priority queue prototypes------ //
struct edge;
struct Pq *pq;

// main functions
struct Pq *makePq( int size );
void insertPq( struct Pq *pq, int x, int y, int key );
struct edge *extract( struct Pq *pq );

//auxiliary functions
void heapifydown( struct Pq *pq , int parent_idx );
void heapifyup( struct Pq *pq , int i );
struct edge *new_edge( int x, int y, int key);
int getKey(struct edge *e);

void swap(struct edge **e1, struct edge **e2 );
int father( int child);
int leftChild(int father );
int rightChild(int father);


void printPq(struct Pq *pq);
// -------------------------------------------------- //



/***** Priority queue Abstract Data type ( using the Min Heap Data Structure ) */
struct edge{
    int vrtx_x, vrtx_y;
    int weight;
};
struct Pq{
    struct edge **Edge;
    int size;
    int max_size;
};


/** 
 * makePq( int size ) takes an integer size, and creates the array where we will store the
 * vertices of a Priority queue.
 */
struct Pq *makePq( int size ){
    struct Pq *pq = calloc(1, sizeof(struct Pq ));
    pq->Edge = calloc(size+1, sizeof( struct edge *));//this is size+1 because we will ignore position 0.
    pq->max_size = size+1;
    return pq;
}


void insertPq( struct Pq *pq, int x, int y, int key ){
    //New Edge 
   /* struct edge *new_edge = calloc( 1, sizeof( struct edge *));
    new_edge->vrtx_x = x;
    new_edge->vrtx_y = y;
    new_edge->weight = key;

    pq->Edge[++pq->size] = new_edge;//insert new edge
    */
    ++pq->size;
    int idx = pq->size;
    pq->Edge[idx] = calloc( 1, sizeof( struct edge *));
    pq->Edge[idx]->vrtx_x = x;
    pq->Edge[idx]->vrtx_y = y;
    pq->Edge[idx]->weight = key;

    
    heapifyup( pq, pq->size );
    return;

}

struct edge *extract( struct Pq *pq ){
    struct edge *retEdge = pq->Edge[1];
    swap( &(pq->Edge[1]) , &( pq->Edge[pq->size] ) );
    pq->size--;
    heapifydown( pq, 1 );
    return retEdge;
}

/**Auxiliary functions*/ //
void heapifydown( struct Pq *pq , int parent_idx ){
    // if rightchild or leftchild > size --> no more children
    int left_child = leftChild( parent_idx);
    int right_child = rightChild(parent_idx);
    int smallest_child;
    if( left_child <= pq->size ){ // parent has at least one child
        if( left_child == pq->size){ // parent has only one child
            smallest_child = left_child;
        }else{
            smallest_child =  getKey( pq->Edge[left_child] ) < getKey( pq->Edge[right_child] ) ? left_child : right_child;
        }

        if( getKey(pq->Edge[smallest_child]) < getKey(pq->Edge[parent_idx]) ){
            swap( &(pq->Edge[smallest_child]) , &(pq->Edge[parent_idx]) );
            heapifydown( pq, smallest_child );
        }
    }
}

void heapifyup( struct Pq *pq , int i ){ // <--- NEED TO FIX THIS
    if( i > 1 ){
        int parent = father(i);
        int keyParent = getKey(pq->Edge[parent]);
        int keyChild = getKey( pq->Edge[i] );
        if( parent >= 1 && keyParent > keyChild ){
            swap( &(pq->Edge[parent]), &(pq->Edge[i]) );
            heapifyup( pq, parent);
        }
    }
    return;
}



struct edge *new_edge( int x, int y, int key){
    struct edge *e = calloc( 1, sizeof( struct edge ));
    e->vrtx_x = x;
    e->vrtx_y = y;
    e->weight = key;
}

void printPq(struct Pq *pq){
    for( int i = 1; i <= pq->size; i++){
        printf("Edge[%d] -> vertices: ( %d, %d) - [key:%d]\n",i, pq->Edge[i]->vrtx_x, pq->Edge[i]->vrtx_y, getKey(pq->Edge[i]) );
    }
}


void swap(struct edge **e1, struct edge **e2 ){
    struct edge *tmp = *e1;
    *e1 = *e2;
    *e2 = tmp;
}
int getKey(struct edge *e){
    return e->weight;
}
int father( int child){
    return child/2;
}

int leftChild(int father ){
    return father*2;
}

int rightChild(int father){
    return father*2+1;
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
bool q_unionbyRank( struct rankUnionFind *ds, int a, int b){
    int root_a = find( a, ds) , root_b = find(b, ds);
    if(root_a == root_b){
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
    int j = 0;
    for( int i = 0; i < size; i++){
        printf("[%d]");
    }
}




/*-------------------  The leetcode Solution  -----------------*/
/**manhattan distance <- |xi - xj| + |yi - yj|*/
int manhDist( int *a, int *b ){
    return   abs( a[0] - b[0] ) + abs( a[1] - b[1]  );
}

int minCostConnectPoints(int** points, int pointsSize, int* pointsColSize){
    
    struct Pq *PQ = makePq( pointsSize );
    // Generate all the edges and store the edges in a priority queue
        for( int i = 0; i < pointsSize; i++){
            //dist <-- manhattan distance between vertex: i  and vertex: i+1
            for(int j = i; j < pointsSize; j++){
                if( i != j ){
                    int dist = manhDist( points[i], points[j]);
                    printf("(%d,%d)k:%d\n", i, j, dist);
                    insertPq( PQ, i, j, dist);    
                }
                
            }
            

        }
        printf("\n--------------------------------------\n");
        printPq(PQ);

    return 0;
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
        
        for(int j = i; j < sizeArr; j++){
            
            if( i != j ){
                printf("EDGE:%d -> %d -- Weight:%d\n", i, j, manhDist( points[i], points[j]  ));
            }
            
        }
        printf("\n");
    }

    printf("--------------------------------\n");
    int colSize = 2;
    int tmp = minCostConnectPoints( ptr_points, sizeArr, &colSize );


}