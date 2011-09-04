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

struct ugl_profiler_t* ugl_profiler_create(int count, char* tag);
__inline ugl_profiler_mark(struct ugl_profiler_t* prof, char* label);
void ugl_profiler_reset(struct ugl_profiler_t* prof);
void ugl_profiler_print(struct ugl_profiler_t* prof);