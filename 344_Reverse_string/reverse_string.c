#include <stdio.h>

void swap( char *s1, char *s2 ){
    char tmp_s = *s1;
    *s1 = *s2;
    *s2 = tmp_s;
}


void reverseString(char* s, int sSize){
    for( int i = 0; i < sSize/2; i++){
        swap( &s[i], &s[sSize-i-1]);
    }
    return;
}

int main(){
    char s[] = {'h','e','l','l','o'};
    int size_s = sizeof(s)/sizeof(s[0]);
    printf("initial: %s\n", s);
    reverseString(s, size_s);
    printf("result: %s\n", s);
}