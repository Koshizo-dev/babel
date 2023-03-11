#include <asio.hpp>
#include <asio/io_service.hpp>
#include <iostream>
#include <string>

using asio::ip::tcp;

class Client {
public:
  Client(asio::io_service &io_service) : socket_(io_service) {}

  tcp::socket &socket() { return socket_; }

  void start() {
    std::cout << "New client connected\n";
    read();
  }

  void read() {
    asio::async_read_until(socket_, buf_, "\n",
                           [this](std::error_code ec, std::size_t /*length*/) {
                             if (!ec) {
                               std::string message = std::string(
                                   asio::buffer_cast<const char *>(buf_.data()),
                                   buf_.size());
                               std::cout << "Received: " << message << "\n";
                               write("Echo: " + message);
                             }
                           });
  }

  void write(const std::string &message) {
    asio::async_write(socket_, asio::buffer(message),
                      [this](std::error_code ec, std::size_t /*length*/) {
                        if (!ec) {
                          read();
                        }
                      });
  }

private:
  tcp::socket socket_;
  asio::streambuf buf_;
};

class Server {
public:
  Server(asio::io_service &io_service, short port)
      : io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
  }

  void start_accept() {
    auto new_client = std::make_shared<Client>(io_service_);

    acceptor_.async_accept(new_client->socket(),
                           [this, new_client](std::error_code ec) {
                             if (!ec) {
                               new_client->start();
                             }
                             start_accept();
                           });
  }

private:
  asio::io_service &io_service_;
  tcp::acceptor acceptor_;
};

int main() {
  try {
    asio::io_service io_service;
    Server server(io_service, 8080);
    io_service.run();
  } catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
