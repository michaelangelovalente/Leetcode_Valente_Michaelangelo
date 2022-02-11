#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Linked list  utilities*/
struct listnode{
    struct listnode *next;
    int vertex;
};

/*Inserts a new node to a head of a linked list*/
void insertnode( struct listnode **L_head, int n ){
    struct listnode *new_node = calloc( 1, sizeof( struct listnode  ) );
    (*new_node).next = *L_head;
    new_node->vertex = n;
    *L_head = new_node; 
    return;
}


void printNodes( struct listnode **L_head){
    struct listnode *tmp = *L_head;
    if( tmp == NULL ){
        printf("List is empty.\n");
        return;
    }
    while( tmp ){
        printf("[%d]->", tmp->vertex);
        tmp = tmp->next;
    }
    putchar('\n');
}

/*Graph utilities*/
/*adj. list representation*/
struct graph{
    struct listnode **G;
    int n_vertices;
    int n_edges;
};

struct graph *new_graph( int n  ){
    struct graph *g_new = calloc( 1, sizeof( struct graph ) );
    g_new->G = calloc( n, sizeof( struct listnode*) );
    g_new->n_vertices = n;
    g_new->n_edges = 0;
    return g_new;
}

void add_edge( struct graph *g, int x, int y ){
    insertnode( &g->G[x], y );
    insertnode( &g->G[y], x );
    g->n_edges++;
    return;
}

void printGraph( struct graph *g ){
    for( int i = 0; i < g->n_vertices; i++ ){
        printf("[%d]->", i);
        struct listnode *tmp = g->G[i];
        while( tmp ){
            printf( " |%d", tmp->vertex);
            tmp = tmp->next;
        }
        putchar('\n');
    }
}

bool start_dfs(  struct graph *g, int *visited, int start, int end ){
    
    if( start == end){
        return true;
    }
    bool flag = false;

    if( !visited[start]){
        visited[start ] = 1;
        struct listnode *tmp = g->G[start];
        while( tmp ){
            /*
            if( tmp->vertex == end){
                return true;
            }*/
            if( !flag ){
                flag = flag || start_dfs( g, visited, tmp->vertex, end );
            }
            tmp = tmp->next;
        }
    }
    
    return flag;
}

bool dfs( struct graph *g, int start, int end ){
    int *visited = calloc( g->n_vertices, sizeof( int ) );
    bool out = start_dfs( g, visited, start, end );
    free( visited );
    return out;
}

bool validPath(int n, int** edges, int edgesSize, int* edgesColSize, int source, int destination){
    /*Generate graph O( V+ E)*/
    struct graph *g_edges = new_graph( n );
    for( int i = 0; i < edgesSize; i++ ){
        add_edge( g_edges, edges[i][0], edges[i][1] );
    }

    return dfs( g_edges, source, destination );
}

/*10
[[0,7],[0,8],[6,1],[2,0],[0,4],[5,8],[4,7],[1,3],[3,5],[6,5]]
7
5*/


int main(){
        struct graph *gtest = new_graph( 10 );
        int arr[][2] = { {0,7},{0,8},{6,1},{2,0},{0,4},{5,8},{4,7},{1,3},{3,5},{6,5} };
        int size = sizeof( arr) /sizeof(arr[0]);

        for( int i = 0; i < size; i++ ){
            add_edge( gtest, arr[i][0], arr[i][1] );
        }

        printGraph( gtest );
        printf("\n");

        printf("result: %d",  dfs( gtest, 7, 5 ) );
}