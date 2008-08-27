
#ifndef WORDTIP_CLASSIFIER_HH
#define WORDTIP_CLASSIFIER_HH

#include <list>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include "feature-ex.hh"

namespace wordtip {

    // The mapping of category to a feature's occurrence count
    typedef std::map<Glib::ustring, int> class_count;

    class Classifier;
    typedef boost::function<float (Classifier*,
            const Glib::ustring& feat,
            const Glib::ustring& cat)> prob_func_t;

    // Stores the counts for different features in different
    // categories. For example:
    // { 'word1': {'funny': 4, 'boring': 1},
    //   'word2': {'funny': 0, 'boring': 5}, ... }
    typedef std::map<Glib::ustring, class_count> features;

    class Classifier
    {
    public:
        Classifier(get_features_func_t function);
        virtual ~Classifier() {}

        virtual void train(const Glib::ustring& text,
                           const Glib::ustring& category);

        // The number of times a feature has appeared in a category
        virtual float get_feature_count(const Glib::ustring& f,
                                        const Glib::ustring& cat);

        // The number of items in a category
        virtual float get_category_count(const Glib::ustring& cat);

        virtual float get_total_document_count();

        virtual void get_categories(std::vector<Glib::ustring>& cats);

        // Simple conditional probability that a word (feature)
        // is in a particular category.
        virtual float get_cond_prob(const Glib::ustring& feat,
                                    const Glib::ustring& cat);

        // A weighted average of prob_f and assumed probability.
        //
        // Assumed probability is the starting value used
        // for unknown features.
        // A weight of 1 means the assumed probability is weighted
        // the same as one word.
        virtual float get_weighted_prob(const Glib::ustring& feat,
                const Glib::ustring& cat, prob_func_t prob_f,
                float weight = 1.0, float assumed_prob = 0.5);

    protected:
        // Increase the count of a feature/category pair
        void inc_feature(const Glib::ustring& feature,
                         const Glib::ustring& category);

        void inc_category(const Glib::ustring& cat);

        get_features_func_t feature_f_;
        
        features features_;

        // A map of how many times every category has been used:
        class_count cc_;
    };

} // namespace wordtip

#endif // WORDTIP_CLASSIFIER_HH
