#include <stdio.h>



int search(int* nums, int numsSize, int target){
    int mid = numsSize/2;
    while( nums[mid] != target ){
        if( target < nums[mid]){
            mid = mid/2;
        }else{
            mid = (mid+numsSize)/2;
        }
    }
    return ;
}


int main(){
    int nums[] = {-1,0,3,5,9,12}, target = 9, size = sizeof( nums )/ sizeof( nums[0]);
    int result = search( nums, size, target );
    printf("Result: %d\n", result);
    printf("Result value: %d\n", nums[result]);
}