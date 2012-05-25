#ifndef __PROFILE_H
#define __PROFILE_H

struct ugl_profiler_stamp_t 
{
  struct timeval stamp;
  char* tag;
};

struct ugl_profiler_header_t
{
  struct timeval start;
  int pos;
  int count;
  char* tag;
};

struct ugl_profiler_t
{
  struct ugl_profiler_header_t h;
  //struct timeval data[];
  struct ugl_profiler_stamp_t data[];
};

/** 
 * Creates a profiler instance, if the profiling is enabled. Otherwise
 * produces no code.
 * @param maximum number of marks in profiling run
 * @param tag A char* tag for the instance
 *
 * @return a profiler instance for subsequent calls
 */

struct ugl_profiler_t* ugl_profiler_create(int count, char* tag);
/** 
 * Adds a mark to current profiler instance
 *
 * @param prof Profiler instance
 * @param label Custom label for this very place
 *
 */
__inline void ugl_profiler_mark(struct ugl_profiler_t* prof, char* label)
{
	gettimeofday(&prof->data[prof->h.pos].stamp, NULL);
	prof->data[prof->h.pos++].tag=label;
}

/** 
 * Resets the profiler instance
 *
 * @param prof the profiler instance
 */
void ugl_profiler_reset(struct ugl_profiler_t* prof);

/** 
 * Dumps collected info from profiler instance to stdout
 *
 * @param prof Profiler instance
 */
void ugl_profiler_print(struct ugl_profiler_t* prof);

#endif

