#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node;
struct graph;
struct queue;

struct node *new_node( int val );
void print_q( struct queue *q );
struct queue *make_queue();
void enqueue( struct queue *q, int val );
struct node *new_node( int val );
struct graph *make_graph( int n_of_vertices );
void print_graph( struct graph *g);
struct graph *generate( int size );


struct node{
    int val;
    struct node *next;
};


struct graph{
    int vertices, edges;
    struct node **G;
};

struct queue{
    struct node *head, *tail;
};


void print_array( int *a, int size){
    for( int i = 0; i < size; i++){
        printf("[%d]", a[i]);
    }
    printf("\n");
}

void print_q( struct queue *q ){
    if( q->tail == NULL ){
        printf("EMPTY QUEUE.");
    }else{
        struct node *tmp = q->head;
        while( tmp ){
            printf("[%d]->", tmp->val);
            tmp = tmp->next;
        }
    }
    printf("\n");
}

//generates an empty queue
struct queue *make_queue(){
    struct queue *new_q = calloc( 1, sizeof( struct queue ) );
    return new_q;
}

void enqueue( struct queue *q, int val ){
    //if tail == NULL queue is empty
    struct node *new = new_node( val );
    if( q->tail == NULL ){ // queue empty --> tail == head
        q->tail = q->head = new;
    }else{
        q->tail->next = new;
        q->tail = q->tail->next;
    }   

    return;
}

int dequeue( struct queue *q ){
    if( q->tail == NULL ){
        return  -999999;
    }

    struct node *curr = q->head;
    int retval = curr->val;
    q->head = q->head->next;
    if( q->head == NULL ) q->tail = NULL;
    curr->next = NULL;
    free( curr );

    return retval;
}

struct node *new_node( int val ){
    struct node *new = calloc( 1, sizeof( struct node ) );
    new->val = val;
    return new;
}


struct graph *make_graph( int n_of_vertices ){
    struct graph *new_g =  calloc( 1, sizeof( struct graph ));
    new_g->G = calloc( n_of_vertices, sizeof( struct node *) );
    new_g->vertices = n_of_vertices;
    return new_g;
}


void print_graph( struct graph *g){
    int size = g->vertices;
    for( int i = 0; i < size ; i++ ){
        printf("{%d} ->", i);
        struct node *curr = g->G[i];
        while( curr ){
            printf("%d -> ", curr->val);
            curr = curr->next;
        }
        printf("\n");
    }
}

bool is_empty( struct queue *q){
    return q->tail == NULL;
}

struct graph *generate( int size ){
    struct graph *new = make_graph( size );
    struct node *tmp;
    //0 -> 1, 2, 
    new->G[0] = new_node( 1 );
    tmp = new->G[0];
    tmp->next = new_node( 2 );
    

    //1 -> 3, 4, 5
    new->G[1] = new_node( 3 );
    tmp = new->G[1];
    tmp->next = new_node( 4 );
    tmp = tmp->next;
    tmp->next = new_node( 5 );

    //2 -> 6
    new->G[2] = new_node( 6 );

    //6 -> 7
    new->G[6] = new_node( 7 );


    return new;
}

void bfs( struct graph *g ){
    int n_vert = g->vertices;
    int *visited = calloc( n_vert, sizeof( int ));
    int *level = calloc( n_vert, sizeof( int ));
    struct queue *q = make_queue();
    enqueue( q, 0);
    
    while( !is_empty( q ) ){
        int visiting = dequeue( q );
        visited[visiting] = 1;
        struct node *curr = g->G[visiting];
        while(  curr && !visited[curr->val]){
            level[ curr->val ] = level[ visiting ] + 1;
            enqueue( q, curr->val );
            curr = curr->next;
        }
    }

    printf("Nodes: ");
    print_array( visited, n_vert);
    printf("\n");
    printf("Level: ");
    print_array( level, n_vert);
    printf("\n");
    return;
}

int main(){
    struct graph *g = generate( 8 );

    //print_graph( g );

    struct queue *nq = make_queue();
    print_q( nq );
    enqueue( nq, 1 );
    print_q( nq );
    enqueue( nq, 2 );
    enqueue( nq, 3 );
    enqueue( nq, 4 );
    print_q( nq );

    printf("--------------------\n");
    printf("DEQUEUED: %d\n", dequeue( nq ));
    print_q( nq );
    printf("--------------------\n");
    printf("DEQUEUED: %d\n", dequeue( nq ));
    print_q( nq );
    printf("--------------------\n");
    printf("DEQUEUED: %d\n", dequeue( nq ));
    print_q( nq );
    printf("--------------------\n");
    printf("DEQUEUED: %d\n", dequeue( nq ));
    print_q( nq );


    bfs(g);
}