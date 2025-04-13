#include "client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>




Client::Client(int port, const std::string& address){
    this->address = address;
    this->port = port;
}

bool Client::connectToServer(){
tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0);
if(tcp_client_socket < 0){
    perror("Error creating socket");
    return false;
}

struct sockaddr_in tcp_server_address;
tcp_server_address.sin_family = AF_INET;
tcp_server_address.sin_port = htons(port); 
tcp_server_address.sin_addr.s_addr = inet_addr(address.c_str());
int address_size = sizeof(tcp_server_address);

int connection = connect(tcp_client_socket, (struct sockaddr *)&tcp_server_address, address_size); 
if(connection < 0){
    perror("Error connecting to the server!");
    return false;
}

//Receives connection establishment message from the server
char tcp_server_response[256];
recv(tcp_client_socket, &tcp_server_response, sizeof(tcp_server_response), 0);
std::cout << "Server:" << tcp_server_response << std::endl;
close(tcp_client_socket);
return true;
}

void Client:: sendMessage(const std::string& message){
    struct sockaddr_in tcp_server_address;
    tcp_server_address.sin_family = AF_INET;
    tcp_server_address.sin_port = htons(port); 
    tcp_server_address.sin_addr.s_addr = inet_addr(address.c_str());


   tcp_client_socket = socket(AF_INET, SOCK_STREAM, 0);
   connect(tcp_client_socket, (struct sockaddr *)&tcp_server_address, sizeof(tcp_server_address));  
   char databuffer[3000];
   std::string sentmessage = message;
   memset(databuffer, '\0', sizeof(databuffer));
   send(tcp_client_socket,sentmessage.c_str(),sentmessage.length(),0);


}

std::string Client::receiveMessage(){

char tcp_server_response[256];
recv(tcp_client_socket, &tcp_server_response, sizeof(tcp_server_response), 0);
std::string response = tcp_server_response;
close(tcp_client_socket);

return response;
    
}