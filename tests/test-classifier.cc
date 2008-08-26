
#include <boost/test/unit_test.hpp>
#include "classifier.hh"

void
test_construct()
{
    wordtip::Classifier cl(&wordtip::split_simple);
    cl.train("one day i was going to make a tea", "good");
    cl.train("and then a bird came and sang one of my favourite songs", "good");
    cl.train("bla bla whatever dude, one of those days", "bad");
    float val;
    val = cl.get_feature_count("one", "good");
    BOOST_CHECK_EQUAL(val, 2);
    val = cl.get_feature_count("one", "bad");
    BOOST_CHECK_EQUAL(val, 1);
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int,char**)
{
  test_suite* test = BOOST_TEST_SUITE("classifier");
  test->add(BOOST_TEST_CASE(&test_construct));
  return test;
}

