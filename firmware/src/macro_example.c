#include <stdio.h>
#include "lib/list.h"
#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define PASTE2( a, b) a##b
#define PASTE( a, b) PASTE2( a, b)

#define BAD_PASTE(x,y) x##y
#define BAD_STRINGIFY(x) #x

#define SOME_MACRO function_name

LIST(testList);

void macroExample(void)
{
		printf("%s\n",LIST_CONCAT(testList,_list));
    printf( "buggy results:\n");
		printf( "%s\n",STRINGIFY(SOME_MACRO__LINE__));
    printf( "%s\n", STRINGIFY( BAD_PASTE( SOME_MACRO, __LINE__)));
    printf( "%s\n", BAD_STRINGIFY( BAD_PASTE( SOME_MACRO, __LINE__)));
    printf( "%s\n", BAD_STRINGIFY( PASTE( SOME_MACRO, __LINE__)));

    printf( "\n" "desired result:\n");
    printf( "%s\n", STRINGIFY( PASTE( SOME_MACRO, __LINE__)));
}

