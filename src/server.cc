
#include <unistd.h>
#include <config.h>
#include "server.hh"

namespace wordtip {

    using std::string;

    const char* DBUS_SERVER_NAME = "org.freedesktop.Wordtip";
    const char* DBUS_SERVER_PATH = "/org/freedesktop/Wordtip";

    Server::Server(DBus::Connection& connection)
        : DBus::ObjectAdaptor(connection, DBUS_SERVER_PATH)
    {
    }

    string
    Server::Version()
    {
        return PACKAGE_VERSION;
    }

    string
    Server::Echo(const string& msg)
    {
        sleep(5);
        return "you said: '" + msg + "'";
    }

} // namespace wordtip
