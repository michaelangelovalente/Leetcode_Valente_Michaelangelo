#include <stdio.h>
#include <stdlib.h>

void print_array( int *a, int size){
    for( int i = 0; i < size; i++){
        printf("[%d]", a[i]);
    }
    printf("\n");
}
int max( int a, int b){
    return a>b ? a:b;
}

int deleteAndEarn(int* nums, int numsSize){
    int *points = calloc( nums[0]+1, sizeof( int )  );//arbitrary size for points table. We update this with the maxValue available inside nums
    int maxVal = nums[0];
    int  oldSize, pointsSize = oldSize = maxVal+1;
    int *memo;


    for( int i = 0; i < numsSize; i++){ //We iterate over nums to fill the points table. points table will contain how much points each number will have 
        if( nums[i] > maxVal ){
            maxVal = nums[i];
            oldSize = pointsSize;
            pointsSize = maxVal + 1;
            points = realloc( points, pointsSize * sizeof( int ) );
            for( int j = oldSize; j< pointsSize; j++ ) points[j] = 0;
            //print_array( points, maxVal+1);
        }
        
        points[ nums[i] ] += nums[i];
        //print_array( points, maxVal+1);
    }
    
    //print_array( points, maxVal+1);
    memo = calloc( pointsSize, sizeof(int));
    memo[0] = 0, memo[1] = points[1];

    for( int i = 2; i <= maxVal; i++ ){
        memo[i] = max( points[i] + memo[i-2], memo[i-1]); 
    }

    print_array( memo, maxVal+1);
    int finalRes = memo[maxVal];
    free(memo);
    free(points);
    
    return finalRes;
}



int main( int argc, char *argv[]){
   // int nums[] = {3,2,3,2,3,4};
   int nums[] = {3,4,2};
    int size = sizeof(nums)/sizeof(nums[0]);
    printf("Result:%d\n", deleteAndEarn( nums, size ));
}