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
void console_redraw(float del);
#define COLOR_INF 200,200,200
#define COLOR_WRN 210,210,100
#define COLOR_OK 10,200,10
#define COLOR_LN 50,50,50

#endif