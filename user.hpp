#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include <unordered_map>


class User {

public:

    User();
    User(const std::string& username, int socketNo);
    std::string getUsername();
    std::vector<std::string> getLocations();
    //subscribe to a location
    void addLocation(const std::string& location);
    //unsubscribe to a location
    void removeLocation(const std::string& location);
    //returns true if subscribed to a location
    bool isSubscribedTo(const std::string& location);
    int getSocketNo();
    void setSocketNo(int socketNo);

   
private:
    std::string username;              
    std::vector<std::string> locations; // All locations the user is subscribed to
    int socketNo;                      
 
};

#endif 