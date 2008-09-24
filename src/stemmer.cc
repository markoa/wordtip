
#include <glib.h>
#include "stemmer.hh"

namespace wordtip {

    using std::tr1::shared_ptr;
    using Glib::ustring;

    struct _Languages {
        const gchar* code;
        const gchar* name;
    };

    static struct _Languages all_langs[] = {
        { "da", "danish" },
        { "nl", "dutch" },
        { "en", "english" },
        { "fi", "finnish" },
        { "fr", "french" },
        { "de", "german" },
        { "hu", "hungarian" },
        { "it", "italian" },
        { "nb", "norwegian" },
        { "pt", "portuguese" },
        { "ru", "russian" },
        { "es", "spanish" },
        { "sv", "swedish" },
        { NULL, NULL },
    };

    static const gchar*
    get_name_for_code(const Glib::ustring& lang_code)
    {
        if (! lang_code.size()) return "english";

        for (int i = 0; all_langs[i].code; i++) {
            if (g_str_has_prefix (lang_code.c_str(), all_langs[i].code))
                return all_langs[i].name;
        }

        return "";
    }

    Stemmer::Stemmer(const Glib::ustring& lang_code)
        : stemmer_(0)
    {
        const gchar* language = get_name_for_code(lang_code);
        stemmer_ = sb_stemmer_new(language, NULL);

        if (! stemmer_)
            g_warning("eeek, no stemmer found for language %s", language);
    }

    Stemmer::~Stemmer()
    {
        sb_stemmer_delete(stemmer_);
    }

    shared_ptr<Stemmer>
    Stemmer::create(const Glib::ustring& lang_code)
    {
        return shared_ptr<Stemmer>(new Stemmer(lang_code));
    }

    ustring
    Stemmer::stem_word(const Glib::ustring& _word)
    {
        const gchar* stem_word;
        const gchar* word = _word.c_str();

        stem_word = (gchar*)
            sb_stemmer_stem(stemmer_, (guchar*)(word), _word.size());

        return Glib::ustring(stem_word);
    }

} // namespace wordtip
