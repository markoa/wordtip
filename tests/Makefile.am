if AUTOTESTS
# 'make check' automatically runs programs listed in the TESTS variable
#
TESTS=\
	run-test-split-simple

else

TESTS=

endif

noinst_PROGRAMS=$(TESTS)

run_test_split_simple_SOURCES=test-split-simple.cc
run_test_split_simple_LDADD=@WORDTIP_LIBS@ \
			    $(top_builddir)/src/libwordtip.a \
			    @BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB@

INCLUDES=-I$(top_srcdir)/src @WORDTIP_CFLAGS@ -DBOOST_TEST_DYN_LINK
