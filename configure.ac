#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Z80 Macro Assembler], [1.9], [wijnen@debian.org], [z80asm], [http://www.nongnu.org/z80asm])
AM_INIT_AUTOMAKE([gnu dist-bzip2])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([include/config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_RANLIB

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h stdlib.h string.h strings.h unistd.h wchar.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Replacement for missing getopt function
AC_CONFIG_LIBOBJ_DIR([compat])

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([atexit memset strchr strerror getopt getopt_long])

AC_CONFIG_FILES([Makefile
                 examples/Makefile
                 compat/Makefile
                 src/Makefile
                 data/Makefile
		 doc/Makefile
		 doc/man/Makefile
                 tests/Makefile])
AC_OUTPUT
