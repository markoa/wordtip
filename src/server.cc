
#include "naive-bayes.hh"
#include "server.hh"

namespace wordtip {

    using std::string;

    const char* DBUS_SERVER_NAME = "org.freedesktop.Wordtip";
    const char* DBUS_SERVER_PATH = "/org/freedesktop/Wordtip";

    Server::Server(DBus::Connection& connection)
        : DBus::ObjectAdaptor(connection, DBUS_SERVER_PATH)
    {
        classifier_.reset(new NaiveBayes(&wordtip::split_simple));
    }

    void
    Server::SetThreshold(const string& cat, const double& threshold)
    {
        classifier_->set_threshold(cat, threshold);
    }

    double
    Server::GetThreshold(const string& cat)
    {
        return classifier_->get_threshold(cat);
    }
        
    void
    Server::Train(const string& text, const string& cat)
    {
        classifier_->train(text, cat);
    }

    string
    Server::Classify(const string& text)
    {
        return classifier_->classify(text);
    }

} // namespace wordtip
