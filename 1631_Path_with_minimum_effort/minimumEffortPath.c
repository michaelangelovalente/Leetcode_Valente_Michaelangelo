#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX/2

/**
 * @brief 
 * 
    You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

    A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

    Return the minimum effort required to travel from the top-left cell to the bottom-right cell.


    Example 1:

    Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
    Output: 2
    Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
    This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

 * 
 */



void printarr(int *arr){
    printf("(%d, %d) ", arr[0], arr[1]);
    return;
}


void printpq(int **pq){
    int sizePq = pq[0][1], numOfEls = pq[0][0];
    printf("Number of elements: %d\nSize of priority queue:%d\n", numOfEls, sizePq );
    for( int i = 1; i <= sizePq; i++){
        if( i > numOfEls){
            printf("[ NULL, NULL ] ");
        }else{
            printarr( pq[i] );
        }
    }
    printf("\n");
    return;
}
//priority queue

int rightchild( int idx){
    return idx*2 + 1;
}
int leftchild( int idx ){
    return idx*2;
}
int father( int idx ){
    return idx/2;
}
int getkey( int *el ){
    return el[1];
}
void swap( int **arr1, int **arr2){
    int *tmp = *arr1;
    *arr1 = *arr2;
    *arr2 = tmp;
    return;
}
void heapifyup( int **pq, int idx){
    if( idx > 1){
        int parent = father( idx );
        if( getkey( pq[idx] ) < getkey( pq[parent])){
            swap( &(pq[idx]), &(pq[parent])  );
            heapifyup( pq, parent );
        }
    }
    return;
}

void heapifydown( int **pq, int idx){
    int smallest, right, left = leftchild( idx );
    int numOfEls = pq[0][0]; // number of elements inside the priority queue
    if( left <= numOfEls ){ // at least one child
        if( left == numOfEls ){ //onechild
            smallest = left;
        }else{
            right = rightchild(idx);
            smallest = getkey( pq[right] ) < getkey( pq[ left]) ? right : left;
        }

        if( getkey(pq[smallest])  < getkey( pq[ idx ])){
            swap( &(pq[smallest]), &(pq[idx]) );
            heapifydown( pq, smallest );
        }

    }
    return;
}

//returns 1 if priority queue is empty else 0;
int isempty( int **pq ){
    return (pq[0][0] == 0);
}
int **newPq( int size ){
    int **pq = calloc( size, sizeof( int *));
    //pq[0] contains --> pq[0][0] current size, pq[0][1]maxsize 
    for( int i = 0; i<size+1; i++){
        pq[i] = calloc( 2, sizeof( int ));
    }
    pq[0][1] = size;
    return pq;
}

void insert( int **pq, int vrtx, int weight ){
    int *idx = &(pq[0][0]); // current size of the priority queue
    pq[++(*idx)][0] =  vrtx;
    pq[(*idx)][1] =  weight;
    heapifyup( pq, *idx );
    return;
}

int *extract( int **pq ){
    int *idx = &(pq[0][0]); // number of elements and index of the last elements
    swap( &(pq[1]), &(pq[ *idx ]) );
    (*idx)--;
    heapifydown( pq, 1);
    int *result = pq[ *(idx) + 1 ];
    
    return result;
}
// Graph 
typedef struct edge{
    int vertAndWeight[2];
    struct edge *next;
}Edge;

struct Graph{
    int numOfVert;
    Edge **list;
};



Edge *newEdge( int vrtx, int weight){
    Edge *new = calloc( 1, sizeof( Edge ) );
    new->vertAndWeight[0] = vrtx;
    new->vertAndWeight[1] = weight;
    return new;
}

//print Graph's adjacency list
void printGraph( struct Graph *G ){
    for( int i = 0; i < G->numOfVert; i++ ){
        printf("[%d] -  [ ", i);
        Edge *edge = G->list[i];
        while( edge ){
            printf("(%d, %d) -> ", edge->vertAndWeight[0], edge->vertAndWeight[1] );
            edge = edge->next;
        }
        printf("\n");
    }
    return;
}

// right vrtx adjList +1
int rightVal( int **heights, int i , int j ){
    return abs(heights[i][j] - heights[i][j+1]);
}

// bottom vrt adjList + 3;
int bottomVal( int **heights, int i, int j ){
    return abs( heights[i][j] - heights[i+1][j] );
}

//returns array minDistance and prev
int **dijkstra( int start, struct Graph *G ){
    int *minDist = calloc( G->numOfVert, sizeof( int ));
    int *prev = calloc( G->numOfVert, sizeof( int ) );
    for( int i = 0; i < G->numOfVert; i++ ){
        minDist[i] = INF;
        prev[i] = -1;
    }
    int *visited = calloc( G->numOfVert, sizeof( int ) );
    int **pq = newPq( G->numOfVert );
    minDist[start] = 0;
    insert(pq, start,0);
    while( !( isempty( pq ))){
        int *curr = extract(pq), vrtx = curr[0];
        if( !visited[vrtx] ){
            visited[vrtx] = 1;
            Edge *neighborVrtx = G->list[vrtx];
            while( neighborVrtx != NULL){
                int nextDistance = neighborVrtx->vertAndWeight[1];
                int currDistance = minDist[ neighborVrtx->vertAndWeight[0] ];
                if( !visited[neighborVrtx->vertAndWeight[0]] && nextDistance < currDistance ){
                    minDist[neighborVrtx->vertAndWeight[0]] = nextDistance;
                    prev[neighborVrtx->vertAndWeight[0]] = vrtx;
                    insert( pq, neighborVrtx->vertAndWeight[0], nextDistance);
                }
                neighborVrtx = neighborVrtx->next;
            }
            
        }

        
    }
    printf("--index: ");
    for( int i = 0; i < G->numOfVert; i++){
        printf("[%02d]", i);
    }
    printf("\n");

    printf("minDist: ");
    for( int i = 0; i < G->numOfVert; i++){
        printf("[%02d]", minDist[i]);
    }
    printf("\n");
    printf("___prev: ");
    for( int i = 0; i < G->numOfVert; i++){
        printf("[%02d]", prev[i]);
    }
    printf("\n");

    int **result = calloc(2, sizeof( int *));
    result[0] = minDist;
    result[1] = prev;
    return result;
}

int minimumEffortPath(int** heights, int heightsSize, int* heightsColSize){
    int numOfVertices = heightsSize * *heightsColSize;
    struct Graph *adjList = calloc( 1, sizeof( struct Graph ));
    adjList->list = calloc( numOfVertices, sizeof( Edge *) );
    int adjListIdx = 0;
    //generate adjacency list.
    for( int i = 0; i < heightsSize; i++){
        for( int j = 0; j < *heightsColSize; j++) {
            Edge *new;
            //if( < rightBoundry and < bottomBoundry ) 
            // generate right and bottom
            if( i <  (*heightsColSize)-1 && j < heightsSize-1 ){
                new = newEdge( adjListIdx+1, rightVal( heights, i, j ) );
                new->next = newEdge( adjListIdx+3, bottomVal( heights, i ,j ) );
                adjList->list[ adjListIdx++ ] = new;
            }else if( j!= i && i == (*heightsColSize)-1 ){//( == bottom boundary ) --> generate only right
                new = newEdge( adjListIdx+1, rightVal( heights, i, j ) );
                adjList->list[ adjListIdx++ ] = new;
            }else if( j!=i && j == heightsSize -1 ){ //else if( == right boundary ) --> generate only bott
                new = newEdge( adjListIdx+3, bottomVal( heights, i, j ) );
                adjList->list[ adjListIdx++ ] = new;
            }else{// last vertex is empty
                adjList->list[ adjListIdx++ ] = NULL;
            }

        }
    }
    adjList->numOfVert = adjListIdx;
    printGraph( adjList );

    printf("\n---------- Dijkstra:\n");
    // Dijkstra
    int **dijk = dijkstra(0, adjList);
    


    return -1;
}

int main( int argc, char *argv[]){
    //int tmp[][3] = {{1,2,2},{3,8,2},{5,3,5}};
    int tmp[][5] = {{1,2,1,1,1},{1,2,1,2,1},{1,2,1,2,1},{1,2,1,2,1},{1,1,1,2,1}};
    //int tmp[][3] = {{1,2,3},{3,8,4},{5,3,5}};
    int heightsSize = sizeof( tmp )/sizeof(tmp[0]);
    int colSize = sizeof(tmp[0])/sizeof(tmp[0][0]);
    int **heights = calloc( heightsSize, sizeof( int *) );

    for( int i = 0; i < heightsSize; i++){
        heights[i] = calloc( colSize, sizeof( int ));

        heights[i][0] = tmp[i][0];
        heights[i][1] = tmp[i][1];
        heights[i][2] = tmp[i][2];
    }

    int result = minimumEffortPath( heights, heightsSize, &colSize );

   /* int arr[] = { 7, 2, 9, 4, 5, 3};
    int sizeofarr = sizeof( arr )/ sizeof( arr[0]);
    int **PQ = newPq( sizeofarr );
    for( int i = 0; i < sizeofarr; i++ ){
        insert( PQ, arr[i], arr[i]);
        printpq( PQ );
        printf("\n");
    }
    
    printf("----------------------------------------\n\n");
    for( int i = 1; i <= sizeofarr; i++ ){
        
        printpq( PQ );
        int *extracted = extract( PQ );
        printf("Extracted:( %d, %d)\n", extracted[0], extracted[1]);
        printpq( PQ );
        printf("\n\n");
    }*/
}