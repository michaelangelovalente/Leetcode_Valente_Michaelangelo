#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int key;
    int val;
} Pair;

/*Linked list*/
typedef struct node{
    Pair val;
    struct node *next;
}Node;


Node *insert( Node *head, Pair val ){
    Node *tmp = calloc( 1, sizeof( struct node ) );
    tmp->val = val;
    tmp->next = head;
    return tmp;    
}

/*returns NULL if item is not present in the linked list.*/
Node *delete( Node *head, Pair val ){
    Node *prev, *curr;
    for( curr = head, prev = NULL; curr != NULL ;prev = curr, curr = curr->next ){
        if( curr->val.key == val.key) break;
    }

    if( curr == NULL ){
        return NULL;
    }else if( prev == NULL ){
        head = head->next;
    }else{
        prev->next = curr->next;
    }
    curr->next = NULL;
    return curr;
    
}


void printList( Node *head){
    while( head ){
        printf("[Key: %d | Val: %d ]->",head->val.key, head->val.val);
        head = head->next;
    }
    printf("\n");
    return;
}


/*HashMap*/
typedef struct {
    Node **buckets;
    int bucketSize;
} MyHashMap;



MyHashMap* myHashMapCreate() {
    MyHashMap *hashM = calloc( 1, sizeof( MyHashMap ));
    hashM->bucketSize = 7;  /*2069;*/
    hashM->buckets = calloc( hashM->bucketSize, sizeof( Pair * ) );
}

int hash( int key , MyHashMap *hashM ){
    return key % hashM->bucketSize;
}

void myHashMapPut(MyHashMap* obj, int key, int value) {
    int bucket_idx  = hash( obj, key );
    Pair tmp = {.key = key, .val = value};
    obj->buckets[ bucket_idx ] = insert( obj->buckets[ bucket_idx ], tmp);
    return;
}

int myHashMapGet(MyHashMap* obj, int key) {
  return 1;
}

void myHashMapRemove(MyHashMap* obj, int key) {
  return;
}

void myHashMapFree(MyHashMap* obj) {
    return;
}

void printHashMap( MyHashMap* obj ){
    for( int i = 0; i < obj->bucketSize; i++ ){
        printf("Bucket idx[%d]: ", i);
        printList( obj->buckets[i] );
    }
    printf("-----------------------------------------  -------------\n");
}

/**
 * Your MyHashMap struct will be instantiated and called as such:
 * MyHashMap* obj = myHashMapCreate();
 * myHashMapPut(obj, key, value);
 
 * int param_2 = myHashMapGet(obj, key);
 
 * myHashMapRemove(obj, key);
 
 * myHashMapFree(obj);
*/


int main( ){
    /*Pair tmp = { .key = 1, .val = -1};
    Node *head =  insert( head, tmp );
    printList( head );

    tmp = (Pair){ .key = 2, .val = -2};
    head = insert( head, tmp);
    printList( head );
    
    tmp = (Pair){ .key = 3, .val = -3};
    head = insert( head, tmp);
    printList( head );

    tmp = (Pair){ 4, -4};
    head = insert( head, tmp);
    printList( head );

    Pair del_tmp = { .key = 3, .val = 909 };
    Node *tmp_node = delete( head, del_tmp );
    printf("\nDeleted:[key%d|val:%d] \n", tmp_node->val.key, tmp_node->val.val );
    printList( head );*/

}