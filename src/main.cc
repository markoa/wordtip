
#include <signal.h>
#include <iostream>
#include "classifier.hh"
#include "server.hh"

DBus::BusDispatcher dispatcher;

void
interrupt_handler(int sig)
{
    std::cout << "wordtip shutting down on signal " << sig << std::endl;
    dispatcher.leave();
}


int
main(int /*argc*/, char** /*argv*/)
{
    std::cout << "wordtip running" << std::endl;
    
    signal(SIGTERM, interrupt_handler);
    signal(SIGINT, interrupt_handler);

    DBus::default_dispatcher = &dispatcher;

    DBus::Connection conn = DBus::Connection::SessionBus();
    conn.request_name(wordtip::DBUS_SERVER_NAME);

    wordtip::Server server(conn);

    dispatcher.enter();

    return 0;
}
