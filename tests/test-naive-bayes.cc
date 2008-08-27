
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "naive-bayes.hh"

using std::cout;
using std::endl;
using Glib::ustring;
using wordtip::Classifier;
using wordtip::NaiveBayes;

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
test_document_prob()
{
    NaiveBayes cl(&wordtip::split_simple);
    sample_train_good_bad(cl);
    
    ustring text("quick birds");
    ustring cat_good("good");

    cout << cl.get_document_prob(text, cat_good) << endl;
}

void
test_prob()
{
    NaiveBayes cl(&wordtip::split_simple);
    sample_train_good_bad(cl);

    ustring text("quick birds");
    ustring cat_good("good");
    ustring cat_bad("bad");

    float pr_good = cl.get_prob(text, cat_good);
    float pr_bad = cl.get_prob(text, cat_bad);

    cout << pr_good << endl;
    cout << pr_bad << endl;
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int, char**)
{
  test_suite* test = BOOST_TEST_SUITE("naive Bayes tests");

  test->add(BOOST_TEST_CASE(&test_document_prob));
  test->add(BOOST_TEST_CASE(&test_prob));

  return test;
}

