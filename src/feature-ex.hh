
#ifndef WORDTIP_FEATURES_HH
#define WORDTIP_FEATURES_HH

#include <boost/function.hpp>
#include <glibmm/ustring.h>
#include <vector>

namespace wordtip {

    typedef boost::function<void (const Glib::ustring& txt,
            std::vector<Glib::ustring>& results)> get_features_func_t;

    void split_simple(const Glib::ustring& txt,
                      std::vector<Glib::ustring>& words);

} // namespace wordtip

#endif // WORDTIP_FEATURES_HH
