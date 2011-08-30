struct ugl_profile_stamp_t 
{
  struct timeval stamp;
  char* tag;
};

struct ugl_profile_t
{
  struct timeval start;
  int pos;
  int count;
  char* tag
  struct timeval data[];
};

#ifdef UGL_PROFILE_ENABLED
#define 
#else
#endif