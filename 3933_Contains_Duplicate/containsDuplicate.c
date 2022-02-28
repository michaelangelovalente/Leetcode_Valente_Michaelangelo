#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*
https://leetcode.com/problems/contains-duplicate/

Example 1:

Input: nums = [1,2,3,1]
Output: true

Example 2:

Input: nums = [1,2,3,4]
Output: false

Example 3:

Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true
*/

/* Binary tree /w search and insert implementation*/
struct Node{
    int key;
    struct Node *left;
    struct Node *right;
};

/*creates an empty binary tree and return the pointer to its root. This will be used to create a BST*/
struct Node **makeTree( ){
    struct Node **root = calloc( 1, sizeof( struct Node* ));
    return root;
}

struct Node *insert( struct Node **root, int key ){
    if( !(*root) ){
        struct Node *new_node = calloc( 1, sizeof( struct Node ));
        new_node->key = key;
        return new_node;
    }
    
    if( key < (*root)->key ){
        (*root)->left = insert( &( (*root)->left ) , key  );
    }else{
        (*root)->right = insert( &( (*root)->right ), key );
    }
    
    return (*root);
}


/*return pointer to node with key, else returns null*/
struct Node *find( struct Node **root, int key ){
    struct Node *find = (*root);
    while( find && find->key != key ){
        if( key < find->key ){
            find = find->left;
        }else{
            find = find->right;
        }
    }

    return find;
}




void printLevel( int i ){
    for( int j = 0 ; j< i; j++){
        printf("_ ");
    }
    printf("->");
}
void printTree( struct Node **root ){
    if( (*root)){
        printf("|%d|" , (*root)->key);
        printTree( &((*root)->left));
        printTree( &( (*root)->right ));
    }
    return;
}

/* HashSet /w search() and insert() implmentation*/

#define MaxSize 7
struct HashSet{
    struct Node **root;
    int max;
    int currItems;
};



struct HashSet *makeHashSet( int maxSize ){
    struct HashSet *new_h = calloc( 1, sizeof( struct HashSet ));
    new_h->max = MaxSize;
    new_h->root = ( new_h->max, sizeof( struct Node *));
    return new_h;
}

int getkey( struct HashSet *h_set, int val ){
    return val % h_set->max;
}
void insert( struct HashSet *h_set, int key ){
    /*h_set->currItems + getkey(h_set, key) ;
    return;
}

/**/
bool containsDuplicate(int* nums, int numsSize){

    return true;
}




/**/
int main(){
    struct Node **treeRoot = makeTree();
    *treeRoot = insert( treeRoot, 100);
    /*printTree( treeRoot, 0);*/
    *treeRoot = insert( treeRoot,  150);
    *treeRoot = insert( treeRoot, 20);
    *treeRoot = insert( treeRoot, 15);
    *treeRoot = insert( treeRoot, 25);
    printTree( treeRoot);
    printf("\n");

}