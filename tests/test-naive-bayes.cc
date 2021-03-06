
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <giomm/init.h>
#include "language.hh"
#include "naive-bayes.hh"

using std::cout;
using std::endl;
using Glib::ustring;
using wordtip::Classifier;
using wordtip::Language;
using wordtip::NaiveBayes;

void
sample_train(Classifier& cl)
{
    cl.train("the quick brown fox jumps over the lazy dog", "good");
    cl.train("the birds are singing and the sun is bright", "good");
    cl.train("quick movement is vital in the struggle for survival", "good");
    cl.train("make quick money selling online viagra in casino", "bad");
    cl.train("buy cactus medications and reach the clouds", "bad");
    cl.train("Stroustrup began work on C with Classes in 1979. The idea of "
            "creating a new language originated from Stroustrup's experience "
            "in programming for his Ph.D. thesis. Stroustrup found that "
            "Simula had features that were very helpful for large software "
            "development, but the language was too slow for practical use, "
            "while BCPL was fast but too low-level to be suitable for "
            "large software development.", "evil");
}

void
test_document_prob()
{
    NaiveBayes cl(Language::create("en"));
    sample_train(cl);
    
    ustring text("quick birds");
    ustring cat_good("good");

    cout << cl.get_document_prob(text, cat_good) << endl;
}

void
test_prob()
{
    NaiveBayes cl(Language::create("en"));
    sample_train(cl);

    ustring text("quick birds");
    ustring cat_good("good");
    ustring cat_bad("bad");

    double pr_good = cl.get_prob(text, cat_good);
    double pr_bad = cl.get_prob(text, cat_bad);

    cout << pr_good << endl;
    cout << pr_bad << endl;
}

void
test_classify()
{
    NaiveBayes cl(Language::create("en"));
    sample_train(cl);

    cout << cl.classify("quick birds", "unknown") << endl;
    cout << cl.classify("quick money", "unknown") << endl;
    cout << cl.classify("some other programming language", "unknown") << endl;
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int, char**)
{
    Gio::init();
    test_suite* test = BOOST_TEST_SUITE("naive Bayes tests");

    test->add(BOOST_TEST_CASE(&test_document_prob));
    test->add(BOOST_TEST_CASE(&test_prob));
    test->add(BOOST_TEST_CASE(&test_classify));

    return test;
}

