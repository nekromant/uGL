#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <GL/glx.h>     // Header file fot the glx libraries.
#include <unistd.h>     // Header file for sleeping.
#include <math.h>       // Header file for sin/cos functions.
#include <stdio.h>      // Header file for printf debugging.
#include <stdarg.h>
#include <time.h>


#include "frametimer.h"
#include <string.h>
#include <stdarg.h>

struct clog_instance
{
	int count; 
	int pos;
	struct char **text;
};


// initializes the instance
struct clog_instance *clog_init(int count)
{
	struct clog_instance *inst = malloc(sizeof(clog_instance));
	if (!clog_instance)
	{
		return 0;
	}
	inst->count = count;
	ins->pos = 0;
	inst->text = calloc(count, sizeof(char*));
	if (!inst->text)
		goto alloc_fail;
	return inst;
alloc_fail:
	free(clog_instance);
	return 0;
}
	
static inline void pos_increment(clog_instance* inst)
{
	inst->pos++;
	if (inst->count==inst->pos)
		inst->pos=0;
}

void clog_push(clog_instance* inst, char* format, ...)
{
	va_list ap;
        va_start(ap, format);	
	if (NULL != inst->text[pos])
		free(inst->text[pos]);
	int ret = vasprintf(&inst->text[pos], format, ap);
	va_end(ap);
	if (ret == -1)
	{
		fprintf(stderr, "internal logging library error\n");
		exit(0xdead);
	}
	pos_increment(inst);
}


void clog_destroy(clog_instance* inst)
{
	int i;
	for (i=0; i< inst->count; i++)
	{
		if (inst->text[i])
			free(inst->text[i]);
	}
	free(inst->text);
	free(inst);
}


void clog_dump(clog_instance* inst)
{
	int i=inst->pos;
	printf("Dumping logger circular buffer\n");
	while (i != (inst->pos - 1))
	{
		printf(inst->text[i]);
		printf("\n");
		pos_increment(inst);
	}
	printf("----done----\n");
}


char* clog_read(clog_instance* inst, int pos)
{
	int rpos;
	if (pos >= inst->count)
	{
		return 0;
	}
	rpos = abs(inst->pos + pos) % inst->count;
	return inst->text[rpos];
	
}

