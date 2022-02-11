#include <stdio.h>
#include <stdlib.h>

#define N = 36
struct listnode {
    int board_pos;
    struct listnode *next;
};

struct graph{
    int n, m; /* vertices and edges*/
    struct listnode **A;
};


typedef  struct graph *Graph;

void *my_calloc( int n_memb, int size){
    void *p = calloc( n_memb, size );
    if( !p ){
        printf( "There was a problem with memory allocation.\n" );
        exit( EXIT_FAILURE );
    }
    return p;
}

Graph make_graph( int n ){
    Graph g = my_calloc( 1, sizeof( struct graph ) );
    g->A = my_calloc( n , sizeof( struct listnode *) );
    g->n = n;
    return g;
}

/* Directed graph x->y*/
void insert_edge( Graph g, int x, int y ){
    struct listnode *tmp = my_calloc( 1, sizeof( struct listnode ) );
    tmp->board_pos = y;
    tmp->next = g->A[x];
    g->A[x] = tmp;
    g->m++;
    return;
}

void print_graph_adjL( Graph g){
    struct listnode *traverser = NULL;
    for( int i = 0 ; i < g->n; i++){
        traverser = g->A[i];
        printf( "[%d]-> ", i );
        while( traverser ){
            printf( " %d |-> " , traverser->board_pos );
            traverser = traverser->next;
        }
        printf("\n");
    }

    return;
}
/* O(6) -> O(1)*/
void add_six_die_edges( Graph g, int currpos , int **board, int colSize, int boardSize, int r, int c  ){
    /*int tmp = currpos +1;*/
    int six_die = 0;
    /*int board_start_pos = board[r][c];*/
    int movebyone;
    movebyone = (r%2 == 0)? -1:1;
    while( six_die++ < 6 && currpos + six_die < 36 ){


       if( c >= colSize ){
           r--;
           if( r%2 == 0 ){/*start from right side of the board*/
            c = boardSize-1;
            movebyone = -1;
           }else{/*else left side*/
            c = 0;
            movebyone = 1;
           }
       }


       if( board[r][c] == -1 ){
           insert_edge( g, currpos, currpos + six_die );
       }else{
           insert_edge( g, currpos, board[r][c] );
       }
       c +=movebyone;
       
    }
}
int snakesAndLadders( int** board, int boardSize, int *boardColSize){
    /*Generate adjList from board*/
    int n_boardsquares = boardSize * *boardColSize;
    Graph g_board = make_graph( n_boardsquares ); 
    int r, c;
    int curr_pos = 0;
    /* */
    for( int i = 0; i < boardSize; i++){
        r = boardSize - 1 - i;
        for( int j = 0; j < *boardColSize; j++ ){
            if ( r%2 == 0 ) { /* start from right side of board */
                c = (*boardColSize) - j - 1;
            }else{ 
                c = j;    
            }
            if( board[r][c] == -1){
                /*add edges from curr pos ->0, ..., currpos-> n-1*/
                /* if at post r,c of board the val != -1 you cannot stay on that position.*/
                add_six_die_edges( g_board, curr_pos, board, *boardColSize, boardSize, r, c  );
                
            }
            curr_pos++;
        }
    }
    print_graph_adjL( g_board);
    return 1;
}


int main(){
    /* [[],[],[],[],[],[]] */
    /* Why doesnt this work????*/
    int arr[6][6] = { { -1,-1,-1,-1,-1,-1 }, { -1,-1,-1,-1,-1,-1 }, { -1,-1,-1,-1,-1,-1 }, { -1,35,-1,-1,13,-1 },{ -1,-1,-1,-1,-1,-1 }, { -1,15,-1,-1,-1,-1 } };;
    int **solution = malloc( 6 * sizeof( int * ));
    for( int i = 0 ; i < 6; i++){
        solution[i] = malloc( 6 * sizeof( int ));
    }


    for( int i = 0; i < 6; i++){
        for( int j = 0; j < 6; j++ ){
            solution[i][j] = arr[i][j];
        }
    }

    for( int i = 0; i < 6; i++){
        for( int j = 0; j < 6; j++){
            printf("[%d] ", solution[i][j]);
        }
        printf("\n");
    }
    /*solution = &arr;*/
    
    printf("\n");
    int boardsize = 6;
    int boardColSize = 6;
    int i = snakesAndLadders(solution, boardsize, &boardColSize );
}