#pragma once

#include <string>

namespace babel {

class Server {
public:
    Server(std::string name, unsigned int port): _name(name), _port(port) {}
    const std::string getName(void);
protected:
private:
    const unsigned int _port;
    const std::string _name;
};

} // namespace babel
