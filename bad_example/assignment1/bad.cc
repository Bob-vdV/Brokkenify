/*
File that should contain most of the 'mistakes' listed in the abbreviations.
*/

#include <stdio.h>

#define CONST 4
#define ASSIGNTHREE int x = 3;

int main(){
    ASSIGNTHREE
    int Y = x;

    for(int i=0;i<3;i++){
        printf("\n");
    }

    ++x;
    x++;
    x--;
    --x;

//Tab below here, do not touch in any IDE:
	printf("Tab%s", "\n");

	printf("Hello world!!!!!!!!!!!!!\n");printf("hello there\n"); printf("sample text\n");printf("sure hope that the prof doesn't see this\n");

    return 0;
}