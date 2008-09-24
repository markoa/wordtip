
#ifndef WORDTIP_LANGUAGE_HH
#define WORDTIP_LANGUAGE_HH

#include <tr1/memory>
#include <vector>
#include <boost/noncopyable.hpp>
#include <glibmm/ustring.h>

namespace wordtip {

    class Stemmer;

    class Language : private boost::noncopyable
    {
    public:
        static std::tr1::shared_ptr<Language> create(const Glib::ustring& code);

        bool is_stop_word(const Glib::ustring& word);

        Glib::ustring stem_word(const Glib::ustring& word);

    protected:
        explicit Language(const Glib::ustring& lang_code);

        std::vector<Glib::ustring> stop_words_;
        std::tr1::shared_ptr<Stemmer> stemmer_;
    };

} // namespace wordtip

#endif // WORDTIP_LANGUAGE_HH
