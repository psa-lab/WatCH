#ifndef _BASICS_H
#define _BASICS_H

extern void  err_panic ( char  *function,
			 char  *message );

extern void  err_usage ( char  *message );

extern char  *mymalloc ( int  size );

#endif

