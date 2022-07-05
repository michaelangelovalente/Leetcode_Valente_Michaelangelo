#include <stdio.h>
#include <stdlib.h>


struct ListNode{
    int val;
    struct ListNode *next;
};

void print_list( struct ListNode *head ){
    while( head ){
        printf("[%d]->", head->val);
        head = head->next;
    }
    printf("\n");
}

struct ListNode *new_node( int val ){
    struct ListNode *new = calloc( 1, sizeof( struct ListNode ));
    new->val = val;
    return new;
}

struct ListNode *insert_node( struct ListNode *head, int val ){
    struct ListNode *new = new_node( val );
    if( head == NULL ) return new;
    new->next = head;
    return new;
}


struct ListNode* deleteDuplicates(struct ListNode* head){
    
    struct ListNode *prev=head, *curr = head;
    int modified = 0;
    while( curr ){
        
        while( curr->next && curr->next->val == curr->val ){
            struct ListNode *tmp = curr->next;
            curr->next = curr->next->next;
            free(tmp);
            tmp = NULL;
            modified = 1;

        }
        if( modified ){
            modified = 0;
            prev->next = curr->next;
            if( curr == head ){
                head = curr->next;
            }
            free(curr);
            curr = prev->next;
        }else{
            prev = curr;
            curr = curr->next;
        }
        
    }
    return head;
}

int main(void){
    int tmp[] = {1,1,1,2,3};
    int size_tmp = sizeof( tmp )/sizeof( tmp[0] );
    struct ListNode *head;

    for( int i = size_tmp-1; i >= 0 ; i-- ){
        head = insert_node( head, tmp[i]);
    }
    print_list( head );
    printf("-------------------------------------\n");
    head = deleteDuplicates( head );
    print_list( head );

}