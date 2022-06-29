#include <stdio.h>
#include <string.h>

void reverse_word( char *s, int low, int high){
    int delim = (low + high)/2;
    for( int i = 0; i+low < delim; i++){
        char tmp = s[i+low];
        s[i+low] = s[high-i-1];
        s[high-i-1] = tmp;
    }

}

char *reverseWords(char * s){
    int start = 0, end, i;
    for( i = 0; s[i] != '\0'; i++){

        if( s[i] == ' '){
            end = i;
            reverse_word(s, start, end);
            start = end+1;
        }
    }
    end = i;
    reverse_word(s, start, end);
    return s;
}
