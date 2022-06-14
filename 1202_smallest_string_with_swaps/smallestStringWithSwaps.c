#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct set;

int find_set( struct set *uf, int a);


void q_sort( char *str, int i, int f);

//quick union disjoint set/union find
struct set{
    int *rank;
    int *p;
    int setSize;
};

void print_array( int *arr, int size ){
    for( int i = 0; i < size; i++ )
        printf("[%d] ", arr[i]);
    putchar('\n');
    return;
}
struct set *make_set( int size ){
    struct set *uf = calloc( 1, sizeof( struct set *));
    uf->rank = calloc( size, sizeof( int ));
    uf->p = calloc( size, sizeof( int ));
    uf->setSize = size;
    for( int i = 0; i < size; i++) uf->p[i] = i;
    return uf;
}

bool is_connected( struct set *uf, int a, int b){
    return find_set( uf, a) == find_set( uf, b);
}

int find_set( struct set *uf, int a){
    if( uf->p[a] == a ){
        return a;
    }
    return uf->p[a] = find_set( uf , uf->p[a]);
}

//union by rank
bool union_set( struct set *uf,int a, int b ){
    int parent_a = find_set( uf, a);
    int parent_b = find_set( uf, b);
    if( parent_a != parent_b ){
        //parent with highest rank is now the new parent
        if( uf->rank[ parent_a ] > uf->rank[ parent_b ] ){
            //parent_a has the  highest rank --> new parent of parent_b
            uf->p[ parent_b ] = parent_a;
        }else if( uf->rank[ parent_a ] < uf->rank[ parent_b ] ){
            //parent _b has the highest rank --> new parent of parent_a
            uf->p[ parent_a ] = parent_b;
        }else{ // both parents has the same rank
            uf->p[ parent_b ] = parent_a;// parent a is the new parent
            uf->rank[ parent_a ]++;
        }
        
        return true;
    }
    return false;
}

/*char *smallestString_sort(  )*/

char * smallestStringWithSwaps(char * s, int** pairs, int pairsSize, int* pairsColSize){
    int size_s = strlen( s );
    int **dict = calloc( size_s, sizeof( int *) );

    //set that contains all the pairs
    struct set *swappable = make_set( size_s );  
    for( int i = 0; i < pairsSize; i++ ){
        union_set( swappable, pairs[i][0], pairs[i][1] );
    }

    //check how many roots there and generate a dictionary with root as key and child nodes of root as values.
    for( int i = 0; i < swappable->setSize; i++ ){
        if( i == find_set( swappable, i )){
            dict[i] = calloc( size_s, sizeof( int ));
            //fill dict[i] with all the node of the set.
            for( int j = 0; j < size_s; j++ ){
                if( is_connected( swappable, i, j )){ // if i and j are part of the same set add j as value of the dictionary
                    dict[i][j] = 1;
                }
            }
        }
    }

    //test print
    printf("\n");
    for( int i = 0; i < swappable->setSize; i++ ){
        if( dict[i] != NULL ){
            print_array( dict[i], swappable->setSize );
        }else{
            printf("Empty\n");
        }
    }
    //

    
    for( int i = 0; i < size_s; i++ ){
        if( dict[i] ){
            char *tmp_str = calloc( size_s+1, sizeof( char ));
            //generate a substring containing only the characters of each set.
            int j;
            for( j = 0; j < size_s; j++){ 
                if( dict[i][j] == 1){
                    //take the char at position j from the original string and place it in the sub-string
                    tmp_str[j] = s[j];
                }
            }
            tmp_str[j+1] = '\0';
            //test
            printf("string: %s\n", tmp_str);
            //sort the substring
            q_sort(tmp_str, 0, strlen(tmp_str));
            printf("string: %s\n", tmp_str);

        }else{//test
            printf("Empty\n");
        }
    }

    return 0;
}

void swap_str( char *s1, char *s2){
    char tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
    return;
}

int partition( char *str, int i, int f ){
    char pivot = str[i];
    int l = i;
    int r = f;
    while( l < r){
        do r--;while(str[r] > pivot);
        do l++; while( str[l] <= pivot && l < r );
        if( l < r ) swap_str( &(str[l]), &(str[r]));
    }
    swap_str( &(str[i]), &(str[r]));
    return r;
}

void q_sort( char *str, int i, int f){
    if( f-i > 1){
        int m = partition( str, i, f );
        q_sort( str, i, m);
        q_sort( str, m+1, f);
    }
    return;
}
int main(){
    
    char s[] = "dcabzf";
    int a[][2] = { {0, 3}, {1, 2}, {0,2}, {4,5}};
    int size_a = sizeof( a )/ sizeof( a[0] );
    int **arr = calloc( size_a, sizeof( int *) );
    int colsize = 2;
    for( int i = 0; i < size_a; i ++ ){
        arr[i] = calloc( 2, sizeof( int ));
        arr[i][0] = a[i][0];
        arr[i][1] = a[i][1];
    }

    printf("\n");
    for( int i = 0; i < size_a;  i++){
        print_array( arr[i], 2);
    }

    char *str  = smallestStringWithSwaps( s, arr, size_a, &colsize);
    
   /*
    printf("str: %s\n", s);
    printf("position: %d\n", partition( s, 0, strlen(s)));
    printf("str: %s\n", s);
    q_sort(s, 0, strlen(s));
    printf("str: %s\n", s);*/

    
}