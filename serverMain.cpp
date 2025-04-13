#include <iostream>
#include <fstream>
#include "server.hpp"
#include "user.hpp"

using namespace std;


bool findUser(const std::string& filename, const std::string& userCredentials) {
    ifstream file(filename);
    if (!file.is_open()) {
        perror("Error opening file: ");
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find(userCredentials) != std::string::npos) {
            file.close();
            return true; // user found
        }
    }
    file.close();
    return false; // user not found
}

bool addUser(const std::string& filename, const std::string& userCredentials) {
    size_t pos = userCredentials.find(",");
    string username = userCredentials.substr(0, pos);
    string password = userCredentials.substr(pos + 1, userCredentials.length()-1); 


    //TODO: change 1 to the actual socket number
    User user(username, 1);
    std::ofstream outputFile(filename, std::ios::app);
    //checks if username in use
    ifstream file(filename);
    if (!file.is_open()) {
        perror("Error opening file: ");
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(",");
        string usernamecheck = line.substr(0, pos);
        if (username == usernamecheck) {
            file.close();
            cout << "username in use register failed\n";
            return false; // username already in use
        }
    }
    file.close();

    if (outputFile.is_open()) {
        outputFile << user.getUsername() <<"," << password <<"|" <<std::endl;
        outputFile.close();
        return true;
    } else {
      perror("unable to open file");
      return false;
    }
}

std::vector<std::string> thedata;
void loaddata(const std::string& filename){ // loads data from users.txt
    thedata.clear();
    ifstream file(filename);
    if (!file.is_open()) {
        perror("Error opening file: ");
    }

    std::string line;
    while (std::getline(file, line)) {
        thedata.push_back(line);
    }
    file.close();
}
void printdata(){
    for(size_t i = 0; i < thedata.size(); i++){
        cout << thedata[i] << endl;
    }
}
void storedata(const std::string& filename){
    std::ofstream outputfile(filename, std::ios::trunc);
    if (!outputfile){
        perror("Error opening file: ");
    }
    for(size_t i = 0; i < thedata.size(); i++){
        outputfile << thedata[i] << endl;
    }
}
void changepassword(std::string username,std::string newpassword){
    for(size_t i = 0; i < thedata.size(); i++){
        size_t pos = thedata[i].find(",");
        size_t end = thedata[i].find("|");
        string usernamecheck = thedata[i].substr(0, pos);
        if(username == usernamecheck){
            thedata[i].replace(pos+1,end-pos-1,newpassword);
        }
    }
}
std::string getlocations(std::string username){
for(size_t i = 0; i < thedata.size(); i++){
    string thelocations;
        size_t pos = thedata[i].find(",");
        size_t end = thedata[i].find("|");
        string usernamecheck = thedata[i].substr(0, pos);
        if(username == usernamecheck){
            thelocations = thedata[i].substr(end+1);
            return thelocations;
        }
    }
    return "";
}

void changelocations(std::string username, std::string entry){
    string thelocations;
    if(entry == "3" || entry == "2" || entry == "1"){ // if valid location
        for(size_t i = 0; i < thedata.size(); i++){
        
            size_t pos = thedata[i].find(",");
            size_t end = thedata[i].find("|");
            string usernamecheck = thedata[i].substr(0, pos);
            if(username == usernamecheck){
                thelocations = thedata[i].substr(end+1); 
                if(thelocations.find(entry) == std::string::npos){
            thelocations= thelocations + entry;
            thedata[i].replace(end+1,std::string::npos,thelocations);
                }
            }
        }
    }
    
}
void deletelocation(std::string username, std::string entry){
    string thelocations;
    if(entry == "3" || entry == "2" || entry == "1"){ // if valid location
        for(size_t i = 0; i < thedata.size(); i++){
        
            size_t pos = thedata[i].find(",");
            size_t end = thedata[i].find("|");
            string usernamecheck = thedata[i].substr(0, pos);
            if(username == usernamecheck){
                thelocations = thedata[i].substr(end+1); 
                size_t deletepos = thelocations.find(entry);
                if(deletepos != std::string::npos){
            thelocations.erase(deletepos, 1);
            thedata[i].replace(end+1,std::string::npos,thelocations);
                }
            }
        }
    }
    
}

std::string filename = "users.txt";
int main(){

    Server server(600003);
    bool loggedIn = false;
   
    
    server.start();
    server.acceptConnections(); 


   while (!loggedIn){

    string clientChoice = server.getMessage();
   
    if(clientChoice.compare("1") == 0){
        cout << "User Attempting Login" << endl;
        string credentials = server.getMessage();
        cout << credentials << endl;
        if(findUser(filename, credentials)){
       
            server.sendToClient("Valid");
            loggedIn = true;
          
        }
        else{
            cout << "Invalid Login Attempt" << endl;
            server.sendToClient("invalid");
  
        }
    }
    else if(clientChoice.compare("2") == 0){
        cout << "User Registering" << endl;
        string credentials = server.getMessage();
        cout << credentials << endl;
        if(addUser(filename, credentials)){
            cout << "User Registered" << endl;
            server.sendToClient("Successfully Registered!");
        }else{
            server.sendToClient("Unable to Register User, Username in use");
        }
    }

   }
    cout << "User logged in" << endl;
    std::string curuser;
    string returndata;
    loaddata(filename);
   while(true){
    
    string clientChoice = server.getMessage();
    // user wants to subscribe
    if(clientChoice[0] == '1'){ 
        clientChoice.erase(0,1);
        curuser = clientChoice;
        cout << "User wants to subscribe to a location";
        returndata = getlocations(curuser);
        server.sendToClient(returndata);
        clientChoice = server.getMessage();
        if(clientChoice[0]!= '0'){
            changelocations(curuser,clientChoice);
            storedata(filename);
        }
        
        
    }
    // user wants to unsubscribe
    else if(clientChoice[0] == '2'){ 
        clientChoice.erase(0,1);
        curuser = clientChoice;
        cout << "\nuser trying to unsubscribe\n";
        returndata = getlocations(curuser);
        server.sendToClient(returndata);
        clientChoice = server.getMessage();
        if(clientChoice[0]!= '0'){
            deletelocation(curuser,clientChoice);
            storedata(filename);
        }
    }
    // user wants to see subscriptions
    else if(clientChoice[0] == '3'){ 
        clientChoice.erase(0,1);
        curuser = clientChoice;
        cout << "\nuser wants to see subscriptions\n";
        returndata = getlocations(curuser);
        server.sendToClient(returndata);
    }
    // user wants to change password
    else if(clientChoice[0] == '4'){ 
        clientChoice.erase(0,1);
        curuser = clientChoice;
        cout << "user trying to change password\n";
        clientChoice = server.getMessage();
        cout << "\n test\n";
        cout << "user: " << curuser << " is changing password to : " << clientChoice << endl;
        changepassword(curuser,clientChoice);
        storedata(filename);
    }
    // user wants to log off
    else if(clientChoice[0] == '0'){ 
        clientChoice.erase(0,1);
        cout << "user: " << clientChoice <<" is logging off\n";
    }
    else if(clientChoice.compare("debug") == 0){ 
        cout << "Debug\n";
        loaddata(filename);
        printdata();
        cout << "\nstoredatatest\n";
        storedata(filename);
        printdata();
    }
   }

return 0;
}