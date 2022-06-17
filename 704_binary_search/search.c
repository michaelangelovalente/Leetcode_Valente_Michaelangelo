#include <stdio.h>

int rec_search( int* nums, int start, int end, int target ){
    int m = (end+start)/2;
    if( target < nums[m] ){
        m = rec_search( nums, 0, m, target );
    }else if( target > nums[m]){
        m = rec_search( nums, m+1, end, target);
    }
    return m;
}

int search(int* nums, int numsSize, int target){
    return rec_search(nums, 0, numsSize, target);
}


int main(){
    int nums[] = {-1,0,3,5,9,12}, target = 9, size = sizeof( nums )/ sizeof( nums[0]);
    int result = search( nums, size, target );
    printf("Result: %d\n", result);
    printf("Result value: %d\n", nums[result]);
}