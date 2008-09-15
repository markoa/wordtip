
#include <iostream>
#include <boost/test/unit_test.hpp>
#include <giomm/init.h>
#include "language.hh"

using std::cout;
using std::endl;
using Glib::ustring;
using wordtip::Language;

void
test_all()
{
    boost::shared_ptr<Language> lang = Language::create("en");
    bool is_sw = lang->is_stop_word("have");
    ustring output = (is_sw) ? "true" : "false";
    cout << output << endl;
    cout << lang->stem_word("beautiful") << endl;
}

using namespace boost::unit_test;

test_suite*
init_unit_test_suite(int, char**)
{
    Gio::init();
    test_suite* test = BOOST_TEST_SUITE("Language sanity check");

    test->add(BOOST_TEST_CASE(&test_all));
    
    return test;
}
