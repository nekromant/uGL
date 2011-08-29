#ifndef FRAMETIMER_H
#define FRAMETIMER_H

__inline float frametimer_getfps();
__inline float frametimer_getdelta();
void frametimer_init();
void frametimer_update();
__inline void frametimer_process_fps();

float frametimer_since(float offset);



#endif
