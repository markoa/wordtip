
#include <boost/test/unit_test.hpp>
#include "feature-ex.hh"

void
test_construct()
{
    std::vector<Glib::ustring> results;
    wordtip::split_simple("жзхеј man!\n have a... cigar();", results);
    BOOST_CHECK_EQUAL(results.size(), 3);

    Glib::ustring item;
    item = results[0];
    BOOST_CHECK_EQUAL(item.size(), 5);

    item = results[1];
    BOOST_CHECK_EQUAL(item.size(), 3);
    
    item = results[2];
    BOOST_CHECK_EQUAL(item.size(), 5);
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int,char**)
{
  test_suite* test = BOOST_TEST_SUITE("split-simple");
  test->add(BOOST_TEST_CASE(&test_construct));
  return test;
}
