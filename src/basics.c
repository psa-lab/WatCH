#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
 
void  err_panic ( char  *function,
		  char  *message )
{
  fprintf ( stderr, 
	    "FATAL ERROR: %s (%s)\n", 
	    message, 
	    function );
  exit ( 1 );
}
 
void  err_usage ( char  *message )
{
  fprintf ( stderr, 
	    "USAGE: %s\n", 
	    message );
  exit ( 1 );
}
 
char  *mymalloc ( int  size )
{
  char  *adr;
 
  adr = malloc ( size );
  if ( !adr )
    err_panic ( "", "malloc failed" );
  return ( adr );
}
