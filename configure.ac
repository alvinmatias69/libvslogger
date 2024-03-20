#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libvsLogger], [1.0.0], [vslogger@matiasalvin.dev])
AM_INIT_AUTOMAKE
LT_PREREQ([2.4.6])
LT_INIT([dlopen])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for header files.
AC_CHECK_HEADERS([stdbool.h stdio.h stdarg.h stdlib.h string.h time.h ltdl.h])

# Checks for library functions.
AC_SEARCH_LIBS([lt_dlopen], [ltdl])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 libvslogger/Makefile])
AC_OUTPUT
