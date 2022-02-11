#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define inf 99999
/*
There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.

For each house i, we can either build a well inside it directly with cost wells[i - 1] (note the -1 due to 0-indexing), or pipe in water from another well to it. The costs to lay pipes between houses are given by the array pipes where each pipes[j] = [house1j, house2j, costj] represents the cost to connect house1j and house2j together using a pipe. Connections are bidirectional, and there could be multiple valid connections between the same two houses with different costs.

Return the minimum total cost to supply water to all houses.

 

Example 1:
Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
Output: 3
The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so the total cost is 3.

Example 2:
Input: n = 2, wells = [1,1], pipes = [[1,2,1],[1,2,2]]
Output: 2
Explanation: We can supply water with cost two using one of the three options:
Option 1:
  - Build a well inside house 1 with cost 1.
  - Build a well inside house 2 with cost 1.
The total cost will be 2.
Option 2:
  - Build a well inside house 1 with cost 1.
  - Connect house 2 with house 1 with cost 1.
The total cost will be 2.
Option 3:
  - Build a well inside house 2 with cost 1.
  - Connect house 1 with house 2 with cost 1.
The total cost will be 2.
Note that we can connect houses 1 and 2 with cost 1 or with cost 2 but we will always choose the cheapest option. 



*/
/*

Solution with Prim's Algorithm.
Uses ds:
  - PriorityQueue (Heap)
  - adj. List rep. of the graph
*/

/**/

typedef struct elements{
  int vertx;
  int weight;
}Elements;

/*Each node represents a vertex with a value*/
struct listnode{
  struct listnode *next;
  Elements vertex;
};

typedef struct graph{
  struct listnode **G;
  int n_of_vertices;
  int n_of_edges;
}*Graph;


/*Graph ------------------------------------------------------------*/
/*Creates an empty graph*/
Graph graph_new( int n ){
  Graph g = calloc( 1, sizeof( struct graph ) );

  /*Generate adj with pointer to n nodes*/
  /*for( int i = 0; i < n; i++ ){
    g->G[i] = calloc( 1, sizeof( struct listnode *) );
  }*/
  g->G = calloc( n, sizeof( struct listnode *) );
  g->n_of_vertices = n;
  g->n_of_edges = 0;

  return g;
}

/*Insert node to head of a list*/
/*Need to  fix(?): weight is redundant -> graph is biderctional/undirected*/
struct listnode *listnode_insert( struct listnode *list_head, int vertx, int weight ){
  struct listnode *new = calloc( 1, sizeof( struct listnode ) );
  new->vertex.vertx = vertx;
  new->vertex.weight = weight;
  new->next = list_head;
  return new;
}

void add_edge( Graph g, int x, int y, int weight ){
  g->G[x] = listnode_insert( g->G[x], y, weight );
  g->G[y] = listnode_insert( g->G[y], x, weight );
  g->n_of_edges++;
}
/*------ ------------------------------------------------------------*/
/*Pqueue ------------------------------------------------------------*/
typedef struct pqueue {
  Elements *elements;
  int maxCapacity;
  int currSize;
  int *lookup_vertx_idx;
}*Pqueue;

Pqueue new_pqueue( int maxSize ){
  Pqueue new_Pq = calloc( 1, sizeof( struct pqueue ) );
  new_Pq->elements = calloc( maxSize, sizeof( struct elements));
  new_Pq->maxCapacity = maxSize;
  new_Pq->lookup_vertx_idx = calloc( maxSize, sizeof( int ));
  for( int i = 0; i < new_Pq->maxCapacity; i++){
    new_Pq->lookup_vertx_idx[i] = inf;
  }
  
  return new_Pq;
}

int is_empty( Pqueue pq ){
  return !(pq->currSize);
}
int pqkey( Elements element ){
  return element.weight;
}

int father_idx( int idx ){
  return  (idx-1)/2;
}

int leftchild_idx( int idx){
  return idx*2+1;
}

int rightchild_idx( int idx ){
  return idx*2+2;
}

void swap( Elements *a, Elements *b ){
  Elements tmp = *a;
  *a = *b;
  *b = tmp;
  return;
}


void heapify_up(Pqueue pq, int idx){
  if( idx > 0 ){
    if( pqkey( pq->elements[ father_idx( idx )] ) > pqkey( pq->elements[ idx ] )  ){
      swap( &pq->elements[ father_idx( idx ) ], &pq->elements[ idx ] );
      /*???*/
      pq->lookup_vertx_idx[ pq->elements[ father_idx( idx ) ].vertx ] = father_idx( idx );
      pq->lookup_vertx_idx[ pq->elements[ idx ].vertx  ] =  idx ;
      heapify_up( pq, father_idx( idx ) );
    }
  }
  return;
}

/*void heapify_down( Pqueue pq, int idx ){
  if( idx*2 + 1 <= pq->currSize){
      int child = leftchild_idx( idx );
      if( pqkey( pq->elements[ rightchild_idx( idx ) ] ) < pqkey( pq->elements[ child ] ) ){
        child = rightchild_idx( idx );
      }
      /*child = ( pqkey( rightchild_idx( idx ) ) < pqkey( leftchild_idx( idx ) ) ) ?  rightchild_idx( idx ) : leftchild_idx( idx );*/

      /* child < father idx then swap*/
      /* heapify recursively new child*/
      /*if( pqkey( pq->elements[child] ) < pqkey( pq->elements[idx] ) ){
          swap(  &pq->elements[ child ], &pq->elements[ idx ] );
          pq->lookup_vertx_idx[ pq->elements[ child ].vertx ] = child;
          pq->lookup_vertx_idx[ pq->elements[ idx ].vertx ] = idx;
          heapify_down( pq, child );
      }
  }
  return;
}*/


void heapify_down( Pqueue pq, int idx ){
  if( idx*2 + 1 <= pq->currSize){
      int child;
      if( 2*idx + 1 == pq->currSize ){
        child = leftchild_idx( idx );
      }else{
        if( pqkey( pq->elements[ rightchild_idx( idx ) ] ) < pqkey( pq->elements[ leftchild_idx( idx ) ] ) ){
          child = rightchild_idx( idx );
        }else{
          child = leftchild_idx( idx );
        }
      }
      
      /*child = ( pqkey( rightchild_idx( idx ) ) < pqkey( leftchild_idx( idx ) ) ) ?  rightchild_idx( idx ) : leftchild_idx( idx );*/

      /* child < father idx then swap*/
      /* heapify recursively new child*/
      if( pqkey( pq->elements[child] ) < pqkey( pq->elements[idx] ) ){
          swap(  &pq->elements[ child ], &pq->elements[ idx ] );
          pq->lookup_vertx_idx[ pq->elements[ child ].vertx ] = child;
          pq->lookup_vertx_idx[ pq->elements[ idx ].vertx ] = idx;
      }
      heapify_down( pq, child );
  }
  return;
}

/*extracts the minimum value from the heap ds*/
Elements extract( Pqueue pq ){
  Elements root = pq->elements[0];
  swap( &pq->elements[0], &pq->elements[pq->currSize-1] );
  pq->lookup_vertx_idx[ pq->elements[0].vertx ] = 0;
  pq->lookup_vertx_idx[ pq->elements[pq->currSize-1].vertx ] = inf;
  pq->currSize--;
  heapify_down( pq, 0);
  
  
  return root;
}

void insert( Pqueue pq, Elements element ){
  pq->elements[pq->currSize] = element;
  pq->lookup_vertx_idx[ element.vertx ] = pq->currSize;
  heapify_up( pq, pq->currSize );
  pq->currSize++;
  return;
}

/*returns Element idx of vertex in heap if present, else -1 */
int find( Pqueue pq, int vertex ){
  return pq->lookup_vertx_idx[vertex];
}


/************************************************************************************************************/

void graphPrint( Graph g );


int minCostToSupplyWater(int n, int* wells, int wellsSize, int** pipes, int pipesSize, int* pipesColSize){
  /*Generate an adj. list to represent the graph with n vertices, 
  that represent the houses and an extra vertex at idx = 0 to represent the wells*/
  
  Graph g_pipes = graph_new( n + 1 );
  /*vertex 0 contains the cost/value of the wells*/
  for( int j = 0; j < wellsSize; j++ ){
    add_edge( g_pipes, 0 ,j+1 , wells[j]);
  }
  
  for( int i = 0; i < pipesSize; i++ ){
    /*if edge exists*/
    /*check weight of existing edge*/
    /*keep cheapest*/
    
    add_edge( g_pipes, pipes[i][0] ,pipes[i][1] , pipes[i][2]);
  }
  
  /*Building the MST*/
  /*Note MST is complete when edges = vertices - 1*/
  int cost = 0;
  int *visited = calloc( n+1, sizeof( int ) );

  /*visit vertex 0
  add to a heap ds the adj. vertices*/
  Pqueue pq = new_pqueue( n+1 );
  Elements tmp = { .weight = 0, .vertx = 0 };
  insert( pq, tmp );
  struct listnode *traverser ;
  while( !is_empty( pq )){
    /* pop */
    tmp = extract(pq);
    if( !visited[tmp.vertx] ){
      cost += tmp.weight;
    visited[tmp.vertx] = 1;
    
    /*check all neighbouringh edges*/
    traverser = g_pipes->G[tmp.vertx];
    }

    while( traverser ){
      /*if !visited add new neighbouring elements to the pqueue*/
        Elements  curr_vertex = traverser->vertex;
        if( !visited[curr_vertex.vertx] ){
          /*if exists in pqueue and if new weight < current weight then currentweight = newweight*/
          if( pq->lookup_vertx_idx[ curr_vertex.vertx ] != inf && curr_vertex.weight < pq->elements[ pq->lookup_vertx_idx[ curr_vertex.vertx ] ].weight   ){
            pq->elements[ pq->lookup_vertx_idx[ curr_vertex.vertx ] ].weight = curr_vertex.weight;
          }else { 
            /*else if does not exist/not visited in pqueue -> insert in pqueue*/
            insert( pq, curr_vertex ); 
          }
          
        }
        traverser = traverser->next;  
    }
  }
  return cost;
}

void print2d( int **a, int size1, int size2 ){
  int i, j;
  for( i = 0; i < size1; i++ ){
    printf("[ ");
    for( j = 0; j < size2-1; j++ ){
      printf("%d, ", a[i][j]);
    }
    printf("%d ] ", a[i][j]);
  }
  putchar('\n');
  return;
}

void graphPrint( Graph g ){
  for( int i = 0; i < g->n_of_vertices; i++){
    printf("[%d]->", i );
    struct listnode *tmp = g->G[i];
    while( tmp ){
      printf(" |%d(w:%d)->", tmp->vertex.vertx, tmp->vertex.weight);
      tmp = tmp->next;
    }
    printf("\n");
  }
}

void printpq( Pqueue pq ){
  for( int i = 0; i < pq->currSize; i++){
    printf("idx:%d{ %d, %d} ",i ,pq->elements[i].vertx, pq->elements[i].weight );
  }
  putchar('\n');
  for( int j = 0; j < pq->currSize; j++){
    printf( "vrtx:%d[idx: %d] ", j, pq->lookup_vertx_idx[j]);
  }
  putchar('\n');
  return;
}
int main(){

  /* Test case******************/
  int input_n = 2;
  int wells[] = { 1, 1};
  int wellsSize = sizeof( wells )/ sizeof( wells[0]);

  int pipes[][3] = { {1, 2, 1}, { 1, 2, 2} };
  int pipesSize_r = sizeof(pipes)/sizeof(pipes[0]);
  int pipesColSize = sizeof(pipes[0])/sizeof(pipes[0][0]);

  int **pipes_tmp = calloc( pipesSize_r, sizeof( int *) );
  for( int i = 0; i < pipesSize_r; i++){
    pipes_tmp[i] = calloc( 3, sizeof(int) );
    pipes_tmp[i][0] = pipes[i][0];
    pipes_tmp[i][1] = pipes[i][1];
    pipes_tmp[i][2] = pipes[i][2];
  } 

  int totalcost = minCostToSupplyWater( input_n, wells, wellsSize, pipes_tmp, pipesSize_r, &pipesColSize );
  printf("Total cost: %d", totalcost);
  /*Elements tmp;
  Pqueue test_pq = new_pqueue( 3+1 );
  int arr[][2] = { {0,0}, {3,2}, { 2, 1}, { 1, 3}};
  for( int i = 0 ; i < 4; i++){
    tmp.vertx = arr[i][0]; tmp.weight = arr[i][1];
    insert( test_pq, tmp );
    printpq( test_pq );
    putchar('\n');
  }

  tmp = extract( test_pq);
  printpq( test_pq );
  putchar('\n');

  tmp = extract( test_pq);
  printpq( test_pq );
  putchar('\n');


  tmp = extract( test_pq);
  printpq( test_pq );
  putchar('\n');

  tmp = extract( test_pq);
  printpq( test_pq );
  putchar('\n');
  
  return 0;*/
}