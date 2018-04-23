#ifndef _TYPES_H
#define _TYPES_H

#include "defs.h"

typedef struct {
  double pos[3];
  int    type;
  char   *contents;
  int    contents_size;
} point_t;

typedef point_t  *point_pt;

#endif
