bin_PROGRAMS = ugl
AM_CFLAGS = $(DEPS_FLAGS)
ugl_SOURCES = main.c \
	console.c console.h \
	common.c common.h \
	frametimer.c frametimer.h

ugl_CFLAGS = $(DEPS_CFLAGS) -g -Wall
ugl_LDADD = $(DEPS_LIBS) $(GLUT_LFLAGS)
