#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "defs.h"
#include "types.h"
#include "basics.h"

void output_cluster_points ( FILE      *out,
			     point_pt  points,
			     int       number_of_points,
			     double    threshold)
{
  int       i, j;

  fprintf(out, "# Number of cluster points: %d\n",number_of_points);
  fprintf(out, "# Cluster Threshold: %5.2f\n", threshold);
  fprintf(out, "#Density: X      Y      Z     -- Cluster Contents\n");
  for (i = 0; i<number_of_points; i++) {
    fprintf (out, "%-4d %5d  ", i, points[i].type);
    for (j=0;j<=Z;j++) {
      fprintf(out, "%8.3f ",points[i].pos[j]);
    }
    fprintf(out, " -- %s\n",points[i].contents);
  }

}
