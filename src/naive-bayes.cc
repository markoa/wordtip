
#include "naive-bayes.hh"

namespace wordtip {

    using std::map;
    using std::vector;
    using Glib::ustring;

    NaiveBayes::NaiveBayes(get_features_func_t func)
        : Classifier(func)
    {
    }

    float
    NaiveBayes::get_document_prob(const ustring& text, const ustring& cat)
    {
        vector<ustring> features;
        float pr = 1.;

        feature_f_(text, features);

        vector<ustring>::iterator it(features.begin());
        vector<ustring>::iterator end(features.end());

        for ( ; it != end; ++it)
            pr *= get_weighted_prob(*it, cat, &Classifier::get_cond_prob);

        return pr;
    }

    float
    NaiveBayes::get_prob(const ustring& text, const ustring& cat)
    {
        float cat_prob, doc_prob;

        cat_prob = static_cast<float>(get_category_count(cat)) /
                    get_total_document_count();

        doc_prob = get_document_prob(text, cat);

        return doc_prob*cat_prob;
    }

    void
    NaiveBayes::set_threshold(const ustring& cat, float threshold)
    {
        thresholds_[cat] = threshold;
    }
    
    float
    NaiveBayes::get_threshold(const ustring& cat)
    {
        if (thresholds_.find(cat) == thresholds_.end()) return 1.0;
        return thresholds_[cat];
    }

    ustring
    NaiveBayes::classify(const ustring& text, const ustring& default_cat)
    {
        ustring best_cat;

        // find the category with the highest probability
        float max = 0.;
        map<ustring, float> probs;
        
        vector<ustring> categories;
        get_categories(categories);

        vector<ustring>::iterator it(categories.begin());
        vector<ustring>::iterator end(categories.end());
        float tmp_max;

        for ( ; it != end; ++it) {
            tmp_max = get_prob(text, *it);
            probs[*it] = tmp_max;

            if (tmp_max > max) {
                max = tmp_max;
                best_cat = *it;
            }
        }

        // The probability should exceed next best probability
        // by more then its threshold.
        map<ustring, float>::iterator prob_it(probs.begin());
        map<ustring, float>::iterator prob_end(probs.end());

        for ( ; prob_it != prob_end; ++prob_it) {
            if (prob_it->first == best_cat) continue;
            if ((probs[prob_it->first] * get_threshold(best_cat)) > probs[best_cat])
                return default_cat;
        }

        return best_cat;
    }

} // namespace wordtip
