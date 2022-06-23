#include <stdio.h>
#include <stdlib.h>
//solution uses O(1) space

void print_arr( int *arr, int size){
    for( int i = 0; i < size; i++) printf("[%d]", arr[i]);
    printf("\n");
    return;
}

void swap( int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}


void reverse( int *arr, int start ,int end){
    while( start < end){
        swap( &(arr[start++]), &(arr[end--]));
    };
}
void rotate(int* nums, int numsSize, int k){
    k=k%numsSize;
    if( numsSize > 1 && k > 0){
        reverse( nums, 0, numsSize-1);
        reverse( nums, k, numsSize-1);// 0-indexes position
        reverse( nums, 0, k-1);    
    }
}


int main(){
    int nums[] = {1,2,3,4,5,6,7}, k = 3, size = sizeof(nums)/sizeof(nums[0]);
    rotate( nums, size, k);

}
