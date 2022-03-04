#include <stdio.h>
#include <stdlib.h>

/*HashSet exercise*/

/*need to implement BST*/
/* void insert()*/
/* struct Node *search()*/
/* struct Node *delete() ??? <--- DO I really need this? */ 

struct node{
    int key;
    struct node *left;
    struct node *right;
};

struct node *newNode( int key ){
    struct node *new_node = calloc( 1, sizeof( struct node ) );
    new_node->key = key;
    return new_node;
}


/*BST*/
struct bst{
    struct node **root;
    int max;
};

/*returns a pointer to root of an empty BST*/
struct bst *newTree( int maxSize ){
    struct bst *new_rTree = calloc( 1, sizeof( struct bst  ));
    new_rTree->root = calloc( 1, sizeof( struct node *));
    new_rTree->max = maxSize;
    return new_rTree;
}

void insert( struct node **root, int key){
    
    if( (*root) == NULL ){
        (*root) = newNode( key );
        return;
    }
    if( key < (*root)->key ){
        insert( &((*root)->left), key );
    }else{
        insert( &((*root)->right), key );
    }
    return;
}

void insertBST( struct bst *treeRoot, int key   ){
    insert( treeRoot->root, key );
    return;
}

struct node *searchBST( struct bst *treeRoot, int key ){
    struct node *tmp = *(treeRoot->root);
    while( tmp && tmp->key != key ){
        if( key < tmp->key ){
            tmp = tmp->left;
        }else{
            tmp = tmp->right;
        }
    }
    return tmp;
}
void printNode( struct node *root ){
    if( root ){
        printf("[%d] " , root->key );
        printNode( root->left );
        printNode( root->right );
    }
    return;
}
void printBST( struct bst *treeR ){
    if( treeR->root == NULL ){
        printf("No root, tree is empty.\n");
        return;
    }
    printNode( *(treeR->root) );
    return;
}

/*Hash set implmentation*/
#define maxSizeHash 7 /*2069*/

struct hashSet{
    struct bst **Roots;/*array of trees ptr struct bst*/
    int hash_maxSize;
};


struct hashSet *newHashSet( int maxSize ){
    struct hashSet *new_hset = calloc( 1, sizeof( struct hashSet ));
    new_hset->Roots = calloc( maxSize, sizeof( struct bst *) );/* array of bst trees*/
    new_hset->hash_maxSize = maxSize;
    return new_hset;
}

struct node *searchHashSet(  struct hashSet *h_set, int key   ){

}
int getKey( struct hashSet *h_set, int val ){
    return abs( val%h_set->hash_maxSize);
}

void insertHashSet( struct hashSet *h_set, int key  ){
    int idx = getKey( h_set, key );
    /*accesses the hset that contains an array of bst Trees called Roots*/
    if( h_set->Roots[idx]  == NULL ){
         h_set->Roots[idx] = newTree( h_set->hash_maxSize );
    }else{
        struct node *tmp = searchBST( h_set->Roots[idx], key );
        if(tmp && tmp->key == key ){
            return;
        }
    }
    insertBST( h_set->Roots[idx], key );
    return;
}


void printHashSet( struct hashSet *h_set ){
    for( int i = 0 ; i < h_set->hash_maxSize; i++ ){
        int idx = getKey( h_set, i );
        printf("Bucket number:[_ %d _]\n", i);
        if(h_set->Roots[idx] == NULL ){
            printf( "Empty bucket: :(\n" );
        }else{
            printBST( h_set->Roots[idx] );
        }
        printf("\n---------------------------------------------\n\n");
    }
    return;
}
/*struct Node *searchHashSet(  )*/

/*
Given two integer arrays nums1 and nums2, return an array of their intersection. Each element in the result must be unique and you may return the result in any order.

Example 1:
    Input: nums1 = [1,2,2,1], nums2 = [2,2]
    Output: [2]

Example 2:
    Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
    Output: [9,4]
    Explanation: [4,9] is also accepted.


*/

/**
 * Note: The returned array must be malloced.
 */
int* intersection(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize){
    
    return NULL;
}


int main( int argc, char *argv[] ){
    /*struct bst *nTree = newTree( 7 );
    printBST( nTree );
    insertBST( nTree, 8 );
    insertBST( nTree, 3 );
    insertBST( nTree, 10 );

    insertBST( nTree, 1 );
    insertBST( nTree, 6 );
    insertBST( nTree, 4 );
    insertBST( nTree, 7 );

    insertBST( nTree, 14 );
    insertBST( nTree, 13 );

    printBST( nTree );
    printf("\n-----------------------------------------------\n\n");
    int searchfor = 1;
    struct node *found = searchBST( nTree, searchfor );
    if( found != NULL ){
        printf("%d is present!\n", found->key );    
    }else{
        printf("%d not found.\n" , searchfor );
    }*/
    


    struct hashSet* new_hs = newHashSet( maxSizeHash );
    
    insertHashSet( new_hs, 8 );
    insertHashSet( new_hs, 15 );

    insertHashSet( new_hs, 7 );
    insertHashSet( new_hs, 14 );
    insertHashSet( new_hs, 14 );/*This wont get added to the hash*/
    printHashSet( new_hs );

}