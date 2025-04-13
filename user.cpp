#include "user.hpp" 
#include <algorithm>


User::User(){}


User::User(const std::string& username, int socketNo) {
    this->username = username;
    this ->socketNo = socketNo;
}


std::string User::getUsername(){
    return username;
}

std::vector<std::string> User::getLocations(){
    return locations;
}

void User::addLocation(const std::string& location){
    locations.push_back(location);
}

void User::removeLocation(const std::string& location){
    locations.erase(std::remove(locations.begin(), locations.end(), location), locations.end());
}

bool User::isSubscribedTo(const std::string& location){
    if(std::find(locations.begin(), locations.end(), location) != locations.end()){
        return true;
    }
    return false;
}

int User::getSocketNo(){
    return socketNo;
}

void User::setSocketNo(int socketNo){
    this->socketNo = socketNo;
}