#ifndef SERVER_HPP
#define SERVER_HPP



#include <string>

class Server{


public:
// destroys socket when ending program
~Server();
//Constructs for server object using a port number
Server(int port);
//returns true if successfully sends the client a message
bool sendToClient(int client_id, const std::string& data);
// Starts the server
bool start();
//sets buffer for incoming message
std::string getMessage();
//accepts connections from clients
void acceptConnections();
//sends message to client
void sendToClient(const std::string& message);


private:
    int port;
    int tcp_server_socket;
    int tcp_client_socket;
    
};




#endif