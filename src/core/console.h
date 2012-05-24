#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <stdarg.h>
struct console_color_t
{
  GLbyte r;
  GLbyte g;
  GLbyte b;
} ;

void console_init(int _spacing, char* font);
void gl_printk(GLbyte r, GLbyte g, GLbyte b, char* fmt, ...);
void console_redraw(float del);
__inline void console_enable();
__inline void console_disable();
__inline void console_handle_key(char key);


#define COLOR_INF 200,200,200
#define COLOR_WRN 210,210,100
#define COLOR_OK 10,200,10
#define COLOR_ERR 200,0,0
#define COLOR_LN 50,50,50

#endif