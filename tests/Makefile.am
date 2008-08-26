if AUTOTESTS
# 'make check' automatically runs programs listed in the TESTS variable
#
TESTS= \
	run-test-classifier \
	run-test-split-simple

else

TESTS=

endif

noinst_PROGRAMS=$(TESTS)

common_ld=@WORDTIP_LIBS@ \
	  $(top_builddir)/src/libwordtip.a \
	  @BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB@


run_test_classifier_SOURCES=test-classifier.cc
run_test_classifier_LDADD=${common_ld}

run_test_split_simple_SOURCES=test-split-simple.cc
run_test_split_simple_LDADD=${common_ld}

INCLUDES=-I$(top_srcdir)/src @WORDTIP_CFLAGS@ -DBOOST_TEST_DYN_LINK
