#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"
#include "types.h"
#include "basics.h"

int  read_input_file ( char  *filename, 
			 point_pt  points )
{
  FILE      *in;
  point_pt  point;
  char      linebuffer[MAX_LINE_LENGTH];
  int       number_of_points;
  int i, j;

  in = fopen ( filename, "r" );
  if ( in == NULL ) 
    {
      sprintf ( linebuffer, 
		"unable to open file %s", 
		filename );
      err_panic ( "read_input_file", 
		  linebuffer );
    }
  point = points;
  number_of_points = 0;
  while ( fgets ( linebuffer, MAX_LINE_LENGTH, in ) != NULL )
    {
      if ( linebuffer[0] == '#' 
	   || linebuffer[0] == '\0' 
	   || linebuffer[0] == '\n' )
	/* comment line or empty line, skip */
	continue;
      sscanf ( linebuffer, 
	       "%d %lf %lf %lf",
	       &point->type,
	       &point->pos[X],
	       &point->pos[Y],
	       &point->pos[Z] );
      point++;
      number_of_points++;
      if ( number_of_points == MAX_NUMBER_OF_INPUT_POINTS )
	  err_panic ( "read_input_file", 
		      "more than MAX_NUMBER_OF_INPUT_POINTS points" );
    }
  fclose ( in );


  return number_of_points;
}
