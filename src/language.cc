
#include <string>
#include <glibmm/fileutils.h>
#include <giomm.h>
#include "language.hh"
#include "stemmer.hh"

namespace wordtip {

    using std::tr1::shared_ptr;
    using Glib::ustring;

    Language::Language(const ustring& lang_code)
    {
        ustring swfile = "stop-words-" + lang_code + ".txt";
        ustring path = WORDTIP_PKGDATADIR G_DIR_SEPARATOR_S;
        path = path.append(swfile);

        if (! Glib::file_test(path, Glib::FILE_TEST_EXISTS)) {
            g_warning("no stop word file for language code %s: bad language? "
                      "Will use English",
                      lang_code.c_str());
            path = WORDTIP_PKGDATADIR G_DIR_SEPARATOR_S "stop-words-en.txt";
            if (! Glib::file_test(path, Glib::FILE_TEST_EXISTS))
                g_warning("even the English is gone; expect the worst");
        }

        Glib::RefPtr<Gio::File> file = Gio::File::create_for_path(path);
        Glib::RefPtr<Gio::FileInputStream> istream = file->read();
        Glib::RefPtr<Gio::DataInputStream> dis =
            Gio::DataInputStream::create(istream);
        
        std::string word;
        while (dis->read_line(word)) {
            if (word.size() == 0) continue;
            stop_words_.push_back(word);
        }

        stemmer_ = Stemmer::create(lang_code);
    }

    shared_ptr<Language>
    Language::create(const ustring& lang_code)
    {
        return shared_ptr<Language>(new Language(lang_code));
    }

    bool
    Language::is_stop_word(const ustring& word)
    {
        return find(stop_words_.begin(),
                    stop_words_.end(),
                    word) != stop_words_.end();
    }

    ustring
    Language::stem_word(const ustring& word)
    {
        return stemmer_->stem_word(word);
    }

} // namespace wordtip
