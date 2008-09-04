
#include <iostream>
#include <glibmm/regex.h>
#include "feature-ex.hh"
#include "stop-words-en.hh"

namespace wordtip {

    using std::vector;
    using Glib::ustring;

    void
    split_simple(const ustring& txt, vector<ustring>& words)
    {
        // since we have unicode text, the only safe bet is to split by
        // whitespace. then we can strip some special characters.
        vector<ustring> split_words = Glib::Regex::split_simple("\\s+", txt);

        ustring spec_chars = "[,.!@#\\$\\%\\^\\&\\*\\(\\)"
                                "\\_\\+\\=\\[\\]\\;\\/]";
        Glib::RefPtr<Glib::Regex> regex = Glib::Regex::create(spec_chars);

        vector<ustring> stop_words;
        load_stop_words_en(stop_words);

        vector<ustring>::iterator it(split_words.begin());
        vector<ustring>::iterator end(split_words.end());
        vector<ustring>::iterator sw_end(stop_words.end());
        ustring none = "";

        for ( ; it != end; ++it) {
            ustring replaced = regex->replace(*it, 0, none,
                        static_cast<Glib::RegexMatchFlags>(0));
            ustring word(replaced.lowercase());

            bool is_stop_word =
                find(stop_words.begin(), stop_words.end(), word) != sw_end; 
            
            if (word.size() > 2 && word.size() < 20 && (! is_stop_word))
                words.push_back(word);
        }
    }

} // namespace wordtip

