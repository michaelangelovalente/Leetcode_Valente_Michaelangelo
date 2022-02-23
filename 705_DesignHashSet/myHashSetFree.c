#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Your MyHashSet struct will be instantiated and called as such:
 * MyHashSet* obj = myHashSetCreate();
 * myHashSetAdd(obj, key);
 
 * myHashSetRemove(obj, key);
 
 * bool param_3 = myHashSetContains(obj, key);
 
 * myHashSetFree(obj);
*/

/*BST  Implementation */

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void printLevel( int level ){
    for( int i = 0; i < level; i++){
        printf("-");
    }
    return;
}
void print( struct TreeNode **root, int level ){
    if( !(*root)){
        return;
    }
    printLevel( level );
    printf( "[%d]\n", (*root)->val );
    level++;
    print( &((*root)->left), level );
    print( &((*root)->right), level );
    return;
}

struct TreeNode *new_node( int val ){
    struct TreeNode *new_node = calloc( 1, sizeof( struct TreeNode ));
    new_node->val = val;    
    return new_node;
}
/*insert*/
void insert( struct TreeNode **root, int val ){
    if( !(*root) ){
        (*root) = new_node(val);
    }else if( val > (*root)->val ){
        insert( &( (*root)->right ), val );
    }else{
        if( (*root)->val == val ) return;
        insert( &((*root)->left), val );
    }
    return;
}

/*search*/
struct TreeNode **search( struct TreeNode **root, int val ){
    if( !(*root) || (*root)->val == val){
        return root;
    }else if( val > (*root)->val ){
        root = search( &(*root)->right, val );
    }else{
        root = search( &(*root)->left, val );
    }
    
    return root;
}

struct TreeNode *largest( struct TreeNode *root ){
    while( root->right ) root = root->right;
    return root;
}
/*delete deletes a node with value == val and returns the root of the tree*/
struct TreeNode **delete( struct TreeNode **root, int val ){
    if( !(*root)) return NULL;

    if( val < (*root)->val  && (*root)->left != NULL){
        (*root)->left = *delete( &( (*root)->left ) , val  );
    }else if( val > ( *root )->val && (*root)->right != NULL ){
        (*root)->right = *delete( &( (*root)->right ) , val ); 
    }else{/* node found */
        if( (*root)->left == NULL && (*root)->right == NULL ){
            free((*root));
            (*root) = NULL;
        }else if( (*root)->left == NULL ){
            struct TreeNode *tmp = (*root)->right;
            free( *root );
            (*root) = tmp;

        }else if( (*root)->right == NULL ){
            struct TreeNode *tmp = (*root)->left;
            free( *root );
            (*root) = tmp;
        }else{
            struct TreeNode *bigL =  largest( (*root)->left );
            (*root)->val = bigL->val;
            (*root)->left = *delete( &((*root)->left), bigL->val );
        }
    }
    return root;
}


typedef struct {
    struct TreeNode **set;
    int numOfItems;
    int maxSize;
} MyHashSet;


MyHashSet* myHashSetCreate() {
    MyHashSet *new_set = calloc( 1, sizeof( MyHashSet ) );
    new_set->maxSize = 10;
    new_set->numOfItems = 0;
    new_set->set = calloc( new_set->maxSize, sizeof( struct TreeNode *) );
    return new_set;
}


void myHashSetAdd(MyHashSet* obj, int key) {
  insert( &(obj->set[ key % obj->maxSize ]), key );
  obj->numOfItems++;
  return;
}

void myHashSetRemove(MyHashSet* obj, int key) {
  struct TreeNode **throw = delete( &(obj->set[ key % obj->maxSize ]) , key );
  return;
}

bool myHashSetContains(MyHashSet* obj, int key) {
    if( obj->set[ key % obj->maxSize  ] == NULL ){
        return false;
    }
    struct TreeNode *result_key = *( search( &(obj->set[ key % obj->maxSize  ]) , key ) );
    if( !result_key ){
        return false;
    }
    return key == result_key->val;
}

void myHashSetFree(MyHashSet* obj) {
    return;
}

void printHashSet( MyHashSet *set ){
    printf( "Max size of hashTable: %d\n", set->maxSize );
    printf( "Number of items inside the Hashtable: %d\n", set->numOfItems );
    for( int i = 0; i < set->maxSize; i++){
        if( set->set[ i ] != NULL ){
            printf("bucket[%d]: \n", i);
            print( &(set->set[i]), 0 );
        }else{
            printf("bucket[%d]: \nempty\n", i);
        }
        printf("\n");
    }

    return;
}

/*
["MyHashSet","add","add","contains","contains","add","contains","remove","contains"]
[[],          [1],   [2],    [1],        [3],    [2],    [2],        [2],    [2]]
*/

int main(){

    MyHashSet *set = myHashSetCreate();
    printHashSet( set );
    printf("--------------- -------------------------  ------\n");
    myHashSetAdd( set, 1 );
    myHashSetAdd( set, 11 );
    myHashSetAdd( set, 2 );
    myHashSetAdd( set, 2 );
    printHashSet( set );

    int contains = 1;
    if( myHashSetContains( set, contains ) ){
        printf("contains %d\n", contains );
    }else{
        printf("does not contain: %d\n", contains);
    }

    /*struct TreeNode **root = calloc( 1, sizeof( struct TreeNode *));
    insert( root , 4);
    insert( root , 5);
    insert( root , 2);
    insert( root , 3);

    insert( root , 0);
    insert( root , 1);

    insert( root , 8);
    insert( root , 23);

    insert( root , 6);
    insert( root , 7);
    
    print( root, 0);
    printf("\n\n");

    struct TreeNode **tmp = search( root, 25);
    if( !(*tmp) ){
        printf("value not present\n");
    }else{
        printf("found: %d", (*tmp)->val);    
    }
    tmp = search( root, 7 );
    if( !(*tmp) ){
        printf("value not present\n");
    }else{
        printf("found: %d", (*tmp)->val);    
    }

    printf("\n\n");
    /*delete( );*/
    /*
    tmp = delete( root, 8);

    printf("%d deleted\n", (*tmp)->val );

    printf("\n");
    print( root, 0);
    printf("\n\n");*/
}