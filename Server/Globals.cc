/* Copyright (c) 2012 Stanford University
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR(S) DISCLAIM ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL AUTHORS BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <signal.h>

#include "Core/Debug.h"
#include "Core/StringUtil.h"
#include "Protocol/Common.h"
#include "RPC/Server.h"
#include "Server/ClientService.h"
#include "Server/Globals.h"
#include "Server/LogManager.h"

namespace LogCabin {
namespace Server {

////////// Globals::SigIntHandler //////////

Globals::SigIntHandler::SigIntHandler(Event::Loop& eventLoop)
    : Signal(eventLoop, SIGINT)
{
}

void
Globals::SigIntHandler::handleSignalEvent()
{
    VERBOSE("Received SIGINT; shutting down.");
    eventLoop.exit();
}

////////// Globals //////////

Globals::Globals()
    : config()
    , eventLoop()
    , sigIntHandler(eventLoop)
    , logManager()
    , clientService()
    , rpcServer()
{
}

Globals::~Globals()
{
    // LogManager assumes it and its logs have no active users when it is
    // destroyed. Currently, the only user is clientService, and this is
    // guaranteed by clientService's destructor.
}

void
Globals::init()
{
    if (logManager.getExclusiveAccess().get() == NULL) {
        logManager.reset(new LogManager(config));
    }

    if (!clientService) {
        clientService.reset(new Server::ClientService(*this));
    }

    if (!rpcServer) {
        rpcServer.reset(new RPC::Server(eventLoop,
                                        Protocol::Common::MAX_MESSAGE_LENGTH));

        uint32_t maxThreads = config.read<uint16_t>("maxThreads", 16);
        rpcServer->registerService(Protocol::Common::ServiceId::CLIENT_SERVICE,
                                   clientService,
                                   maxThreads);

        std::string configServers = config.read<std::string>("servers", "");
        std::vector<std::string> listenAddresses =
            Core::StringUtil::split(configServers, ';');
        if (listenAddresses.empty()) {
            PANIC("No server addresses specified to listen on. "
                  "You must set the 'servers' configuration option.");
        }
        std::string error;
        for (auto it = listenAddresses.begin();
             it != listenAddresses.end();
             ++it) {
            RPC::Address address(*it, Protocol::Common::DEFAULT_PORT);
            error = rpcServer->bind(address);
            if (error.empty()) {
                NOTICE("Serving on %s", address.toString().c_str());
                break;
            }
        }
        if (!error.empty()) {
            PANIC("Could not bind to any server address in: %s. "
                  "Last error was: %s",
                  configServers.c_str(),
                  error.c_str());
        }
    }
}

void
Globals::run()
{
    eventLoop.runForever();
}

} // namespace LogCabin::Server
} // namespace LogCabin
