
AM_CXXFLAGS = -Wall -Wextra \
              -Wctor-dtor-privacy -Woverloaded-virtual -Wchar-subscripts \
              -Wpointer-arith -Wcast-align -Wsign-compare

bin_PROGRAMS = wordtip

wordtip_SOURCES = \
	feature-ex.cc \
	main.cc

global_defines = \
	-DPREFIX=\""$(prefix)"\" \
	-DSYSCONFDIR=\""$(sysconfdir)"\" \
	-DLIBDIR=\""$(libdir)"\" \
	-DDATADIR=\""$(datadir)"\" \
	-DWORDTIP_PKGDATADIR=\""$(pkgdatadir)"\" \
	-DDBUS_API_SUBJECT_TO_CHANGE

AM_CPPFLAGS = -I$(top_builddir) -I$(top_srcdir) $(global_defines) \
               ${WORDTIP_CFLAGS} \
              -DWORDTIP_LOCALEDIR=\"${WORDTIP_LOCALEDIR}\"

wordtip_LDADD = ${WORDTIP_LIBS}
