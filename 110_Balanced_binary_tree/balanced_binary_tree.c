#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    int height;
    struct node *left, *right;
};

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

    root->height++;    
    if( key < root->key ){
        root->left = insertNodeTree( root->left, key);
    }else{
        root->right = insertNodeTree( root->right, key);
    }
    
    
    return root;
}
/*
void printTree( struct node *root ){
   if( root == NULL ) {
       printf("[NULL](h:-1) |");
       return;
   }
    printTree( root->left);
    printf("[%d](h:%d) |",root->key, root->height);
    printTree( root->right);
    return;
}*/

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


int main( int argc, char *argv[]){
    struct node **rootTree = calloc(1 , sizeof( struct node *));
    struct node *root = newNode( 5 );
    *rootTree = root;

    insertNodeTree( *rootTree, 1);

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
    printf("\n\n");
}
