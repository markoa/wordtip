
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

        // The total number of items
        virtual float get_total_count();

        virtual void get_all_categories(std::vector<Glib::ustring>& cats);

        // Simple conditional probability that a word (feature)
        // is in a particular category.
        virtual float get_cond_prob(const Glib::ustring& feat,
                                    const Glib::ustring& cat);

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
