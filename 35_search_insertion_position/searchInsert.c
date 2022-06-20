#include <stdio.h>



int searchInsert(int* nums, int numsSize, int target){
    int left, right = numsSize-1;
    int mid = left + ( right - left )/ 2;
    
    while( left <= right ){
        mid = left + ( right - left )/ 2;
        if( nums[mid] == target ) return mid;

        if( target < nums[mid]){
            right = mid;
        }else{
            left = mid+1;
        }
    }

    return left;
}