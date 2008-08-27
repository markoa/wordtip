

#ifndef WORDTIP_NAIVE_BAYES_HH
#define WORDTIP_NAIVE_BAYES_HH

#include "classifier.hh"

namespace wordtip {

    class NaiveBayes : public Classifier
    {
    public:
        NaiveBayes(get_features_func_t func);
        virtual ~NaiveBayes() {}

        // Extracts the features and multiplies all their probabilities
        // together to get an overall probability.
        // Actually calculates Pr(Document | Category).
        virtual float get_document_prob(const Glib::ustring& text,
                                        const Glib::ustring& cat);

        // Returns naive Bayesian probability of category cat
        // given document text:
        //
        // Pr(cat | item) = Pr(item | cat) x Pr(cat)/Pr(item)
        //
        // Here we ignore Pr(item) as it's the same no matter
        // which item is given.
        virtual float get_prob(const Glib::ustring& text,
                               const Glib::ustring& cat);
    };

} // namespace wordtip

#endif // WORDTIP_NAIVE_BAYES_HH
