#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
Balanced
Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the left and right subtrees of every node differ in height by no more than 1.

Notes: 
    - Compared to ./AVL_Balanced_binary_tree this version does not store the height of each tree.
    - This is not a complete version of an AVL, since the exercise asks only to calculate the height of a given subtree, we
      just need to create one to test: isBalanced()
    - Height is calculated height(rightTree) - height(leftTree), this means that the complexity of height() will be O(logn) and not O(1);

*/

/**
 * Definition for a binary tree node for the exercise.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/**Tree functions*/
struct TreeNode *newNode( int key);
struct TreeNode *insertNode( struct TreeNode *root, int val );
int balanceFactor( struct TreeNode *root);

/*--------------------Utilities---------------------------------------------------*/
int max( int a, int b);
void printTree_util( struct TreeNode *root , int dist);
int height( struct TreeNode *root);





/*Function implementations*/
struct TreeNode *newNode( int key){
    struct TreeNode *new = calloc( 1, sizeof( struct TreeNode));
    new->val = key;
    return new;
}

/**This is a BST insertNode, therefore it does not contain any rotation operation, but 
 * it is useful to create the example case.**/
struct TreeNode *insertNode( struct TreeNode *root, int val ){
    if( root == NULL){
        struct TreeNode *new = newNode( val );
        return new;
    }else if( val > root->val ){
        root->right = insertNode( root->right, val );
    }else if( val < root->val){
        root->left = insertNode( root->left, val);
    }
    return root;
}


/*--------------------Utilities---------------------------------------------------*/
/*printTree Source: https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/*/
void printTree_util( struct TreeNode *root , int dist){
    if( root == NULL ){
        dist += 7;
        for( int i = 0; i < dist; i++)
            printf(" ");
         printf("[NULL](h:%d)", height(root));
         return;
    }
    dist += 8;
    printTree_util( root->right, dist);

    //distance between nodes
    printf("\n");
    for( int i = 0; i < dist; i++)
        printf(" ");
    printf( "[%d](h:%d)(balF.[%d])\n", root->val, height(root), balanceFactor(root) );
    printTree_util( root->left, dist);

}




/**The leetcode solution*/
int balanceFactor( struct TreeNode *root){
    return height( root->right) - height(root->left);
}

int max( int a, int b){
    return a>b? a: b;
}

int height( struct TreeNode *root){
    if( root == NULL){
        return -1;
    }
    return max( height(root->left), height(root->right))+1;
}


/**The leetcode solution*/
bool isBalanced(struct TreeNode* root){

    if(!root || ( abs( balanceFactor( root )) < 2 && isBalanced( root->left) && isBalanced(root->right) ) ){
        return true;
    }
    return false;
}



int main(int argc, char *argv[]){
    struct TreeNode *root = newNode( 25 );
    struct TreeNode **ptr_root = &root;

    int arr[] = { 20, 36, 10, 22, 12, 30, 40, 28, 33, 48, 13, 14};
    for( int i = 0; i < sizeof( arr )/ sizeof(arr[0]) ; i++){
        root = insertNode( root, arr[i]);
    }
    printTree_util( root, 0 );
    printf("\n");

    if( isBalanced(root )){
        printf("The tree is Balanced\n");
    }else{
        printf("The tree is not Balanced\n");
    }
    
    

}