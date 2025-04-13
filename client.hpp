#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>


class Client{

public:


Client(int port, const std::string& address = "127.0.0.1");
void sendMessage(const std::string& message);
std::string receiveMessage();
bool connectToServer();

private:
int port;
std::string address;
int tcp_client_socket;

};

#endif