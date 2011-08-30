#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <GL/glx.h>     // Header file fot the glx libraries.
#include <unistd.h>     // Header file for sleeping.
#include <math.h>       // Header file for sin/cos functions.
#include <stdio.h>      // Header file for printf debugging.
#include <stdarg.h>
#include <time.h>
#include "console.h"
#include "common.h"
#include "frametimer.h"
#include "profile.h"

struct ugl_profile_t* ugl_profile_create(int count, char* tag)
{
  struct ugl_profile_t* prof = (struct ugl_profile_t*) malloc(2*sizeof(int)+sizeof(char*)(count+1)*sizeof(struct timeval));
  prof->pos=0;
  prof->tag=tag;
  prof->count=count;
  gettimeofday(&prof->start, NULL);
  return prof;
}

__inline ugl_profile_mark(struct ugl_profile_t* prof)
{
  gettimeofday(&prof->data[prof->pos++], NULL);
}

void ugl_profile_print(struct ugl_profile_t* prof)
{
  printf("UGL PROFILER REPORT\n");
  printf("---\n");
  int i;
  struct timeval prev = prof->start;
  float delta, abs;
  for (i=0; i < prof->count; i++ )
  {
    delta = (float)(prof->data[i].tv_sec-prev.tv_sec) + 0.000001*((float)(prof->data[i].tv_usec-prev.tv_usec));
    abs = (float)(prof->data[i].tv_sec-prof->start.tv_sec) + 0.000001*((float)(prof->data[i].tv_usec-prof->start.tv_usec));
    prev = prof->data[i];
    printf("[%.6f] %.6f\n",abs,delta);
  }
}

void ugl_profiler_test()
{
  struct ugl_profile_t* p = ugl_profile_create(10);
  ugl_profile_mark(p);
  sleep(1);
  ugl_profile_mark(p);
  ugl_profile_mark(p);
  ugl_profile_mark(p);
  sleep(5);
  ugl_profile_mark(p);
  ugl_profile_mark(p);
  ugl_profile_print(p);
  exit(0);
  
  
}