//Name: Chakravorty, Naireet
//Project: PA-1(Programming)
//Instructor: Feng Chen
//Class: cs7103-au19
//LogonID: cs710303
#include <iostream>
#include <sys/types.h>          
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <netinet/in.h>

using namespace std;

int main(){

    //address to connect to
    string ipAddress = "127.0.0.1";
    int port = 42000; //listening port # on server

    //create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in hint;
    //struct hostent* server = gethostbyname("127.0.0.1");
    //bcopy((char *)server->h_addr, 
    //    (char *)&hint.sin_addr.s_addr,
    //   server->h_length);
    
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    //hint.sin_addr.s_addr = inet_addr("127.0.0.1");
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);
    int conn_status = connect(clientSocket, 
                             (sockaddr*) &hint, 
                             sizeof(hint));
    //check connection for error
    if (conn_status == -1){

        cerr << "Could not connect to the remote socket"<< endl;
        exit(0);

    }
    cout << "Connected to the server" << endl;

    //receiving stuff from server
    char msgBuff [4096]; // string to put stuff in from server
    string userInput;
    do{

        cout << "> ";
        getline(cin, userInput);
        
        //Clear msgBuffer first
        int sendResult = send (clientSocket, userInput.c_str(), userInput.size() + 1, 0);    
        //TODO: will have checks here
        if (sendResult == -1){
            cerr << "Could not send to server!" << endl;
            continue;
        }


        memset(msgBuff, 0, 4096);
        //receive message from server
        int rcvd = recv(clientSocket, msgBuff, sizeof(msgBuff), 0); // putting it in the string
        if (rcvd == -1){
                cerr << "Something went wrong with server" << endl;
                break;
            }

        //Display message
            cout << "Server:> " << string(msgBuff, 0, rcvd) << endl;


    }while(true);
    close(clientSocket);
    cout << "Leaving server" << endl;

    return 0;
}
