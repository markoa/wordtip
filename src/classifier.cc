
#include <iostream>
#include "classifier.hh"

namespace wordtip {

    using std::vector;
    using Glib::ustring;

    Classifier::Classifier(get_features_func_t function)
        : feature_f_(function)
    {
    }

    void
    Classifier::inc_feature(const ustring& feature, const ustring& category)
    {
        features_[feature][category]++;
    }

    void
    Classifier::inc_category(const ustring& cat)
    {
        cc_[cat]++;
    }

    float
    Classifier::get_feature_count(const ustring& f, const ustring& cat)
    {
        features::iterator fit = features_.find(f);
        if (fit == features_.end()) return 0.0;
        class_count::iterator cit = fit->second.find(cat);
        if (cit == fit->second.end()) return 0.0;
        return static_cast<float>(cit->second);
    }

    float
    Classifier::get_category_count(const ustring& cat)
    {
        class_count::iterator it = cc_.find(cat);
        if (it == cc_.end())
            return 0.0;
        else
            return static_cast<float>(it->second);
    }

    float
    Classifier::get_total_count()
    {
        int res = 0;
        
        class_count::iterator it(cc_.begin());
        class_count::iterator end(cc_.end());
        
        for ( ; it != end; ++it)
            res += it->second;

        return res;
    }

    void
    Classifier::get_all_categories(vector<ustring>& cats)
    {
        //TODO
    }

    void
    Classifier::train(const ustring& text, const ustring& category)
    {
        vector<ustring> words;
        feature_f_(text, words);

        vector<ustring>::iterator it(words.begin());
        vector<ustring>::iterator end(words.end());
        for ( ; it != end; ++it)
            inc_feature(*it, category);

        inc_category(category);
    }

} // namespace wordtip
