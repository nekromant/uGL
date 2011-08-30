struct ugl_profile_stamp_t 
{
  struct timeval stamp;
  char* tag;
};

struct ugl_profile_header_t
{
  struct timeval start;
  int pos;
  int count;
  char* tag;
};

struct ugl_profile_t
{
  struct ugl_profile_header_t h;
  //struct timeval data[];
  struct ugl_profile_stamp_t data[];
};

#ifdef UGL_PROFILE_ENABLED
#define 
#else
#endif