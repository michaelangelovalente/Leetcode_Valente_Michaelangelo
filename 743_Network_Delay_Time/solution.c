#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define INF INT_MAX

typedef struct node{
    int vrtx, weight; // (node, weight)
    struct node *next;
}Node;

struct graph{
    Node **vertx;
    int size;
};

// Prototypes

//pq
int **makePQ( int size);

void insert( int **pq, int vrtx, int key );
int *pop( int **pq );
int isempty( int **pq );
//utilities
void heapifyup( int **pq, int idx);
void heapifydown( int **pq, int idx);

void swap( int **arr1, int **arr2 );
int getKey( int *arr);
int leftchild( int idx);
int rightchild( int idx );
int father( int idx );


// Priority queue
int **makePQ( int size){
    // We store the actual size of the heap in index [0][0].
    // We store the Max size of the heap in index  [0][1]
    int **pq = calloc(size+1, sizeof( int *));
    pq[0] = calloc( 2, sizeof( int ));
    pq[0][1] = size;
    return pq; 
}


void insert( int **pq, int vrtx, int key ){  // :(vrtx, weight)
    int *idx = &(pq[0][0]);
    pq[++(*idx)] = calloc( 2 , sizeof(int));
    pq[*idx][0] = vrtx;
    pq[*idx][1] = key;
    //heapifyup
    heapifyup( pq, *idx );
    return;
}
int *pop( int **pq ){
    int *extracted = pq[1];
    int *pq_size = &(pq[0][0]);
    swap( &(pq[ *pq_size] ), &(pq[1]) );
    (*pq_size)--;
    heapifydown(pq,1);
    return extracted;
}


int isempty( int **pq ){
    return pq[0][0] == 0;
}
//utilities
void heapifydown( int **pq, int idx){
    int sizePQ = pq[0][0];
    if( idx*2 <= sizePQ ){ // at least 1 child
        int left_child = leftchild( idx );
        int right_child = rightchild( idx );
        
        int smallest_child;
        if( idx*2 == sizePQ ){ // one child
            smallest_child = left_child;
        }else{ // at least two children
            smallest_child = getKey( pq[left_child]) < getKey( pq[right_child] ) ? left_child : right_child;
        }

        if( getKey( pq[smallest_child] ) < getKey( pq[idx] ) ){
            swap( &(pq[smallest_child]),&(pq[idx]) );
            heapifydown( pq, smallest_child );
        }

    }
}
void heapifyup( int **pq, int idx){
    if( idx > 1){
        int parent = father( idx );
        if( getKey( pq[idx] ) < getKey( pq[ parent ]) ){
            swap( &(pq[idx]), &(pq[parent]) );
            heapifyup( pq,  parent );
        }
    }
}

void swap( int **arr1, int **arr2 ){
    int *tmp = *arr1;
    *arr1 = *arr2;
    *arr2 = tmp;
}
int getKey( int *arr){
    return arr[1];
}
int leftchild( int idx){
    return idx*2;
}
int rightchild( int idx ){
    return idx*2 +1;
}
int father( int idx ){
    return idx/2;
}

//743 leetcode


int *dijkstra( int start, struct graph *G){
    int *minDist = calloc( G->size , sizeof( int ) );
    int *visited = calloc( G->size, sizeof( int ) );

    // initialize empty priorityqueue
    int **pq = makePQ( 300); //(start_vrtx, dist/key == 0)

    //int *prev = calloc( G->size, sizeof( int ));
    // Minimum distance to get to a vrtx start from vrtx start.
    // initially all are set to +INF and minDist[start] = 0. ( distance from start -> start == 0)
    for( int i = 1; i < G->size; i ++ ){
        if( i != start ){
            minDist[i] = INF;
        }
        //prev[i] = -1;
    }

    insert( pq, start, 0);

    while( !isempty( pq ) ){

        int *extracted = pop(pq);

        if( !visited[ extracted[0] ]){
            int currDist = minDist[ extracted[0] ];
            visited[ extracted[0] ] = 1;
        
            //add all neighbors to pq
            // and check distance
            Node *hasNeigh = G->vertx[ extracted[0] ];
            while( hasNeigh ){
                int nextWeight = currDist + hasNeigh->weight;
                if( !visited[ hasNeigh->vrtx ] &&  nextWeight < minDist[ hasNeigh->vrtx ] ){
                    insert( pq, hasNeigh->vrtx, nextWeight );
                    minDist[ hasNeigh->vrtx ] = nextWeight;
                    //prev[ hasNeigh->vrtx ] = extracted[0];
                }
                hasNeigh = hasNeigh->next;
            }
        }
    }
    return minDist;
}

int networkDelayTime(int** times, int timesSize, int* timesColSize, int n, int k){

    //generate adj. list
    struct graph *G = calloc( 1, sizeof( struct graph ) );
    G->vertx = calloc(n+1, sizeof( Node *));
    G->size = n+1;

    for( int i = 0; i < timesSize; i++ ){
        //G->vertx[i] = calloc( 1, sizeof( Node ));
        Node *currNode = calloc( 1, sizeof( Node ) );
        currNode->vrtx = times[i][1];
        currNode->weight = times[i][2];
        if( G->vertx[ times[i][0] ] == NULL ){
            G->vertx[ times[i][0] ] = currNode;
        }else{
            Node *pos = G->vertx[ times[i][0] ];
            while( pos->next ){
                pos = pos->next;
            }
            pos->next = currNode;
        }
    }

    int *result = dijkstra( k, G);
    int max = result[1];
    for( int i = 2; i <= n; i++){
        if( max == INF || result[i] == INF ) return -1;
        if( max < result[i]) max = result[i];
    }

    return max;
}


