#include <stdio.h>
#include <stdbool.h>
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

bool hasCycle(struct ListNode *head) {
    struct ListNode *fast, *slow;
    slow = fast = head;
    while( fast != NULL && fast->next != NULL ){
        slow = slow->next;
        fast = fast->next->next;
        if( fast == slow ) return true;
    }
    return false;
}