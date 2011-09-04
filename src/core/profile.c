#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <GL/glx.h>     // Header file fot the glx libraries.
#include <unistd.h>     // Header file for sleeping.
#include <math.h>       // Header file for sin/cos functions.
#include <stdio.h>      // Header file for printf debugging.
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include "console.h"
#include "common.h"
#include "frametimer.h"
#include "profile.h"

struct ugl_profiler_t* ugl_profiler_create(int count, char* tag)
{
  struct ugl_profiler_t* prof = (struct ugl_profiler_t*) malloc(
    sizeof(struct ugl_profiler_header_t) + count*sizeof(struct ugl_profiler_stamp_t));
  prof->h.pos=0;
  prof->h.tag=tag;
  prof->h.count=count;
  gettimeofday(&prof->h.start, NULL);
  return prof;
}

__inline ugl_profiler_mark(struct ugl_profiler_t* prof, char* label)
{
  gettimeofday(&prof->data[prof->h.pos].stamp, NULL);
  prof->data[prof->h.pos++].tag=label;
}

void ugl_profiler_reset(struct ugl_profiler_t* prof)
{
  prof->h.pos=0;
}


void ugl_profiler_print(struct ugl_profiler_t* prof)
{
  printf("UGL PROFILER REPORT: %s\n", prof->h.tag);
  printf("---\n");
  int i;
  struct timeval prev = prof->h.start;
  float delta, abs;
  for (i=0; i < prof->h.count; i++ )
  {
    delta = (float)(prof->data[i].stamp.tv_sec-prev.tv_sec) + 0.000001*((float)(prof->data[i].stamp.tv_usec-prev.tv_usec));
    abs = (float)(prof->data[i].stamp.tv_sec-prof->h.start.tv_sec) + 0.000001*((float)(prof->data[i].stamp.tv_usec-prof->h.start.tv_usec));
    prev = prof->data[i].stamp;
    printf("[%.6f] %.6f (%s)\n",abs,delta,prof->data[i].tag);
  }
}

void ugl_profiler_test()
{
  struct ugl_profiler_t* p = ugl_profiler_create(10,"test profiling");
  ugl_profiler_mark(p,"uisn");
  sleep(1);
  ugl_profiler_mark(p,"uisn");
  sleep(2);
  ugl_profiler_mark(p,"uin");
  sleep(3);
  ugl_profiler_mark(p,"uins");
  ugl_profiler_mark(p,"uindfa");
  ugl_profiler_mark(p,"uin");
  ugl_profiler_mark(p,"uindfa");
  ugl_profiler_mark(p,"uin");
  ugl_profiler_mark(p,"uindfa");
  ugl_profiler_print(p);
  exit(0);
}