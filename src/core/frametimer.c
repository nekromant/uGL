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


//Dumb time for frames. Single instance for the whole app

static struct timespec start_time;
static struct timespec delta;
static unsigned long delta_nsec;

__inline void frame_start()
{
  clock_gettime(CLOCK_MONOTONIC, &start_time);  
}

__inline void frame_end()
{
  struct timespec end;
  clock_gettime(CLOCK_MONOTONIC, &end);  
  delta.tv_sec = start_time.tv_sec-end.tv_sec;
  delta.tv_nsec = delta.tv_sec*1000000000L + start_time.tv_nsec-end.tv_nsec;
  delta_nsec = delta.tv_sec*1000000000L;
}

__inline struct timespec* frame_delta()
{
  return &delta;
}

__inline unsigned long frame_delta_ticks()
{
  return delta_nsec;
}