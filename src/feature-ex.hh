
#ifndef WORDTIP_FEATURES_HH
#define WORDTIP_FEATURES_HH

#include <glibmm/ustring.h>
#include <vector>

namespace wordtip {

    void split_simple(const Glib::ustring& txt,
                      std::vector<Glib::ustring>& words);

} // namespace wordtip

#endif // WORDTIP_FEATURES_HH
