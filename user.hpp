/*
File name: user.hpp
Description: contains the declarations of our user class that stores the user's information
*/
#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include <unordered_map>


class User {

public:
   //constructs an user object
    User();
   //constructs an user object given a username and socket number
    User(const std::string& username, int socketNo);
   //returns the user's username
    std::string getUsername();
    std::vector<std::string> getLocations();
    //subscribe to a location
    void addLocation(const std::string& location);
    //unsubscribe to a location
    void removeLocation(const std::string& location);
    //returns true if subscribed to a location
    bool isSubscribedTo(const std::string& location);
    //returns the user's socket number
    int getSocketNo();
    //sets the user's socket number
    void setSocketNo(int socketNo);

   
private:
    std::string username;              
    std::vector<std::string> locations; // All locations the user is subscribed to
    int socketNo;                      
 
};

#endif 