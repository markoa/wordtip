
#ifndef WORDTIP_SERVER_HH
#define WORDTIP_SERVER_HH

#include <string>
#include <boost/shared_ptr.hpp>
#include <dbus-c++/dbus.h>
#include "server-glue.hh"

namespace wordtip {

    extern const char* DBUS_SERVER_NAME;
    extern const char* DBUS_SERVER_PATH;

    class NaiveBayes;

    class Server
        : public org::freedesktop::Wordtip_adaptor,
        public DBus::IntrospectableAdaptor,
        public DBus::ObjectAdaptor
    {
    public:
        Server(DBus::Connection& connection);

        void SetThreshold(const std::string& cat, const double& threshold);

        double GetThreshold(const std::string& cat);

        void Train(const std::string& text, const std::string& cat);
        
        std::string Classify(const std::string& text);

    protected:
        boost::shared_ptr<NaiveBayes> classifier_;
    };

} // namespace wordtip

#endif // WORDTIP_SERVER_HH
