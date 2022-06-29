#include <stdio.h>
#include <stdlib.h>
/**
 * 
 * Note: The returned array must be malloced, assume caller calls free().
 * 
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize){
    int left = 0, right = numbersSize-1;
    int *ret = calloc(2, sizeof( int ));
    *returnSize = 2;
    ret[0] = ret[1] = -1;
    while( left < right ){
        int result = numbers[left] + numbers[right];
        if( result == target){
            ret[0] = left+1, ret[1] = right+1;
            left = right;
        }
        if( result<target ){
            left++;
        }else{
            right--;
        }
    }
    return ret;
}



int main(){
    int numbers[] = {2,7,11,15}, target = 9;
    int size_n = sizeof(numbers)/sizeof(numbers[0]);
    int size_ret = 2;
    int *finalResult = twoSum(numbers, size_n, target, &size_ret );
    printf("Target:%d = idx(%d):%d + idx(%d):%d\n", target, finalResult[0] ,numbers[ finalResult[0]-1], finalResult[1], numbers[finalResult[1]-1]);

}