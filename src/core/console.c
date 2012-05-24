#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <GL/glx.h>     // Header file fot the glx libraries.
#include <unistd.h>     // Header file for sleeping.
#include <math.h>       // Header file for sin/cos functions.
#include <stdio.h>      // Header file for printf debugging.
#include <stdarg.h>
#include <time.h>

#define CONSOLE_LINES	8
#define CONSOLE_LMASK	0x7
#define LINE_LENGTH	1024
#include "console.h"
#include "frametimer.h"
#include <string.h>

static GLuint base;            	// base display list for the font set.
static char lines[CONSOLE_LINES][LINE_LENGTH]; 	//buffer Lines

typedef struct console_color_t console_color_t;
static console_color_t colors[CONSOLE_LINES]; 	//buffer Lines
static int line;
#define next_line(line) line=(line+1) &  CONSOLE_LMASK;


static GLuint base;            // base display list for the font set.
static GLfloat cnt1;           // 1st counter used to move text & for coloring.
static GLfloat cnt2;           // 2nd counter used to move text & for coloring.

GLvoid console_build_font(char* font) 
{
    Display *dpy;
    XFontStruct *fontInfo;  // storage for our font.

    base = glGenLists(96);                      // storage for 96 characters.
    
    // load the font.  what fonts any of you have is going
    // to be system dependent, but on my system they are
    // in /usr/X11R6/lib/X11/fonts/*, with fonts.alias and
    // fonts.dir explaining what fonts the .pcf.gz files
    // are.  in any case, one of these 2 fonts should be
    // on your system...or you won't see any text.
    
    // get the current display.  This opens a second
    // connection to the display in the DISPLAY environment
    // value, and will be around only long enough to load 
    // the font. 
    dpy = XOpenDisplay(NULL); // default to DISPLAY env.   

    //fontInfo = XLoadQueryFont(dpy, "-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1");
    fontInfo = XLoadQueryFont(dpy, font);
    if (fontInfo == NULL) {
	fontInfo = XLoadQueryFont(dpy, "fixed");
	if (fontInfo == NULL) {
	    printf("no X font available?\n");
	}
    }

    // after loading this font info, this would probably be the time
    // to rotate, scale, or otherwise twink your fonts.  

    // start at character 32 (space), get 96 characters (a few characters past z), and
    // store them starting at base.
    glXUseXFont(fontInfo->fid, 32, 96, base);

    // free that font's info now that we've got the 
    // display lists.
    XFreeFont(dpy, fontInfo);

    // close down the 2nd display connection.
    XCloseDisplay(dpy);
}

GLvoid console_unload_font(GLvoid)                         // delete the font.
{
    glDeleteLists(base, 96);                    // delete all 96 characters.
}


void gl_printk(GLbyte r, GLbyte g, GLbyte b, char* fmt, ...)
{
  va_list ap;
  va_start(ap,fmt);
  next_line(line);
  float since = frametimer_since(0.0);
  //FixMe: ugly
  char buffer[LINE_LENGTH];
  vsnprintf(buffer,LINE_LENGTH,fmt,ap);
  snprintf(&lines[line][0], LINE_LENGTH,"[ %.02f ] %s",since,buffer);
  printf(&lines[line][0]);
  printf("\n");
  colors[line].r=r;
  colors[line].g=g;
  colors[line].b=b;
  
  //line=(line+1) &  CONSOLE_LMASK;
  
  va_end(ap);
}

static int spacing=1;
void console_init(int _spacing, char* font)
{
  console_build_font(font);
  spacing=_spacing;
}

//     if (text == NULL) {                         // if there's no text, do nothing.
// 	return;
//     }
//     
//     glPushAttrib(GL_LIST_BIT);                  // alert that we're about to offset the display lists with glListBase
//     glListBase(base - 32);                      // sets the base character to 32.
// 
//     glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // draws the display list text.
//     glPopAttrib();  

//Update method
GLvoid glPrint(char *text)                      // custom gl print routine.
{
    if (text == NULL) {                         // if there's no text, do nothing.
	return;
    }
    
    glPushAttrib(GL_LIST_BIT);                  // alert that we're about to offset the display lists with glListBase
    glListBase(base - 32);                      // sets the base character to 32.

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // draws the display list text.
    glPopAttrib();                              // undoes the glPushAttrib(GL_LIST_BIT);
}


static float ppos=0;
static int console_enabled=1;

__inline void console_enable()
{
  console_enabled=1;
}

__inline void console_disable()
{
  console_enabled=0;
}

__inline void console_handle_key(char key)
{
  switch (key)
  {
	case '~':
	console_enabled=!console_enabled;
	break;
  }
}

__inline void console_redraw(float del)
{
  if (console_enabled)
  {
  frametimer_process_fps(); 
  int pos = glutGet(GLUT_WINDOW_HEIGHT);
  glEnable2D();
  int i=line;
  do{ 
  next_line(i);
  glColor3ub(colors[i].r,colors[i].g,colors[i].b);
  pos-=spacing;
  if (lines[i][0])
  {   
      glRasterPos2d(0,pos);
      glPushAttrib(GL_LIST_BIT);
      glListBase(base - 32); 
      glCallLists(strlen(lines[i]), GL_UNSIGNED_BYTE, lines[i]);
      glPopAttrib(); 
  }
  
  } while (i!=line);
  pos-=5;
  //FPS
  char fps[128];
  glColor3ub(COLOR_INF);
  //FPS Counter
  glPushAttrib(GL_LIST_BIT);
  glListBase(base - 32);
  
  sprintf(fps,"FPS: %.2f",frametimer_getfps());
  glRasterPos2d(glutGet(GLUT_WINDOW_WIDTH)-100,glutGet(GLUT_WINDOW_HEIGHT)-32);
  glCallLists(strlen(fps), GL_UNSIGNED_BYTE, fps);
  sprintf(fps,"Delta: %.2f",frametimer_getdelta());
  glRasterPos2d(glutGet(GLUT_WINDOW_WIDTH)-100,glutGet(GLUT_WINDOW_HEIGHT)-32*2);
  glCallLists(strlen(fps), GL_UNSIGNED_BYTE, fps);
  sprintf(fps,"Elapsed: %.2f",frametimer_since(0.0));
  glRasterPos2d(glutGet(GLUT_WINDOW_WIDTH)-100,glutGet(GLUT_WINDOW_HEIGHT)-32*3);
  glCallLists(strlen(fps), GL_UNSIGNED_BYTE, fps);
  
   
  //
  
  glPopAttrib(); 
      
  //Now draw a pretty animation
glBegin(GL_LINES); 
	      glColor3ub(COLOR_LN);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2-ppos, pos);                          
	      glColor3ub(255,255,255);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2-ppos-15, pos);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2-ppos-15, pos);                          
	      glColor3ub(COLOR_LN);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2-ppos-30, pos);                       
	      //
	      glColor3ub(COLOR_LN);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2+ppos, pos);                          
	      glColor3ub(255,255,255);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2+ppos+15, pos);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2+ppos+15, pos);                          
	      glColor3ub(COLOR_LN);
	      glVertex2d( glutGet(GLUT_WINDOW_WIDTH)/2+ppos+30, pos);                       
  glEnd();  
  glBegin(GL_LINES);      
                glVertex2d( 0, pos);                          
		glVertex2d( 1024, pos);                       
  glEnd();
  ppos+=del*250.0;
  if (ppos>=glutGet(GLUT_WINDOW_WIDTH)/2)
    ppos=-5.0;
  glDisable2D();
  }
}