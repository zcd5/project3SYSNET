/*
File name: ClientMain.cpp
Description: the entry point of our client class that handles communication from the user to the server
*/
#include <iostream>
#include "client.hpp"

using namespace std;

int port = 600003;

int main(){
    string hostname;
    string input;
    string username;
    string password;
    bool loggedIn = false;

    cout << "Enter the hostname: ";
    cin >> hostname;

    if(hostname.compare("localhost") == 0){
        cout << "local host resolved to 127.0.0.1" << endl;
        hostname = "127.0.0.1";
    }else{
        //if anotherhost besides local host is given, it will default to connecting to the localhost
        cout << hostname << " is not available, connecting to local host instead" << endl;
        hostname = "127.0.0.1";
    }
        

    Client client(port, hostname);
    
    const string message = "Hello Server, this is the client";
    client.connectToServer();

//When a user is not logged in
    while(!loggedIn){
    cout << "Welcome!" << endl;
    cout << "Press 1 to Login" << endl;
    cout << "Press 2 to Register" << endl;
    cout << "Type 'exit' to Quit" << endl;
    cin >> input;

    if(input.compare("1") == 0){
        cout << "login" << endl;
        client.sendMessage("1");
        
        cout << "Enter your username: " << endl;
        cin >> username;
        cout << endl;

        cout << "Enter your password: " << endl;
        cin >> password;
        cout << endl;


        string credentials = username + "," + password;
        client.sendMessage(credentials);
        if(client.receiveMessage().compare("Valid") == 0){
            cout << "This user is valid" << endl;
            loggedIn = true;
        }
        else{
            cout << "This is not a valid user. Please register" << endl;
        }

    }else if(input.compare("2") == 0){
        cout << "register" << endl;
        client.sendMessage("2");

        cout << "Enter your username: " << endl;
        cin >> username;
        cout << endl;
         
        cout << "Enter your password: " << endl;
        cin >> password;
        cout << endl;
        
        string credentials = username + "," + password;
        client.sendMessage(credentials);

        string response = client.receiveMessage();
        cout << response << endl;

    }else if(input.compare("exit") == 0){
        exit(0);

    }else{
        cout << "Invalid option" << endl;
    }

}


//When a user is logged in
cout << "Successfully logged in!" << endl;

    while(loggedIn){

    cout << "1 - Subscribe to a location" << endl;
    cout << "2 - Unsubsribe to a location" << endl;
    cout << "3 - See subscribed locations" << endl;
    cout << "4 - Change Password" << endl;
    cout << "0 - Quit" << endl;
    cin >> input;
    string newmessage;
    string location;
    if(input.compare("1") == 0){
        newmessage = "1" + username;
        client.sendMessage(newmessage);
        cout << "these are your currently Subscribed locations:\n";
        newmessage = client.receiveMessage();
        if(newmessage.find('1') != std::string::npos){
            cout << "1 - Pensacola\n";
        }
        if(newmessage.find('2') != std::string::npos){
            cout << "2 - Milton\n";
        }
        if(newmessage.find('3') != std::string::npos){
            cout << "3 - Mobile\n";
        }
        cout << "Insert location you would like to Subscribe:" << endl;
        cout << "Type the number(ex 1) Options: \n1-Pensacola\n2-Milton\n3-Mobile\n";
        cout << "0-exit\n";
        cin >> location;
        client.sendMessage(location);
        

    }else if(input.compare("2") == 0){
        newmessage = "2" + username;
        client.sendMessage(newmessage);
        cout << "these are your currently Subscribed locations:\n";
        newmessage = client.receiveMessage();
        if(newmessage.find('1') != std::string::npos){
            cout << "1 - Pensacola\n";
        }
        if(newmessage.find('2') != std::string::npos){
            cout << "2 - Milton\n";
        }
        if(newmessage.find('3') != std::string::npos){
            cout << "3 - Mobile\n";
        }
        cout << "Insert location you would like to Unsubscribe:" << endl;
        cin >> location;
        client.sendMessage(location);
        
    }else if(input.compare("3") == 0){
        newmessage = "3" + username;
        client.sendMessage(newmessage);
        newmessage = client.receiveMessage();
        cout << "Your Subscribed Locations are :\n";
        if(newmessage.find('1') != std::string::npos){
            cout << "1 - Pensacola\n";
        }
        if(newmessage.find('2') != std::string::npos){
            cout << "2 - Milton\n";
        }
        if(newmessage.find('3') != std::string::npos){
            cout << "3 - Mobile\n";
        }
    }

    else if(input.compare("4") == 0){
        newmessage = "4" + username;
        client.sendMessage(newmessage);
        bool done = false;
        string newpassword;
        string confirmpassword;
        while(!done){
            cout << "Enter New Password:\n";
            cin >> newpassword;
            cout << "Enter Confirm New Password:\n";
            cin >> confirmpassword;
            if(newpassword!=confirmpassword){
                cout << "confirm password failed\n";
            } else{
                done = true;
            }
        }
        client.sendMessage(newpassword);

    }else if(input.compare("0") == 0){
        newmessage = "0" + username;
        client.sendMessage(newmessage);
        exit(0);
    }else if(input.compare("9") == 0){ // used for testing
    // tells server to cout data
        client.sendMessage("debug");
        
    }
    else{
        cout << "Invalid option!" << endl;
    }

    }

return 0;
}