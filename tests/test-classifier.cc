
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "classifier.hh"

using std::cout;
using std::endl;
using Glib::ustring;

void
test_feature_count()
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

void
test_cond_prob()
{
    wordtip::Classifier cl(&wordtip::split_simple);
    cl.train("the quick brown fox jumps over the lazy dog", "good");
    cl.train("the birds are singing and the sun is bright", "good");
    cl.train("quick movement is vital in the struggle for survival", "good");
    cl.train("make a quick buck selling online viagra in casino", "bad");
    cl.train("buy cactus medications and reach the clouds", "bad");

    ustring word("quick");
    ustring cat("good");
    float prob = cl.get_cond_prob(word, cat);
    BOOST_CHECK_EQUAL(prob, static_cast<float>(2./3));
    cout << "Pr(" << word << " | " << cat << ") = " << prob << endl;
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int, char**)
{
  test_suite* test = BOOST_TEST_SUITE("classifier tests");

  test->add(BOOST_TEST_CASE(&test_feature_count));
  test->add(BOOST_TEST_CASE(&test_cond_prob));

  return test;
}
