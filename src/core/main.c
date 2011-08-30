//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <GL/glx.h>     // Header file fot the glx libraries.
#include <unistd.h>     // Header file for sleeping.
#include <math.h>       // Header file for sin/cos functions.
#include <stdio.h>      // Header file for printf debugging.
#include <stdarg.h>
#include <string.h>
#include "console.h"
#include "frametimer.h"
/* ascii code for the escape key */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 


/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)              // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);         // This Will Clear The Background Color To Black
  glClearDepth(1.0);                            // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                         // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);                      // Enables Depth Testing
  glShadeModel(GL_SMOOTH);                      // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                             // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);     // Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)                                // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);              // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
  gl_printk(COLOR_WRN, "Screen resized to: %dx%d", Width, Height);
}



static int console_enabled=1;
/* The main drawing function. */
//#ifdef UGL_DRAW_PROFILING 
//static float a,b,c,d,e;
//static char pstr[128];
//#define 



void ugl_update_scene()
{
  frametimer_update();
}

void DrawGLScene()
{
  
  ugl_update_scene();
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           // Clear The Screen And The Depth Buffer
  glLoadIdentity();                             // Reset The View
  glColor4f(1,1,1,1);
  float delta = frametimer_getdelta();
  if (console_enabled) {
    frametimer_process_fps(); 
    console_redraw(delta);
  }
  
  glTranslatef(0.0f,0.0f,-6.0f);
  glEnable2D();
  
  glBegin(GL_LINES);                                                // Drawing Using Triangles
                glVertex2d( 0, 10);                          // Top
		glVertex2d( 1024, 10);                          // Top
  glEnd();
  glDisable2D();
   
  //Draw the console if enabled
  
  // since this is double buffered, swap the buffers to display what just got drawn.
  glutSwapBuffers();
  
  
}




/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
    /* avoid thrashing this procedure */
    usleep(100);

    /* If escape is pressed, kill everything. */
    switch (key)
    {
	case ESCAPE:
        /* shut down our window */
	glutDestroyWindow(window); 

        /* exit the program...normal termination. */
        exit(0);                 
        break;
	//Bring on the console
	case '~':
	console_enabled=!console_enabled;
	break;
    }
    
}



int main(int argc, char **argv) 
{ 
  ugl_profiler_test();
  gl_printk(COLOR_INF,"Necromant's uGL engine.");
  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or 
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */  
  glutInit(&argc, argv);
  gl_printk(COLOR_INF,"Glut initialised & ready");
  /* Select type of Display mode:   
     Double buffer 
     RGBA color
     Alpha components supported 
     Depth buffer */  
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
  gl_printk(COLOR_INF,"Display mode set up");
  /* get a 640 x 480 window */
  int w = 640;
  int h = 480;
  glutInitWindowSize(w, h);  
  gl_printk(COLOR_INF,"Window set to %dx%d", w,h);
  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);  

  /* Open a window */  
  window = glutCreateWindow("Necromant's uGL: Invyl");  

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);  

  /* Go fullscreen.  This is as soon as possible. */
  glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(w, h);
  
  console_init(13,"-adobe-helvetica-medium-r-normal--12-*-*-*-p-*-iso8859-1");
  //console_redraw();
  /* Start Event Processing Engine */  
  gl_printk(COLOR_OK,"core: Starting control thread");
  frametimer_init();
  glutMainLoop();  

  return 1;
}
