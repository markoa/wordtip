
SUBDIRS = libstemmer

AM_CXXFLAGS = -Wall -Wextra \
              -Wctor-dtor-privacy -Woverloaded-virtual -Wchar-subscripts \
              -Wpointer-arith -Wcast-align -Wsign-compare

bin_PROGRAMS = wordtip

EXTRA_DIST = server-introspect.xml

core_sources = \
	       classifier.cc \
	       classifier.hh \
	       feature-ex.cc \
	       feature-ex.hh \
	       language.cc \
	       language.hh \
	       naive-bayes.cc \
	       naive-bayes.hh \
	       noncopyable.hh \
	       stemmer.cc \
	       stemmer.hh

wordtip_SOURCES = ${core_sources} \
		  main.cc \
		  server.cc \
		  server.hh \
		  server-glue.hh

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

wordtip_LDADD = ${WORDTIP_LIBS} \
		$(top_builddir)/src/libstemmer/libstemmer-private.la 

server-glue.hh:
	dbusxx-xml2cpp $(top_srcdir)/src/server-introspect.xml --adaptor=server-glue.hh

BUILT_SOURCES = server-glue.hh
CLEANFILES = $(BUILT_SOURCES)

dist-hook:
	cd $(distdir); rm -f $(BUILT_SOURCES)
