
AM_CXXFLAGS = -Wall -Wextra \
              -Wctor-dtor-privacy -Woverloaded-virtual -Wchar-subscripts \
              -Wpointer-arith -Wcast-align -Wsign-compare

bin_PROGRAMS = wordtip

core_sources = feature-ex.cc

wordtip_SOURCES = \
	${core_sources} \
	main.cc

noinst_LIBRARIES = libwordtip.a
libwordtip_a_SOURCES = ${core_sources}

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
