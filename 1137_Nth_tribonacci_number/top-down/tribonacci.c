/**
 * @file tribonacci.c
 * @author Michaelangelo valente
 * @brief 
 * @version 0.1
 * @date 2022-06-02
 * 
 * @copyright Copyright (c) 2022
 * 
 * 
    The Tribonacci sequence Tn is defined as follows: 

    T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

    Given n, return the value of Tn.

    

    Example 1:

    Input: n = 4
    Output: 4
    Explanation:
    T_3 = 0 + 1 + 1 = 2
    T_4 = 1 + 1 + 2 = 4
    Example 2:

    Input: n = 25
    Output: 1389537
    

    Constraints:

    0 <= n <= 37
    The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
 * 
 */



int tribonacci_dp( int *memo, int n){
    if( n <= 2){
        return n == 0 ? 0 : 1;
    }
    if( memo[n] == 0){
        memo[n] = tribonacci_dp( memo, n - 3 ) + tribonacci_dp( memo, n-2) + tribonacci_dp( memo, n-1 );
    }
    return memo[n];
}

int tribonacci(int n){
    int *memo = calloc( n+1, sizeof( int ));
    int result = tribonacci_dp( memo, n );
    return result;
    
}