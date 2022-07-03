#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */


int findBound( int *nums, int begin, int end, int target, bool first_half ){

    while( begin<=end ){
        int mid = (begin + end )/2;
        if( nums[mid] == target){
            if( first_half ){  
                if( mid == begin || nums[mid-1] != target){
                     return mid;
                }
                end = mid -1;
            }else{//second half bound
                if( mid == end || nums[mid+1]!= target){
                     return mid;
                }
                begin = mid+1;
            }
        }else if( nums[mid] > target ){//first half is usefult
            end = mid-1;
        }else if( nums[mid] < target ){ // second half is useful
            begin = mid + 1;
        }
    }
    return -1;
}
int* searchRange(int* nums, int numsSize, int target, int* returnSize){
    *returnSize = 2;
    int *result = calloc(2, sizeof( int ));
    result[0] = result[1] = -1;
    if( numsSize >= 1){
        result[0] = findBound(nums, 0, numsSize-1, target, true);
        result[1] = findBound(nums, 0, numsSize-1, target, false);            
    }
    
    return result;
}


int main(void){
    //int test[] = {5,8,8,8,8,8,8,8,8,9,10}, target = 8;
    int test[] = {1,2,3,3,3,3,3,3,4,5,6,7,8,9,10,11,12,13}, target = 3;
    int size = sizeof(test)/sizeof(test[0]);
    int retSize =2;

    
    int *result = searchRange( test, size, target, &retSize );
    printf("Result[%d, %d]\n", result[0], result[1]);
    
   //printf("Position: %d\n", binarySearch( test, 0, size-1, target));
}