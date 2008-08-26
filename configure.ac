### Copyright (C) 2008 Marko Anastasov

AC_INIT([wordtip], [0.1])
AC_PREREQ(2.59)
AC_CANONICAL_TARGET
AM_MAINTAINER_MODE
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADER([config.h])
ACLOCAL="$ACLOCAL $ACLOCAL_FLAGS"

AM_INIT_AUTOMAKE([1.9 gnu no-define dist-bzip2])

MAJOR_VERSION=0
MINOR_VERSION=1
MICRO_VERSION=0

WORDTIP_VERSION="$MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION"
AC_SUBST(WORDTIP_VERSION)

AC_ISC_POSIX
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

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
# Unit test option
# *************************************
AC_ARG_ENABLE(autotests,
              AC_HELP_STRING([--enable-autotests=yes|no],
                             [enable automated tests (default is no)]),
              ENABLE_AUTOTESTS=$enableval,
              ENABLE_AUTOTESTS=auto)
if test x$ENABLE_AUTOTESTS = xauto ; then
    if test x$NEMIVER_DEVEL = xon ; then
        ENABLE_AUTOTESTS=yes
    else
        ENABLE_AUTOTESTS=no
    fi
fi

AM_CONDITIONAL(AUTOTESTS, test x$ENABLE_AUTOTESTS = xyes)

# *************************************
# Library checks
# *************************************
AC_CHECK_HEADERS([boost/variant.hpp],
                 [],
                 [AC_MSG_ERROR([Please install boost development headers])])

PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4 >= 2.16])
AC_SUBST([GLIBMM_CFLAGS])
AC_SUBST([GLIBMM_LIBS])

PKG_CHECK_MODULES([DBUS], [dbus-glib-1 >= 0.50])
AC_SUBST([DBUS_CFLAGS])
AC_SUBST([DBUS_LIBS])

if test x$ENABLE_AUTOTESTS = xyes ; then
    AX_BOOST_BASE([1.33.1])
    AX_BOOST_UNIT_TEST_FRAMEWORK

    unit_framework_lib_candidates="/usr/lib/libboost_unit_test_framework-st.a /usr/lib/libboost_unit_test_framework.a"
    for i in $unit_framework_lib_candidates ; do
        if test -f $i ; then
            BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB=$i
            break
        fi
    done
    AC_SUBST(BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB)
fi

# *************************************
# LIBS and CFLAGS definitions
# *************************************

WORDTIP_LIBS="$GTHREAD_LIBS $GLIBMM_LIBS $DBUS_LIBS"
WORDTIP_CFLAGS="$GTHREAD_CFLAGS $GLIBMM_CFLAGS $DBUS_CFLAGS"

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
    tests/Makefile
])

AC_OUTPUT()

cat <<EOT

=================================================================
                      wordtip: $MAJOR_VERSION.$MINOR_VERSION.$MICRO_VERSION
=================================================================
        Here is the configuration of the package:

    Prefix                          : ${prefix}
    Source code location            : ${srcdir}
    C Compiler                      : ${CC}
    C++ Compiler                    : ${CXX}

    CFLAGS                          : ${CFLAGS}
    CXXFLAGS                        : ${CXXFLAGS}
    WORDTIP_LIBS                    : ${WORDTIP_LIBS}
    WORDTIP_CFLAGS                  : ${WORDTIP_CFLAGS}

 OPTIONAL FEATURES:
    Enable autotests                : ${ENABLE_AUTOTESTS}
    Maintainer mode                 : ${USER_MAINTAINER_MODE}
EOT
