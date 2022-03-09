#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


/*BST implementation
    insert()
    search()
    Do not need delete() for this exercise.
*/
struct node{
    int key;
    struct node *left, *right;
};

/*Create node*/
struct node *createNode( int key ){
    struct node *new_node = calloc( 1, sizeof( struct node ));
    new_node->key=key;
    return new_node;
}


/*Insert Node*/
struct node *insertNode( struct node *root, int key ){
    if( root == NULL ){
        return createNode( key );
    }
    if( key < root->key){
        root->left = insertNode( root->left , key );
    }else{
        root->right = insertNode( root->right, key );
    }
    return root;
}

/*Search node*/
/* returns NULL if key is not present else ptr to node that contains the key*/
struct node *searchNode( struct node *root, int key ){
    if( root == NULL || root->key == key ){
        return root;
    }

    if( key < root->key ){
        root->left = searchNode( root->left, key );
    }else{
        root->right = searchNode( root->right, key );
    }

    return NULL;
}

bool containsNode( struct node *root, int key ){
    struct node *tmp = searchNode( root, key );
    return ( tmp != NULL );
}

void printTree( struct node *root ){
    if( root == NULL ){
        return;
    }
    printf("%d| ", root->key);
    printTree( root->left );
    printTree( root->right );
}
/*Hashset implementation
    create()
    add()
    --- do not need to implement remove()
    --
    replace search() with contains()
    
*/

struct hashSet{
    struct node **bst;
    int maxSize;
};

struct hashSet *createHs( int size){
    struct hashSet *new_hs = calloc( 1, sizeof( struct hashSet ));
    new_hs->maxSize = size;
    new_hs->bst = calloc( new_hs->maxSize , sizeof( struct node *));
    
    return new_hs;
}

int getkey( struct hashSet *hs, int val ){
    return abs(val%hs->maxSize);
}

void add( struct hashSet *hs, int val ){
    int idx = getkey( hs, val );
    if( hs->bst[idx] == NULL ){
        hs->bst[idx] = createNode( val );
    }else if( !containsNode( hs->bst[idx], val  ) ){
        hs->bst[idx] = insertNode( hs->bst[idx], val );
    }
    return;
}


bool containsHs( struct hashSet *hs, int val  ){
    int key = getkey( hs, val );
    struct node *tmp = searchNode( hs->bst[key], val);
    return (tmp != NULL && tmp->key == val);
}

void printHashSet( struct hashSet *hs ){
    for( int i = 0; i < hs->maxSize; i++){
        printf("Bucket num[%d]\n", i);
        if( hs->bst[i] == NULL ){
            printf("Bucket is empty :(");
        }else{
            printTree( hs->bst[i] );
        }
        printf( "\n");
    }
}

/*
Write an algorithm to determine if a number n is happy.

A happy number is a number defined by the following process:

Starting with any positive integer, replace the number by the sum of the squares of its digits.
Repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1.
Those numbers for which this process ends in 1 are happy.
Return true if n is a happy number, and false if not.


Example 1:

Input: n = 19
Output: true
Explanation:
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
Example 2:

Input: n = 2
Output: false

*/
int sumOfSquaresOfdigits( int n ){
    int d;
    int res = 0;
    while( n > 0){
        d = n%10;
        res += ( ( int ) pow( (double) d , 2.0 ));
        n = n/10;
    }

    return res;
}

bool isHappy(int n){
    struct hashSet *unique = createHs( 7 );/*2069*/
    int res = sumOfSquaresOfdigits( n );
    while( res != 1 ){
        
        if( containsHs( unique, res ) ){
            break;
        }
        add( unique, res );
        res = sumOfSquaresOfdigits( res );
    }
    return (res == 1);    
}

