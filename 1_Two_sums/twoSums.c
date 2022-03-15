#include <stdlib.h>
#include <stdio.h>

/*
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.

 

Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 


*/


/*
Pseudocode: 
-- DS used: 
    The HashMap (key = nums[idx],value = idx) will be used to store visited values in the array.
    The HashMap uses a balanced BST ( a.k.a AVL tree ) to manage collisions

Iterate through the nums array.
    if  Hashmap not empty && ( curr = nums[idx] ) - 9  --> result is present in HashMap
        get idx of result 
        get idx of curr
        return final result <-- idx of result, idx of curr
    else add the pair { key <-- ( curr = nums[idx]) , val = idx of curr }in the hashmap
*/

/*BST implementation --> AVL implementation ( need to finish 110_Balanced Binary Tree )*/

