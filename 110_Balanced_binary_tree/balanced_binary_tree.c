#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    int height;
    struct node *left, *right;
};


struct node *newNode( int key );
struct node *insertNodeTree( struct node *root, int key );

struct node *rightRotation( struct node **node );
struct node *leftRotation( struct node **node);


/*Utilities*/


void printTree_util( struct node *root , int dist);
void printTree( struct node *root);
int max( struct node *l, struct node *r);

struct node *find( struct node *root, int find );
int balanceFactor( struct node **node );
/*--------------------------------------------------*/

struct node *find( struct node *root, int find ){
    struct node *tmp = root;
    while( tmp  && tmp->key != find ){
        if( find > tmp->key){
            tmp = tmp->right;
        }else{
            tmp = tmp->left;
        }
    }

    return tmp;
}

int max( struct node *l, struct node *r){
    int l_h = - 1, r_h = -1;
    if( l ){
        l_h = l->height;
    }
    if( r ){
        r_h = r->height;
    }
    return l_h > r_h ? l_h : r_h;
}

struct node *newNode( int key ){
    struct node* new = calloc(1, sizeof( struct node ) );
    new->key = key;
    new->height = 0; /* left and right childs are -1*/
    if( !new ){
        printf("There was a problem with memory allocation.\n");
        exit( EXIT_FAILURE );
    }
    return new;
}

struct node *insertNodeTree( struct node *root, int key ){
    
    if( root == NULL ){
        struct node *tmp = newNode(key);
        return tmp ;
    }
    
       
    if( key < root->key ){
        root->left = insertNodeTree( root->left, key);
        
    }else{
        root->right = insertNodeTree( root->right, key);
    }
    /*check which height is greater (L or R ) that is now the height of root*/
    root->height = max( root->left, root->right) + 1;
    return root;
}

/*Applies right rotation operation to a tree and returns the new root*/
struct node *rightRotation( struct node **node ){
    struct node *tmp =  (*node)->left; tmp->height++; (*node)->height--;
    (*node)->left = tmp->right;
    tmp->right = *node;
    return tmp;
}

/*Applies left rotation operation to a tree and returns the new root*/
struct node *leftRotation( struct node **node){
    struct node *tmp = (*node)->right; tmp->height++; (*node)->height--;
    (*node)->right = tmp->left;
    tmp->left = *node;
    return tmp;
}

/* 2 --> left unbalnaced; -2 --> right unbalanceed */
int balanceFactor( struct node **node ){
    int l_h = -1 , r_h = -1;
    if( (*node)->left ){
        l_h = (*node)->left->height;
    }
    if( (*node)->right ){
        r_h = (*node)->right->height;
    }
    return l_h - r_h;
}


/*--------------------Utilities---------------------------------------------------*/

/*Source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/*/
void printTree_util( struct node *root , int dist){
    if( root == NULL ){
        dist += 4;
        for( int i = 0; i < dist; i++)
            printf(" ");
         printf("[NULL](h:-1)");
         return;
    }
    dist += 5;
    printTree_util( root->right, dist);

    //distance between nodes
    printf("\n");
    for( int i = 0; i < dist; i++)
        printf(" ");
    printf( "[%d](h:%d)\n", root->key, root->height );
    printTree_util( root->left, dist);

}

void printTree( struct node *root){
    printTree_util( root, 0);
    putchar('\n');
}


int main( int argc, char *argv[]){
    /*struct node **rootTree = calloc(1 , sizeof( struct node *));*/
    struct node *root = newNode(1); /*newNode( 25 );*/
    int tmp[] = { 2, 3 };/*{20, 36, 10, 22, 12, 30, 40, 28, 38, 48 };*/
    int size = sizeof(tmp)/sizeof(tmp[0]);
    /*insertNodeTree( root, 25);*/
    for( int i = 0; i < size; i++ ){
        insertNodeTree( root, tmp[i] );
    }
    printf("Root of tree is: %d and height is: %d\n", root->key,  root->height);
    printTree( root );
    printf("Balance Factor: %d", balanceFactor( &root ));
    printf("\n\n");

    
    struct node *x = find( root , 25 );
    printf( "Left rotate on %d.\n" , x->key );
    
    x = leftRotation( &x );
    printTree( x );
    printf( "\nRoot is: %d.\n", x->key );
    printf("Balance Factor: %d", balanceFactor( &x ));
    
    /*
    struct node *x = find( root , 20 );
    printf( "Right rotate on %d.\n" , x->key );
    
    x = rightRotation( &x );
    printTree( x );
    printf( "Root is: %d.\n", x->key );
    */

    /*insertNodeTree( *rootTree, 1);

    insertNodeTree( *rootTree, 3);
    insertNodeTree( *rootTree, 4);
    printf("Root: %d\n", root->key );
    printTree( *rootTree );
    printf("\nNo rotation\n");
    printf("\n\n");

    root = rightRotation( rootTree );
    *rootTree = root;
    printf("Root: %d\n", root->key );
    printTree( *rootTree );
    printf("\nRight rotation\n");
    printf("\n\n");

    root = leftRotation( rootTree );
    *rootTree = root;
    printf("Root: %d\n", root->key );
    printTree( *rootTree );
    printf("\nLeft rotation\n");
    printf("\n\n");*/
}
