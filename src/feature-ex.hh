
#ifndef WORDTIP_FEATURES_HH
#define WORDTIP_FEATURES_HH

#include <boost/function.hpp>
#include <glibmm/ustring.h>
#include <vector>

namespace wordtip {

    typedef boost::function<void (Glib::ustring& txt,
            std::vector<Glib::ustring>& results) > get_words_f;

    void split_simple(const Glib::ustring& txt,
                      std::vector<Glib::ustring>& words);

} // namespace wordtip

#endif // WORDTIP_FEATURES_HH
