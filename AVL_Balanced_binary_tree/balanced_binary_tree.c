#include <stdio.h>
#include <stdlib.h>

struct node{
    int key;
    int height;
    struct node *left, *right;
};

/**
 * @brief 
 * 
 * balanced_binary_tree.c contains the complete operations for an AVL tree
 * 
 * 
 * Need to add: delete()
 */

/*AVL tree*/
struct node *newNode( int key );
struct node *insertNodeTree( struct node *root, int key );



struct node *rightRotation( struct node **node );
struct node *leftRotation( struct node **node);

void rebalance( struct node **node );

/*Utilities*/

void printTree_util( struct node *root , int dist);
void printTree( struct node *root);
int max( struct node *l, struct node *r);

struct node *find( struct node *root, int find );
int balanceFactor( struct node *node );
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
    if( abs( balanceFactor(root) ) == 2 ){
        rebalance( &root );
    }
    return root;
}

/*Applies right rotation operation to a tree and returns the new root*/
struct node *rightRotation( struct node **node ){
    struct node *tmp =  (*node)->left; tmp->height++; (*node)->height--;
    (*node)->left = tmp->right;
    tmp->right = *node;

    (*node)->height = max( (*node)->left, (*node)->right ) + 1;
    tmp->height = max( tmp->left, tmp->right) + 1;

    return tmp;
}

/*Applies left rotation operation to a tree and returns the new root*/
struct node *leftRotation( struct node **node){
    struct node *tmp = (*node)->right; 
    (*node)->right = tmp->left;
    tmp->left = *node;
    (*node)->height = max( (*node)->left, (*node)->right ) + 1;
    tmp->height = max( tmp->left, tmp->right) + 1;
    
    return tmp;
}

int balanceFactor( struct node *node ){
    int l_h = -1 , r_h = -1;
    if( node->left ){
        l_h = node->left->height;
    }
    if( node->right ){
        r_h = node->right->height;
    }
    return l_h - r_h;
}



void rebalance( struct node **node ){
    struct node *tmp = *node;
    int bf = balanceFactor( tmp );

   /* bf == -2 --> right unbalanced */
    /*Case Right unbalanced tree*/
    if( bf == -2 ){
        
        /* bf(y) == 1 : Right unbalanced -> left sub tree*/
        /**
         * @brief 
         *  [x]
         *     \
         *      [y]
         *     /
         * [z]
         * rightRotation(y)
         *  [x]
         *     \
         *      [z]
         *         \
         *          [y]
         */
        if( balanceFactor( tmp->right ) == 1 ){
            tmp->right = rightRotation( &(tmp->right) );
        }
        
        /* bf(z) == -1 : Right unbalanced -> right sub tree --> leftRotation(x)*/
        /**
         * @brief 
         *  [x]
         *     \
         *      [z]
         *         \
         *          [y]
         * 
         * leftRotation(x)
         *      [z]
         *     /   \
         *  [x]     [z]
         */
        tmp = leftRotation( &tmp );
        

    }else if( bf == 2 ){/*bf == 2 --> left unbalanced; */

        /* bf(y) == 1 : Left unbalanced -> right sub tree*/
        /**
         * @brief 
         *       [x]
         *      /  
         *    [y]
         *      \
         *      [z]
         * leftRotation(y)
         *         [x]
         *        /
         *      [z]
         *      /      
         *  [y]
         */
        if( balanceFactor( tmp->left ) == -1){
            tmp->left = leftRotation( &(tmp->left) );
        }

        /* bf(y) == -1 : Right unbalanced -> right sub tree*/
        /**
         * @brief 
         *       [x]
         *      /
         *     [z]
         *    /     
         *  [y]
         * 
         * rightRotation(x)
         *      [z]
         *     /   \
         *  [x]     [z]
         */
        tmp = rightRotation( &tmp );
    }

    /*Case Left unblanced tree*/

    *node = tmp;
    return;
}



/*--------------------Utilities---------------------------------------------------*/
/*printTree Source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/*/
void printTree_util( struct node *root , int dist){
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
    printf( "[%d](h:%d)(balF.[%d])\n", root->key, root->height, balanceFactor( root ) );
    printTree_util( root->left, dist);

}

void printTree( struct node *root){
    printTree_util( root, 0);
    putchar('\n');
}


int main( int argc, char *argv[]){
   
    /*struct node *root = newNode( 3 );
    int tmp[] = {1, 2  };
    int size = sizeof(tmp)/sizeof(tmp[0]);*/
    /*insertNodeTree( root, 25);*/
    /*for( int i = 0; i < size; i++ ){
        insertNodeTree( root, tmp[i] );
    }
    printf("Root of tree is: %d and height is: %d\n", root->key,  root->height);
    printTree( root );
    printf("Balance Factor: %d", balanceFactor( root ));
    printf("\n\n");

    printf("Rebalancing: %d\n", root->key);
    rebalance( &root );
    printTree( root );
    printf("Balance Factor: %d", balanceFactor( root ));
    printf("\n\n");*/
   
    /*struct node *root = newNode( 25 );
    int tmp[] = {20, 36, 10, 22, 12, 30, 40, 28, 38, 48 };*/

    struct node *root = newNode( 1 );
    int tmp[] = { 2, 3, 4, 5, 6, 7, 8 };
    int size = sizeof(tmp)/sizeof(tmp[0]);
    for( int i = 0; i < size; i++ ){
        root = insertNodeTree( root, tmp[i] );
    }
    printf("Root of tree is: %d and height is: %d\n", root->key,  root->height);
    printTree( root );
    printf("Balance Factor: %d", balanceFactor( root ));
    printf("\n\n");

    int number_to_be_found = -7;
    struct node *is_present = find( root, number_to_be_found );
    if( is_present ){
        printf("%d is present.\n", is_present->key);
    }else{
        printf("%d is not present.\n");
    }
    
}
