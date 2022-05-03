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

    (3) Priority queue using MinHeap:
        We use the PQ( abstract data type) to store the generated edges, 
        with key(weight) the manhattan distance. 

        The PQ ( abstract data type) is an 
        efficient way to do this since when we store our edge, 
        it will 'automatically' sort it, we will only then need to extract
        n edges, which will be the smallest n edges, that will allow us to build an MST.

        ( An alternative solution could be to generate  the edges and store them inside an array, 
        and then sort them, we use the PQ, for learning and optimization purposes. ).
        
        Implementation:
            We will use a minHeap data structure to implement the priority queue.
            We need to implement the operations:
            makePq(), peek(), remove(), insert().
            ( We will also create the auxiliary functions: heapifyup() and heapifydown(),
              father(), leftchild(), rightchild() )
    ------ 
*/

/** ----------------- Prototypes -----------------------*/


// ------- Priority queue prototypes------ //
struct edge;
struct Pq *pq;

// main functions
struct Pq *makePq( int size );
void insertPq( struct Pq *pq, struct edge *edge);
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
};


/** 
 * makePq( int size ) takes an integer size, and creates the array where we will store the
 * vertices of a Priority queue.
 */
struct Pq *makePq( int size ){
    struct Pq *pq = calloc(1, sizeof(struct Pq ));
    pq->Edge = calloc(size+1, sizeof( struct edge*));//this is size+1 because we will ignore position 0.
    return pq;
}


void insertPq( struct Pq *pq, struct edge *edge){
    pq->Edge[++pq->size] = edge;//insert new edge
    
    if( pq->size > 1  ){
        // if father's key < child's key
        //reaheapifyup
        
        heapifyup( pq, pq->size );
    }

}

struct edge *extract( struct Pq *pq ){
    struct edge *retEdge = pq->Edge[1];
    swap( &(pq->Edge[1]) , &( pq->Edge[pq->size] ) );
    pq->size--;
    heapifydown( pq, 1 );
    return retEdge;
}

/**Auxiliary functions*/ // <--------------- Need to fix this
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

void heapifyup( struct Pq *pq , int i ){
    if( i > 1 ){
        int parent = father(i);
        if( getKey(pq->Edge[parent]) > getKey( pq->Edge[i] ) ){
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

    /*struct rankUnionFind *new_DS = makeset(7);
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
    }*/

    /*
    struct rankUnionFind *new_DS = makeset(7);
    int arr[] = { 0, 0, 0, 1, 3, 5, 5, 6, 7};
    int rank[] = { 3, 2, 0, 1, 0, 3, 2, 1, 0 };
    int size = sizeof( arr )/sizeof(arr[0]);
    for( int i = 0; i < size; i++){
        new_DS->root[i] = arr[i];
    }

    for( int i = 0; i < size; i++){
        new_DS->height[i] = rank[i];
    }

    printf("Before Union:\n");
    for( int j = 0; j < size; j++){
        printf("[%d]", new_DS->root[j]);
    }
    printf("\n");
    for( int j = 0; j < size; j++){
        printf("[%d]", new_DS->height[j]);
    }
    printf("\n");

    if( q_unionbyRank( new_DS, 2, 5 ) ){
        printf("Union worked!\n\n");
    }else{
        printf("Union did not work\n\n");
    }
    printf("After Union:\n");
    for( int j = 0; j < size; j++){
        printf("[%d]", new_DS->root[j]);
    }
    printf("\n");
    for( int j = 0; j < size; j++){
        printf("[%d]", new_DS->height[j]);
    }
    printf("\n");
    */
   /*
   struct edge *arr1 = calloc(1, sizeof(struct edge));
   arr1->vrtx_x = 2; arr1->vrtx_y=2; arr1->weight=222;

   struct edge *arr2 = calloc(1, sizeof(struct edge));
   arr2->vrtx_x = 3; arr2->vrtx_y=3; arr2->weight=333;

   printf("edge1->[%d,%d], key:%d\n" , arr1->vrtx_x, arr1->vrtx_y, arr1->weight);
   printf("edge2->[%d,%d], key:%d\n" , arr2->vrtx_x, arr2->vrtx_y, arr2->weight);

   swap(&arr1, &arr2);

   printf("edge1->[%d,%d], key:%d\n" , arr1->vrtx_x, arr1->vrtx_y, arr1->weight);
   printf("edge2->[%d,%d], key:%d\n" , arr2->vrtx_x, arr2->vrtx_y, arr2->weight);
   */
  int size = 8;
  struct Pq *priority_queue = makePq( size );
  //generating edges
    for( int i = 1; i < size; i++ ){
        int valtmp = i*size;
        struct edge *e = new_edge(i, i, valtmp );
        insertPq( priority_queue, e );
    }

    printPq( priority_queue);
    printf("Size:%d\n", priority_queue->size);
    struct edge *extractEdge = extract( priority_queue );
    printf("Edge[%d] -> vertices: ( %d, %d) - [key:%d]\n",1, extractEdge->vrtx_x, extractEdge->vrtx_y, getKey(extractEdge) );
    printf("Extracted: %d\n", extractEdge->weight);
    printf("\n");
    printPq( priority_queue);
    
   /*
    struct Pq *priority_queue = makePq( 5 );
     
    struct edge *e = new_edge( 1, 1, 1);
    insertPq( priority_queue, e );
    printPq( priority_queue);
    printf("\n");
    struct edge *e2 = new_edge( 2, 2, 2);
    insertPq( priority_queue, e2 );
    printPq( priority_queue);
    printf("\n");
    struct edge *e3 = new_edge( -2, -2, -2);
    insertPq( priority_queue, e3 );
    printPq( priority_queue);
    */
}