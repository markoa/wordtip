
#include "noncopyable.hh"
#include "./libstemmer/include/libstemmer.h"
#include <tr1/memory>
#include <glibmm/ustring.h>

namespace wordtip {

    class Stemmer : NonCopyable
    {
    public:
        static std::tr1::shared_ptr<Stemmer> create(const Glib::ustring& lang_code);

        virtual ~Stemmer();

        virtual Glib::ustring stem_word(const Glib::ustring& word);

    protected:
        explicit Stemmer(const Glib::ustring& lang_code);

        sb_stemmer* stemmer_;
    };

} // namespace wordtip
