/******************************************************************************

WatCH License Agreement

This License agreement with MSU covers your use of the WatCH software
developed in the Protein Structural Analysis and Design Lab at MSU
by Paul C. Sanschagrin and Leslie A. Kuhn, Dept. of Biochemistry and
Molecular Biology, Michigan State University, East Lansing, MI 48824;
(517) 353-8745 (e-mail: kuhnl@msu.edu)

1.  Description of Product.

As used in this agreement, "Product" means the full, integrated Version
1 of the "WatCH" software for analyzing conservation of water sites in
related protein structures, and any associated documentation, developed by
Michigan State University personnel and copyrighted by the Michigan State
University Board of Trustees.

2.  License.

MSU grants to you a non-exclusive, perpetual, non-transferable license to use
the Product for your internal purposes on site.  You may develop derivatives
of the Product for internal use, provided MSU copyright notices remain intact
and that the contributions of MSU personnel as outlined in (3) are included.
You may make copies of the software as needed for your internal purposes,
provided MSU copyright notices remain intact and the contributions of MSU
personnel outlined in (3) are included.  Neither the Product, Product copies,
or derivatives from the Product may be transferred, licensed, or sold.

3.  Acknowledgements.

You agree to acknowledge the use of WatCH in publications or
presentations by citing the following reference:

P. C. Sanschagrin and L. A. Kuhn (1998) "Cluster Analysis of Consensus Water
Sites in Thrombin and Trypsin Shows Conservation Between Serine Proteases and
Contributions to Ligand Specificity", Protein Science 7, 2054-2064.

4.   Prohibited Uses of the Product.

You may not make copies of the Product which do not contain the
notifications of copyright exactly as provided in the Product supplied
to you by MSU.

You may not transfer or assign your rights under this License
without the prior express written consent of MSU.

5.   Prohibited Uses of the University Name and Marks.

You agree to not use the MSU name or marks in publicity, advertising,
fund-raising, or similar activities without the prior written approval
of MSU.

6.   Intellectual Property.

Michigan State University retains title to Product.  You agree
to use reasonable efforts to protect the Product from unauthorized use
or reproduction.  All rights not specifically granted in this License
are reserved by MSU.

7.   Warranty.

MSU MAKES NO OTHER WARRANTY, EXPRESS OR IMPLIED, TO YOU OR ANY
OTHER PERSON OR ENTITY.  SPECIFICALLY, MSU MAKES NO WARRANTY OF
MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE OF PRODUCT.  MSU
WILL NOT BE LIABLE FOR SPECIAL, INCIDENTAL, CONSEQUENTIAL, INDIRECT OR
OTHER SIMILAR DAMAGES, EVEN IF MSU OR ITS EMPLOYEES HAVE BEEN ADVISED OF
THE POSSIBILITY OF SUCH DAMAGES.  IN NO EVENT WILL MSU LIABILITY FOR ANY
DAMAGES TO YOU OR ANY PERSON EVER EXCEED ANY FEE PAID FOR THE
LICENSE TO USE THE PRODUCT, REGARDLESS OF ANY FORM OF THE CLAIM.

Additional statements by employees of MSU, such as correspondence or
oral presentations, do not constitute warranties by MSU and should not
be relied upon.

8.   Supplementary Provisions.

This License represents the entire understanding and agreement between
MSU and you regarding the Product, and supersedes any prior
purchase order, communications, advertising, or representations.  This
License may be modified only in a written amendment signed by an
authorized MSU officer.  If any provision of this License shall be
unlawful, void, or for any reason unenforceable, it shall be deemed
severable from, and shall in no way affect the validity or
enforceability of the remaining provision of this agreement.  This
License shall be governed by Michigan law.


9.   Termination.

In the event that either party hereto commits any breach of or default
in any of the terms or conditions of this Agreement, and also shall fail
to remedy such default or breach within ninety (90) days after receipt
of written notice of such breach or default, the party giving notice may
at its option and in addition to any other remedies which it may have by
law, terminate this Agreement by sending notice of termination in
writing to the other party.  Such termination shall be effective as of
the date of the receipt of such notice.
******************************************************************************/

/******************************************************************************
P. Sanschagrin -- 28-Aug-00

cluster_main -- main program to perform clustering of a series of points
  The clustering function is called independently, so it should be able to
  be easily changed from complete linkage at a later date if desired. 
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "defs.h"
#include "types.h"
#include "basics.h"
#include "complete_link_clustering.h"
#include "output_cluster_points.h"

#define TRAC

int main (int argc, char **argv) {
  
  FILE *fp_in,                    /* input file                      */
    *fp_out;                      /* output file                     */
  point_pt input_points,          /* input points                    */
    cluster_points;               /* output cluster points           */
  char infilename[256],           /* input filename                  */
    outfilename[256],             /* ouput filename                  */
    linebuffer[MAX_LINE_LENGTH];  /* line holder                     */
  double threshold;               /* clustering threshold            */
  int number_of_input_points,     /* number of input points          */
    number_of_cluster_points,     /* number of output/cluster points */
    outfile_flag;                 /* flag for non-default out file   */
  int i, j;

  /* Usage Check */
  if ((argc != 2) && (argc != 3) && (argc != 4)) {
    printf( "Usage: %s <point file> [<clustering threshold>] "
	    "[<output file>] \n"
	    "   (if threshold is not given, %4.2f will be used)\n"
	    "   (for the output file option to be used, the threshold must"
	    " be set explicitly)\n"
            "   (point file must in form of <integer label> <X> <Y> <Z>)\n",
	    argv[0], DEFAULT_THRESHOLD); 
    exit (-1);
  }
  
  /* Parse CL args */
  strcpy(infilename, argv[INPUT_CLARG_POS]);
  outfile_flag = 0;
  if ((argc == 3) || (argc == 4)) 
    threshold = atof (argv[THRESHOLD_CLARG_POS]);
  else
    threshold = DEFAULT_THRESHOLD;
  if (argc == 4)
    {
      strcpy (outfilename, argv[OUTPUT_CLARG_POS]);
      outfile_flag = 1;
    }    
 
#ifdef TRACE
  printf("Threshold: %4.2f\n",threshold);
#endif

  /* Read input points */
  input_points = (point_pt) mymalloc (MAX_NUMBER_OF_INPUT_POINTS *
				      sizeof (point_t));

  number_of_input_points = read_input_file (infilename, input_points);
  
#ifdef TRACE
  printf("Number of input points: %d\n",number_of_input_points);
  for (i = 0; i<number_of_input_points; i++) {
    printf ("%5d:  ", input_points[i].type);
    for (j=0;j<=Z;j++) {
      printf("%6.3f ",input_points[i].pos[j]);
    }
    printf("\n");
  }
#endif

  /* Find clustered points */
  cluster_points = (point_pt) mymalloc (MAX_NUMBER_OF_CLUSTER_POINTS * 
					sizeof (point_t));
  for (i=0;i<MAX_NUMBER_OF_CLUSTER_POINTS;i++) {
    cluster_points[i].contents = NULL;
    cluster_points[i].contents_size = 0;
  }

  number_of_cluster_points = 
    complete_link_clustering (input_points,
			      number_of_input_points,
			      cluster_points,
			      threshold);
#ifdef TRACE
  printf("Number of cluster points: %d\n",number_of_cluster_points);
  for (i = 0; i<number_of_cluster_points; i++) {
    printf ("%5d:  ", cluster_points[i].type);
    for (j=0;j<=Z;j++) {
      printf("%6.3f ",cluster_points[i].pos[j]);
    }
    if (cluster_points[i].contents_size != 0)
      printf("|%s| %d\n",cluster_points[i].contents,
	     cluster_points[i].contents_size);
  }

#endif

  if (outfile_flag == 1) {
    fp_out = fopen (outfilename, "w");
    if (fp_out == NULL ) 
      {
	sprintf ( linebuffer, 
		  "unable to open file %s", 
		  outfilename );
	err_panic ( "output_cluster_points", 
		    linebuffer );
      }
  }
  else
    fp_out = stdout;
  
  output_cluster_points (fp_out, 
			 cluster_points, 
			 number_of_cluster_points,
			 threshold);

  return (0);

}


