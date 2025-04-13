#include "server.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <netinet/in.h>
#include <unistd.h> 
#include <cstring>
#include <fstream>

using namespace std;

Server::~Server(){
    if(tcp_client_socket>0){
        close(tcp_client_socket);
    }
    if (tcp_server_socket>0){
        close(tcp_server_socket);
    }
}
Server::Server(int port){
    this->port = port;
}

bool Server::start(){
tcp_server_socket = socket(AF_INET, SOCK_STREAM, 0);
if(tcp_server_socket == 0){
    perror("Socket creation failed");
    return false;
}
struct sockaddr_in serverAddress;
serverAddress.sin_family = AF_INET;
serverAddress.sin_addr.s_addr = INADDR_ANY;
serverAddress.sin_port = htons(port);

if (bind(tcp_server_socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
    perror("Error binding socket");
    return false;
}

if (listen(tcp_server_socket, 5) < 0) {
     perror("Error listening on socket");
    return false;
}

std::cout << "Server has started on port " << port << std::endl;
return true;
}


void Server::acceptConnections(){
    char tcp_server_message[256] = " Hello, you have successfully connected to the TCP Server \n";

    tcp_client_socket = accept(tcp_server_socket, NULL, NULL);
    std:: cout << "Client has connected!" <<std:: endl; 
    send(tcp_client_socket, tcp_server_message, sizeof(tcp_server_message), 0);
    close(tcp_client_socket);

}

std::string Server::getMessage(){

char databuffer[1500];

tcp_client_socket = accept(tcp_server_socket, NULL, NULL);


while(true){
if(tcp_client_socket < 0){
    continue;
}



memset(databuffer, '\0', sizeof(databuffer));
recv(tcp_client_socket, &databuffer, sizeof(databuffer),0);


string clientMessage = databuffer;
return clientMessage;
}

}

void Server::sendToClient(const std::string& message){

   send(tcp_client_socket, message.c_str(), message.length(), 0);
  
    }
