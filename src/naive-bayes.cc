
#include "feature-ex.hh"
#include "language.hh"
#include "naive-bayes.hh"

namespace wordtip {

    using std::map;
    using std::vector;
    using boost::shared_ptr;
    using Glib::ustring;

    NaiveBayes::NaiveBayes(shared_ptr<Language> lang)
        : Classifier(lang)
    {
    }

    double
    NaiveBayes::get_document_prob(const ustring& text, const ustring& cat)
    {
        vector<ustring> features;
        double pr = 1.;

        split_simple(text, features);

        vector<ustring>::iterator it(features.begin());
        vector<ustring>::iterator end(features.end());

        for ( ; it != end; ++it) {
            if (lang_->is_stop_word(*it)) continue;
            ustring stemmed_word(lang_->stem_word(*it));

            pr *= get_weighted_prob(stemmed_word, cat);
        }

        return pr;
    }

    double
    NaiveBayes::get_prob(const ustring& text, const ustring& cat)
    {
        double cat_prob, doc_prob;

        cat_prob = static_cast<double>(get_category_count(cat)) /
                    get_total_document_count();

        doc_prob = get_document_prob(text, cat);

        return doc_prob*cat_prob;
    }

    void
    NaiveBayes::set_threshold(const ustring& cat, double threshold)
    {
        thresholds_[cat] = threshold;
    }
    
    double
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
        double max = 0.;
        map<ustring, double> probs;
        
        vector<ustring> categories;
        get_categories(categories);

        vector<ustring>::iterator it(categories.begin());
        vector<ustring>::iterator end(categories.end());
        double tmp_max;

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
        map<ustring, double>::iterator prob_it(probs.begin());
        map<ustring, double>::iterator prob_end(probs.end());

        for ( ; prob_it != prob_end; ++prob_it) {
            if (prob_it->first == best_cat) continue;
            if ((probs[prob_it->first] * get_threshold(best_cat)) > probs[best_cat])
                return default_cat;
        }

        return best_cat;
    }

} // namespace wordtip
