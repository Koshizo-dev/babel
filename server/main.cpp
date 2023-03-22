#include "entities/AsioServer.hpp"
#include <iostream>
#include <memory>
#include <string>

using namespace babel;

int main() {
    std::shared_ptr<Server> server(new AsioServer(8080));

    server->run();

    return (0);
}
