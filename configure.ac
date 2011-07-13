AC_PREREQ([2.60])
AC_INIT([ugl], [0.1], [necromant@necromant.ath.cx])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([config.h])
AC_C_INLINE

# Checks for programs.
AC_PROG_CC
AM_PROG_CC_C_O

AC_MSG_NOTICE([Made in USSR in the year 2061])
sleep 2

PKG_CHECK_MODULES([DEPS], [libconfig >= 1.4.6 xmu >= 1.1.0 gl >= 7.10.0 glu >= 7.10.0])


AC_SUBST([GLUT_LFLAGS], [-lglut])

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libconfig.h fcntl.h stdlib.h string.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT16_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero memset strdup strerror])
AC_CONFIG_FILES([Makefile src/Makefile src/core/Makefile])

AC_OUTPUT

