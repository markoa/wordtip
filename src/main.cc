
#include "feature-ex.hh"
#include <iostream>
#include <vector>
#include <boost/function.hpp>
#include <glibmm/convert.h>

int
main(int /*argc*/, char** /*argv*/)
{
    std::vector<Glib::ustring> results;
    wordtip::split_simple("хеј man!\n have a cigar();", results);
    std::vector<Glib::ustring>::iterator it(results.begin());
    std::vector<Glib::ustring>::iterator end(results.end());
    try {
        for ( ; it != end; ++it)
            std::cout << it->raw() << std::endl;
    } catch (const Glib::ConvertError& ex) {
        std::cerr << ex.what() << std::endl;
    }

    return 0;
}
