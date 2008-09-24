

#ifndef WORDTIP_NAIVE_BAYES_HH
#define WORDTIP_NAIVE_BAYES_HH

#include "classifier.hh"

namespace wordtip {

    class Language;

    class NaiveBayes : public Classifier
    {
    public:
        NaiveBayes(boost::shared_ptr<Language> lang);
        virtual ~NaiveBayes() {}

        // Extracts the features and multiplies all their probabilities
        // together to get an overall probability.
        // Actually calculates Pr(Document | Category).
        virtual double get_document_prob(const Glib::ustring& text,
                                         const Glib::ustring& cat);

        // Returns naive Bayesian probability of category cat
        // given document text:
        //
        // Pr(cat | text) = Pr(text | cat) x Pr(cat)/Pr(text)
        //
        // Here we ignore Pr(text) as it's the same no matter
        // which item is given.
        virtual double get_prob(const Glib::ustring& text,
                                const Glib::ustring& cat);

        // Any resulting classification, when calculated, should be larger
        // then the nearest result by a certain threshold.
        virtual void set_threshold(const Glib::ustring& cat, double threshold);
        virtual double get_threshold(const Glib::ustring& cat);

        // The actual Naive Bayes classification method.
        virtual Glib::ustring classify(const Glib::ustring& text, const Glib::ustring& default_cat = Glib::ustring());

    protected:
        std::map<Glib::ustring, double> thresholds_;
    };

} // namespace wordtip

#endif // WORDTIP_NAIVE_BAYES_HH
