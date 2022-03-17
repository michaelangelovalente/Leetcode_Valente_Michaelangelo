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
    new->height = -1;
    if( !new ){
        printf("There was a problem with memory allocation.\n");
        exit( EXIT_FAILURE );
    }
    return new;
}

struct node *insertNodeTree( struct node *root, int key ){
    
    if( root == NULL ){
        return newNode(key);
    }
    
    if( key < root->key ){
        root->left = insertNodeTree( root->left, key);
    }else{
        root->right = insertNodeTree( root->right, key);
    }
    return root;
}

void printTree( struct node *root ){
   if( root == NULL ) {
       printf("[NULL](h:-1) |");
       return;
   }
    printTree( root->left);
    printf("[%d](h:%d) |",root->key, root->height);
    printTree( root->right);
    return;
}


/*returns the new root*/
 struct node *rightRotation( struct node **node ){
    struct node *tmp =  (*node)->left;
    (*node)->left = tmp->right;
    return tmp;
}


int main( int argc, char *argv[]){
    struct node **rootTree = calloc(1 , sizeof( struct node *));
    struct node *root = newNode( 2 );
    *rootTree = root;

    insertNodeTree( *rootTree, 1);

    insertNodeTree( *rootTree, 3);
    printTree( *rootTree );
    printf("\n");

    *rootTree = right
}
