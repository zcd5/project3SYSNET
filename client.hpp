/*
File name: Client.hpp
Description: contains the declarations of our client class that sends and receives messages to the server
*/
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>


class Client{

public:

//Constructs a client given a port number and address
Client(int port, const std::string& address = "127.0.0.1");
//sends a message to the server
void sendMessage(const std::string& message);
//receives a message from the server
std::string receiveMessage();
//connects to the server
bool connectToServer();

private:
int port;
std::string address;
int tcp_client_socket;

};

#endif