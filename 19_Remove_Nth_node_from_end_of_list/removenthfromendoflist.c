#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode *new_node( int val ){
    struct ListNode *new = calloc(1, sizeof( struct ListNode ));
    new->val = val;
    return new;
}

struct ListNode *insert_node( struct ListNode *head, int val ){
    struct ListNode *new = new_node(val );
    if( head != NULL ){
        new->next = head;
    };
    
    return new;

}

void print_list( struct ListNode *head ){
    while( head ){
        printf("[%d]->", head->val);
        head = head->next;
    }
    printf("\n");
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n){
    struct ListNode *prev=NULL, *curr = head;
    int n_nodes = 0;
    while( curr ){
        curr = curr->next;
        n_nodes++;
    }   
    n_nodes = n_nodes - n;
    curr = head;
    while( n_nodes > 0 && curr ){
        prev = curr;
        curr = curr->next;
        n_nodes--;
    }
    prev->next = curr->next;
    return head;

}

int main(){
    int test[] = { 1, 2, 3, 4 , 5 };
    int size_test = sizeof(test)/sizeof(test[0]);
    struct ListNode *head = NULL;
    for( int i = size_test-1; i >= 0; i--){
        head = insert_node( head, test[i]);
    }
    print_list(head);
    printf("--------------------\n");
    struct ListNode *tmp = removeNthFromEnd( head, 2 );
    print_list( tmp );

    

}