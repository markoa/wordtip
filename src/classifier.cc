
#include <iostream>
#include "classifier.hh"
#include "feature-ex.hh"
#include "language.hh"

namespace wordtip {

    using std::tr1::shared_ptr;
    using std::vector;
    using Glib::ustring;

    Classifier::Classifier(shared_ptr<Language> lang)
        : lang_(lang)
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
    Classifier::get_total_document_count()
    {
        int res = 0;
        
        class_count::iterator it(cc_.begin());
        class_count::iterator end(cc_.end());
        
        for ( ; it != end; ++it)
            res += it->second;

        return res;
    }

    void
    Classifier::get_categories(vector<ustring>& cats)
    {
        class_count::iterator it(cc_.begin());
        class_count::iterator end(cc_.end());
        
        for ( ; it != end; ++it)
            cats.push_back(it->first);
    }

    void
    Classifier::train(const ustring& text, const ustring& category)
    {
        vector<ustring> words;
        split_simple(text, words);

        vector<ustring>::iterator it(words.begin());
        vector<ustring>::iterator end(words.end());
        for ( ; it != end; ++it) {
            if (lang_->is_stop_word(*it)) continue;
            ustring stemmed_word(lang_->stem_word(*it));
            inc_feature(stemmed_word, category);
        }

        inc_category(category);
    }

    float
    Classifier::get_cond_prob(const ustring& feat, const ustring& cat)
    {
        if (cc_.find(cat) == cc_.end()) return 0.0;
        return get_feature_count(feat, cat) / get_category_count(cat);
    }

    float
    Classifier::get_weighted_prob(const ustring& feat, const ustring& cat, 
            float weight, float assumed_prob)
    {
        //TODO: the probability function might need to be arbitrary later
        float basic_prob = get_cond_prob(feat, cat);

        vector<ustring> categories;
        get_categories(categories);
        
        float totals = 0.;
        vector<ustring>::iterator it(categories.begin());
        vector<ustring>::iterator end(categories.end());
        for ( ; it != end; ++it) totals += get_feature_count(feat, *it);

        float res = 0.;
        res = ((weight*assumed_prob) + (totals*basic_prob)) / (weight+totals);
        return res;
    }

} // namespace wordtip
