
#include <iostream>
#include <boost/test/unit_test.hpp>
#include "stemmer.hh"

using std::cout;
using std::endl;
using wordtip::Stemmer;

void
test_stem_word()
{
    std::tr1::shared_ptr<Stemmer> stemmer = Stemmer::create("en");

    cout << stemmer->stem_word("beautiful") << endl;
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int,char**)
{
  test_suite* test = BOOST_TEST_SUITE("stem");
  test->add(BOOST_TEST_CASE(&test_stem_word));
  return test;
}
