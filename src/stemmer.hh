
#include <glibmm/ustring.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "./libstemmer/include/libstemmer.h"

namespace wordtip {

    class Stemmer : private boost::noncopyable
    {
    public:
        static boost::shared_ptr<Stemmer> create(const Glib::ustring& lang_code);

        virtual ~Stemmer();

        virtual Glib::ustring stem_word(const Glib::ustring& word);

    protected:
        explicit Stemmer(const Glib::ustring& lang_code);

        sb_stemmer* stemmer_;
    };

} // namespace wordtip
