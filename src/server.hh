
#ifndef WORDTIP_SERVER_HH
#define WORDTIP_SERVER_HH

#include <string>
#include <dbus-c++/dbus.h>
#include "server-glue.hh"

namespace wordtip {

    extern const char* DBUS_SERVER_NAME;
    extern const char* DBUS_SERVER_PATH;

    class Server
        : public org::freedesktop::Wordtip_adaptor,
        public DBus::IntrospectableAdaptor,
        public DBus::ObjectAdaptor
    {
    public:
        Server(DBus::Connection& connection);

        std::string Echo(const std::string& msg);
        std::string Version();
    };

} // namespace wordtip

#endif // WORDTIP_SERVER_HH
