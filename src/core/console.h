#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <stdarg.h>
struct console_color_t
{
  GLbyte r;
  GLbyte g;
  GLbyte b;
} ;


void gl_printk(GLbyte r, GLbyte g, GLbyte b, char* fmt, ...);
#define COLOR_INF 200,200,200
#define COLOR_WRN 200,200,150

#endif