#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

void printList( struct ListNode *head ){
    while( head ){
        printf("[%d]->", head->val);
        head = head->next;
    }
    printf("\n");
    return;
}

struct ListNode *new_node( int val){
    struct ListNode *new = calloc(1, sizeof( struct ListNode));
    new->val = val;
    new->next = NULL;
    return new;
}

struct ListNode *insert_head( struct ListNode *head, int val ){
    struct ListNode *new = new_node( val );
    if( head == NULL ){
        return new;
    }
    new->next = head;
    return new;
}
/**/


struct ListNode* middleNode(struct ListNode* head){
    
    int num_of_nodes = 0;
    struct ListNode *tmp = head;
    while( tmp ){
        tmp = tmp->next;
        num_of_nodes++;
    }
    num_of_nodes = num_of_nodes/2;
    tmp = head;
    while( tmp ){
        if( num_of_nodes <= 0 ){
            return tmp;
        }
        tmp = tmp->next;
        num_of_nodes--;
    };

    return NULL;
}

int main(void){
    int arr[] = {1,2,3,4,5,6};
    int size = sizeof( arr )/sizeof( arr[0] ), tmp = size;
    struct ListNode *head = NULL;
    while( tmp != 0){
        tmp--;
        head = insert_head( head, arr[tmp]);
    }
    printList( head );
    printf("Head:%d\n", head->val);
    printf("-----------------\n");
    head = middleNode( head );
    printList(head);

}