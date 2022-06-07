#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NEGATIVE_INF INT_MIN



typedef struct node Node;

int balance_factor( Node *root);
int max_height( Node *left, Node *right );
Node *right_rotate( Node *root );
Node *left_rotate( Node *root);


Node *new_node( int val );
Node *insert_node( Node *root, int val );
Node *find( Node *root, int val );


typedef struct node{
    int val;
    int height;
    struct node *left, *right;
} Node;



/*printTree Source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/*/
void printTree_util( Node *root , int dist){
    if( root == NULL ){
        dist += 7;
        for( int i = 0; i < dist; i++)
            printf(" ");
         printf("[NULL](h:-1)");
         return;
    }
    dist += 8;
    printTree_util( root->right, dist);

    //distance between nodes
    printf("\n");
    for( int i = 0; i < dist; i++)
        printf(" ");
    printf( "[%d](h:%d)(balF.[%d])\n", root->val, root->height, balance_factor( root ) );
    printTree_util( root->left, dist);

}

void printTree( struct node *root){
    printTree_util( root, 0);
    putchar('\n');
}
/*------------------------------------------------------------------------------------*/


Node *right_rotate( Node *root ){
    Node *tmp = root;
    root = root->left;

    tmp->left = root->right;
    root->right = tmp;
    return root;
}

Node *left_rotate( Node *root){
    Node *tmp = root;
    root=root->right;
    tmp->right = root->left;
    root->left=tmp;
    return root;
}

int balance_factor( Node *root){
    int l = -1, r = -1;
    if( root->left) l = root->left->height;
    if( root->right ) r = root->right->height;
    return l-r;
}

int max_height( Node *left, Node *right ){
    int l_h = -1, r_h = -1;
    if( left ){
        l_h = left->height;
    }
    if( right ){
        r_h = right->height;
    }
    return l_h > r_h? l_h : r_h;
}

Node *new_node( int val ){
    Node *new = calloc( 1, sizeof( int ) );
    new->val = val;
    return new;
}

Node *insert_node( Node *root, int val ){
    if( root == NULL ){
        Node *new = new_node( val );
        return new;
    }

    if( val < root->val){
        root->left = insert_node( root->left, val );
    }else{
        root->right = insert_node( root->right, val);
    }
    
    int bf = balance_factor( root );
    if( abs( bf ) == 2 ){
        //rebalance
        if( bf == -2 ){ // right unbalanced tree --> left_rotate(root)
            //right unbalnced left sub-tree unbalanced --> right_rotate(root->right)
            if( balance_factor( root->right ) == 1 ){
                root->right = right_rotate( root->right );
            }
            root = left_rotate( root );
        }else if( bf == 2 ){ // left unbalanced tree --> right_rotate(root)
            //left unbalanced right sub-tree unbalnaced --> left_rotate(root->left)
            if( balance_factor( root->left ) == -1){
                root->left = left_rotate( root->left);
            }
            root = right_rotate( root );
        }
    }

    root->height = max_height( root->left, root->right ) + 1;
    return root;
}

Node *find( Node *root, int val ){
    struct node *result = root;
    while( result && result->val != val ){
        if( val < result->val ){
            result = result->left;
        }else{
            result = result->right;
        }
    }
    return result;
}

int extract( Node *root, int val){
    struct node *tmp = root, *prev = NULL;
    int result = NEGATIVE_INF;
    
    while( tmp && tmp->val != val){
        prev = tmp;
        if( val <  tmp->val ){
            tmp = tmp->left;

        }else{
            tmp = tmp->right;
        }
    }

    
    if( tmp == NULL ) return result;

    result = tmp->val;

    if( tmp->right && tmp->left ){
        //find the largest node of the left subtree
        struct node *largest = tmp->left;
        while( largest->right ){
            prev = largest;
            largest = largest->right;
        }
        tmp->val = largest->val;
        free( largest );
        prev->right = largest = NULL;


    }
    
    /*else if( tmp->left == NULL && tmp->right){
        
    }else if( tmp->right == NULL && tmp->left ){
        
    }*/

    if( prev->left == tmp){
        prev->left = NULL;
    }else if( prev->right == tmp){
        prev->right = NULL;
    }
    
    
    return result;
}

    

int main(){
    
    struct node *root = new_node( 1 );
    printTree( root );

    for( int i = 2; i <= 8; i++ ){
    printf("\n\n{%d}", i);
    root = insert_node( root, i );
    printTree( root );
    }

    printf("\n\n{%d}", -1);
    root = insert_node( root, -1 );
    printTree( root );
    
    printf("\n----------FIND:\n");
    struct node *found = find( root, 81 );
    if( found == NULL ){
        printf("Value does not exist.\n");
    }else{
        printf("Value: %d\n", found->val);
    }

    printTree( root );
    printf("\n------------------------\n");
    printf("Extracted{ %d }\n", extract( root, 4));
    printTree( root );
}