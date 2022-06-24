#include <stdio.h>

void print_arr( int *nums, int size ){
    for( int i = 0; i < size; i++) printf("[%d]", nums[i]);
    printf("\n");
}


void moveZeroes(int* nums, int numsSize){
    
    int nonZeroPos = 0;
    for( int curr = 0; curr < numsSize; curr++ ){
        if( nums[curr] != 0){
            nums[nonZeroPos++] = nums[curr];
        }
    }
    while( nonZeroPos < numsSize) nums[nonZeroPos++] = 0;
    return;

}

int main(int argc, char *argv[]){
    //int nums[] = {0,1,0,3,12};
    int nums[] = {-1,1,2,3,12};
    int size = sizeof( nums )/ sizeof( nums[0]);
    printf("Before: ");
    print_arr( nums, size);

    moveZeroes( nums, size);

    printf("After: ");
    print_arr( nums, size);
    
}