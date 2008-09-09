
if AUTOTESTS
# 'make check' automatically runs programs listed in the TESTS variable
#
TESTS= \
	run-test-classifier \
	run-test-naive-bayes \
	run-test-split-simple \
	run-test-stemmer

else

TESTS=

endif

noinst_PROGRAMS=$(TESTS)

common_ld=@WORDTIP_LIBS@ \
	  $(top_builddir)/src/libwordtip.a \
	  @BOOST_UNIT_TEST_FRAMEWORK_STATIC_LIB@

run_test_classifier_SOURCES=test-classifier.cc
run_test_classifier_LDADD=${common_ld}

run_test_naive_bayes_SOURCES=test-naive-bayes.cc
run_test_naive_bayes_LDADD=${common_ld}

run_test_split_simple_SOURCES=test-split-simple.cc
run_test_split_simple_LDADD=${common_ld}

run_test_stemmer_SOURCES=test-stemmer.cc
run_test_stemmer_LDADD=${common_ld} \
		       $(top_builddir)/src/libstemmer/libstemmer-private.la 

INCLUDES=-I$(top_srcdir)/src @WORDTIP_CFLAGS@ -DBOOST_TEST_DYN_LINK
