
#include "naive-bayes.hh"

namespace wordtip {

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

} // namespace wordtip
