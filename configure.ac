### Copyright (C) 2008 Marko Anastasov

AC_INIT([wordtip], [0.1])
AC_PREREQ(2.59)

AC_CONFIG_SRCDIR([src/main.cc])

AC_CONFIG_HEADER([config.h])

AM_INIT_AUTOMAKE([1.9 gnu no-define dist-bzip2])

ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AC_ISC_POSIX
AC_PROG_CXX
AC_PROG_CC

# *************************************
# Compiler and platform check
# *************************************

if test "${GXX}" != "yes" ; then
   AC_MSG_ERROR([wordtip needs g++ to be compiled])
fi

AC_MSG_CHECKING([for a supported version of g++])

gxx_version=`${CXX} --version | head -n 1`

case "${gxx_version}" in
     *4.*)
	AC_MSG_RESULT([ok (${gxx_version})])
	;;
     *)
        AC_MSG_RESULT([no (${gxx_version})])
	AC_MSG_ERROR([wordtip requires g++ version 4.*])
	;;
esac

AC_CANONICAL_HOST

# ****************************************************************************
# C structs, typedefs, functions, headers and compiler characteristics checks
# ****************************************************************************
# (running autoscan can help to check if everything's
# here; in that case, an empty autoscan*.log should be produced).
AC_HEADER_DIRENT
AC_HEADER_STDBOOL
AC_CHECK_HEADERS([fcntl.h libintl.h sys/statvfs.h unistd.h])
AC_C_CONST
AC_C_INLINE
AC_CHECK_MEMBERS([struct stat.st_blksize])
AC_STRUCT_TM
AC_CHECK_FUNCS([mkdir])
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_STAT
AC_FUNC_STRFTIME

AC_LANG_CPLUSPLUS

# *************************************
# Library checks
# *************************************
AC_CHECK_HEADERS([boost/variant.hpp],
                 [],
                 [AC_MSG_ERROR([Please install boost development headers])])

PKG_CHECK_MODULES([DBUS], [dbus-glib-1 >= 0.50])
AC_SUBST([DBUS_CFLAGS])
AC_SUBST([DBUS_LIBS])

# *************************************
# LIBS and CFLAGS definitions
# *************************************

WORDTIP_LIBS="$GTHREAD_LIBS $DBUS_LIBS"
WORDTIP_CFLAGS="$GTHREAD_CFLAGS$DBUS_CFLAGS"

AC_SUBST(WORDTIP_LIBS)
AC_SUBST(WORDTIP_CFLAGS)

# *************************************
# Prepare for make
# *************************************

# Allow 'make install'.
AC_PROG_INSTALL

# Generate the files:
AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT

AC_MSG_NOTICE([Configuration complete. Type 'make' to build wordtip.])
