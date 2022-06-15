
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *s = calloc( 5 , sizeof( char ));
    s[0]= 'a';
    s[1]= 'b';
    s[2]= 'c';
    s[3]= '\0';
    printf("%s\n", s);
    printf("\\n\n");

    s[0] = 'z';
    printf("%s\n", s);

}