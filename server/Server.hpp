#pragma once

#include "Client.hpp"

#include <vector>
#include <memory>

namespace babel {

    class Server {

        public:
            virtual void run() = 0;
            virtual std::vector<std::shared_ptr<Client>> getClients() = 0;
            virtual void addClient(std::shared_ptr<Client> client) = 0;
    };
    
}
