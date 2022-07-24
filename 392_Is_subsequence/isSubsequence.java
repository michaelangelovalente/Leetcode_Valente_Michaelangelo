/**
    392. Is Subsequence
    
    Given two strings s and t, return true if s is a subsequence of t, or false otherwise.

    A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

    

    Example 1:

    Input: s = "abc", t = "ahbgdc"
    Output: true
    Example 2:

    Input: s = "axc", t = "ahbgdc"
    Output: false
 */
// 
// [a, b, *c(n-1)] (n)* // [a, h, b, g, d, d (n-1)] *n
// return n-1 == n 
import java.util.ArrayList;

class Solution {
    public boolean isSubsequence(String s, String t) {
        int leftBound = s.length(), rightBound = t.length();
        int leftIdx = 0, rightIdx = 0;
        while( leftIdx < leftBound && rightIdx < rightBound ){
            if( s.charAt(leftIdx) == t.charAt(rightIdx) ){
                leftIdx++;
                rightIdx++;
            }
            rightIdx++;
        }
    return leftIdx == leftBound;       
    }
}



