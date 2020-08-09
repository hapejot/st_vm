#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>


int main(  ) {
    void *prim_lib;
    int ( *prim )( const char * );

    prim_lib = dlopen( "bin/libprimitives.so", RTLD_LAZY );
    if( prim_lib != NULL ) {
/* extopenimage = (int (*)(const char *))dlsym(prim_lib,...)
 *        "man dlopen" says that C99 standard leaves casting from
 *               "void *" to a function pointer undefined. The following is the
 *                      POSIX.1-2003 workaround found in man */
        *( void ** )( &prim ) = dlsym( prim_lib, "print" );
/* the following works with gcc, gives no warning even with
 *        -Wall -std=c99 -pedantic options... :D */
/* extopenimage = dlsym(prim_lib, "openimage"); */
        prim( "Hello World" );
    }
    else{
        printf("dlopen failed.\n");
    }
/* ... */
    if( prim_lib != NULL )
        dlclose( prim_lib );
    return EXIT_SUCCESS;
}
