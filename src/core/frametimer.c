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

// static struct timespec start_time;
// static struct timespec delta;
// static unsigned long delta_nsec;

static float			time_counter, last_frame_time_counter, dt, prev_time, fps, elapsed;
static struct timeval		tv, tv0;
static int			frame, frames_per_fps;



void frametimer_init() {
 gettimeofday(&tv0, NULL);
 frame=1;
 frames_per_fps = 30; 
}

float frametimer_since(float offset)
{
  return elapsed-offset;
}

void frametimer_update() {
 last_frame_time_counter =time_counter;
 gettimeofday(&tv, NULL);
 time_counter = (float)(tv.tv_sec-tv0.tv_sec) + 0.000001*((float)(tv.tv_usec-tv0.tv_usec));
 elapsed+=dt;
 dt = time_counter - last_frame_time_counter; 
 //gl_printk(COLOR_INF,"delta: %.4f", dt);
}

__inline void frametimer_process_fps() {
 frame ++;
 if((frame % frames_per_fps) == 0) {
	//gl_printk(COLOR_INF, "upd: %.2f-%.2f, %.2f",time_counter,prev_time,fps);
	fps = ((float)(frames_per_fps)) / (time_counter-prev_time);
	prev_time = time_counter; 
    } 
}

	
__inline float frametimer_getfps()
{
  return fps;
}

__inline float frametimer_getdelta()
{
  //printf("%.2f\n",dt);
  return dt;
}

// __inline void frame_start()
// {
//   clock_gettime(CLOCK_MONOTONIC, &start_time);  
// }
// 
// __inline void frame_end()
// {
//   struct timespec end;
//   clock_gettime(CLOCK_MONOTONIC, &end);  
//   //delta.tv_sec = start_time.tv_sec-end.tv_sec;
//   //delta.tv_nsec = start_time.tv_nsec-end.tv_nsec;
//   delta_nsec = (start_time.tv_sec-end.tv_sec)*1000000000L + (start_time.tv_nsec-end.tv_nsec);
// }
// 
// __inline struct timespec* frame_delta()
// {
//   return &delta;
// }
// 
// __inline unsigned long frame_delta_ticks()
// {
//   return delta_nsec;
//}