
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "classifier.hh"

using std::cout;
using std::endl;
using Glib::ustring;
using wordtip::Classifier;

void
test_feature_count()
{
    Classifier cl(&wordtip::split_simple);
    cl.train("yesterday i was going to make a tea", "good");
    cl.train("and then a bird came yesterday too and sang of my favourite songs", "good");
    cl.train("bla bla whatever dude, one of those days like yesterday", "bad");

    float val;
    val = cl.get_feature_count("yesterday", "good");
    BOOST_CHECK_EQUAL(val, 2);
    val = cl.get_feature_count("yesterday", "bad");
    BOOST_CHECK_EQUAL(val, 1);
}

void
sample_train_good_bad(Classifier& cl)
{
    cl.train("the quick brown fox jumps over the lazy dog", "good");
    cl.train("the birds are singing and the sun is bright", "good");
    cl.train("quick movement is vital in the struggle for survival", "good");
    cl.train("make quick money selling online viagra in casino", "bad");
    cl.train("buy cactus medications and reach the clouds", "bad");
}

void
test_cond_prob()
{
    Classifier cl(&wordtip::split_simple);
    sample_train_good_bad(cl);

    ustring word("quick");
    ustring cat("good");
    float prob = cl.get_cond_prob(word, cat);
    BOOST_CHECK_EQUAL(prob, static_cast<float>(2./3));
    cout << "Pr(" << word << " | " << cat << ") = " << prob << endl;
}

void
test_weighted_prob()
{
    Classifier cl(&wordtip::split_simple);
    sample_train_good_bad(cl);

    wordtip::prob_func_t pf = &Classifier::get_cond_prob;
    float money_good_pr = cl.get_weighted_prob("money", "good", pf);
    BOOST_CHECK_EQUAL(money_good_pr, 0.25);

    // same data one more time
    sample_train_good_bad(cl);

    money_good_pr = cl.get_weighted_prob("money", "good", pf);
    BOOST_CHECK(money_good_pr - 0.16 > 0.0001);
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int, char**)
{
  test_suite* test = BOOST_TEST_SUITE("classifier tests");

  test->add(BOOST_TEST_CASE(&test_feature_count));
  test->add(BOOST_TEST_CASE(&test_cond_prob));
  test->add(BOOST_TEST_CASE(&test_weighted_prob));

  return test;
}
