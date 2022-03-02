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
struct Node **makeTree(){
    struct Node **root = calloc( 1, sizeof( struct Node* ));
    return root;
}

struct Node *insertTree( struct Node **root, int key ){
    if( !(*root) ){
        struct Node *new_node = calloc( 1, sizeof( struct Node ));
        new_node->key = key;
        return new_node;
    }
    
    if( key < (*root)->key ){
        (*root)->left = insertTree( &( (*root)->left ) , key  );
    }else{
        (*root)->right = insertTree( &( (*root)->right ), key );
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
    if(root==NULL){
        printf("[Empty]");
        return;
    }
    if( (*root)){
        printf("|%d|" , (*root)->key);
        printTree( &((*root)->left));
        printTree( &( (*root)->right ));
    }
    return;
}

/* HashSet /w search() and insert() implmentation*/

/*#define MaxSize 2069*/
typedef struct Node **Root;
struct HashSet{
    Root *root;
    int max;
};



struct HashSet *makeHashSet(int maxSize ){
    struct HashSet *new_h = calloc( 1, sizeof( struct HashSet ));
    new_h->max = maxSize;
    new_h->root = calloc( new_h->max, sizeof( Root ));
    return new_h;
}

int getkey( struct HashSet *h_set, int val ){
    return abs( val % h_set->max );
}

void insert( struct HashSet *h_set, int key ){
    /*(*h_set).root + getkey(h_set, key);*/
    int idx = getkey(h_set, key);
    if( h_set->root[idx] == NULL ){
        /*No root for tree -> no tree*/
        h_set->root[idx] = makeTree();
    }
    *h_set->root[idx] = insertTree( h_set->root[idx], key );
    
    return;
}

void printHashSet( struct HashSet *h_set ){
    for( int i = 0 ; i < h_set->max; i++){
        printf("-------------------------------------\n");
        printf("bucket num.:[%d]\n", i);
        printTree( h_set->root[i] );
        printf("\n");
        printf("-------------------------------------\n\n");
    }
    
    return;
}


/* search() returns ptr to node that contains key else null*/
struct Node *search( struct HashSet *h_set, int key ){
    int idx = getkey( h_set, key);
    if( h_set->root[idx] == NULL ){
        return NULL;
    }
    struct Node *tmp = *(h_set->root[idx]);/*points at root*/
    while( tmp ){
        if( tmp->key == key ){
            return tmp;
        }else if( key < tmp->key ){
            /* key is at left */
            tmp = tmp->left;
        }else{
            /* key is at right */
            tmp = tmp->right;
        }
    }

    return NULL;
}
bool containsDuplicate(int* nums, int numsSize){
/*    struct HashSet **h_set = calloc(1 ,sizeof( struct HashSet *));*/
    struct HashSet *h_set = makeHashSet( numsSize +1 );
    for( int i = 0 ; i < numsSize; i++ ){

        struct Node *tmp = search( h_set, nums[i] );
        if( tmp == NULL  ){
            insert( h_set, nums[i] );
        }else{
            return true;
        }
    }
    /*printHashSet( h_set );*/
    return false;
}




/**/
int main(){
    /*struct Node **treeRoot = makeTree();
    *treeRoot = insertTree( treeRoot, 100);*/
    /*printTree( treeRoot, 0);*/
    /**treeRoot = insertTree( treeRoot,  150);
    *treeRoot = insertTree( treeRoot, 20);
    *treeRoot = insertTree( treeRoot, 15);
    *treeRoot = insertTree( treeRoot, 25);
    printTree( treeRoot);
    printf("\n");*/

    
    /*printHashSet( hash_set );*/
    /*[1,2,3,1]*/
    /*[1,2,3,4]*/
    /*[1,5,-2,-4,0]
*/
    int arr[] = {1, 5, -2, -4, 0};
    int size = sizeof(arr) / sizeof( arr[0]);
    struct HashSet *hash_set = makeHashSet( size );

    if( containsDuplicate( arr, size )){
        printf("There was a duplicate\n");
    }else{
        printf("There wasn't a duplicate\n");
    }
    
    


    
    
    

    int find = 2;
    /*struct Node *found = search( hash_set, find );
    if( found ){
        printf("key %d was found!\n", found->key );
    }else{
        printf("%d key was not present\n", find);
    }*/



}