/************************************************** Description *******************************************************/
/*
    File : TCP.cpp
    Programmer : Mohammad Lotfi
    Used : TCP Socket
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2024/10/21
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include "TCP.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
using namespace std;
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
namespace net {
/*--------------------------------------------------------------------------------------------------------------------*/
std::queue<TCP::struct_Listen::struct_Status> * TCP::AddListen(int Port, bool (*CallBack)(int Socket, char* Data, int* Length)) {  
    struct_Listen *Listen = new struct_Listen();
    if(Listen) {                
        /* Initialize TCP Socket */      
        Listen->CallBack = CallBack;
        Listen->Server.Addr.sin_port = htons(Port);
        Listen->Server.Addr.sin_family = AF_INET;
        Listen->Server.Addr.sin_addr.s_addr = INADDR_ANY; 
        try {
            Listen->Server.Socket = socket(AF_INET, SOCK_STREAM, 0);
            if (Listen->Server.Socket < 0) {
                /* ERROR opening socket */
                Listen->Status.push({-1, "Error opening socket"});
                delete Listen;
                return nullptr;
            }
            /* MESSEGE on accept */
            Listen->Status.push({0, "Opened socket " + to_string(Listen->Server.Socket)});
            if (bind(Listen->Server.Socket, (struct sockaddr *) &Listen->Server.Addr, sizeof(sockaddr_in)) < 0) {
                /* ERROR on binding */
                close(Listen->Server.Socket);
                Listen->Status.push({-2, "Error listening on bind"});
                delete Listen;
                return nullptr;
            }
            /* MESSEGE on accept */
            Listen->Status.push({0, "Listening on socket " + to_string(Listen->Server.Socket)});
            listen(Listen->Server.Socket, 5);
            thread t([Listen](){
                while (true) {                    
                    /* Accept client */
                    struct_Listen::struct_Client *Client = new struct_Listen::struct_Client();
                    socklen_t Client_len = sizeof(sockaddr_in);
                    Client->Socket = accept(Listen->Server.Socket, (struct sockaddr *) &Client->Addr, &Client_len);
                    if (Client->Socket < 0) {
                        /* ERROR on accept */
                        Listen->Status.push({-3, "Error on accept client"});
                        delete Client;
                        return;
                    }
                    /* MESSEGE on accept */
                    Listen->Status.push({0, "Client opened from socket " + to_string(Client->Socket)});
                    thread c([Listen,Client]() {
                        while(true) {
                            memset(Client->Buffer, 0, TCP_SIZEOF_BUFFER);
                            int32_t Length = read(Client->Socket, Client->Buffer, TCP_SIZEOF_BUFFER);
                            if (Length <= 0) {                                                            
                                close(Client->Socket);
                                if(Length<0) {
                                    /* ERROR reading from socket */
                                    Listen->Status.push({-4, "Error client reading from socket " + to_string(Client->Socket)});
                                }
                                else {
                                    /* ERROR reading from socket */
                                    Listen->Status.push({-4, "Client closed from socket " + to_string(Client->Socket)});
                                }
                                delete Client;
                                return;
                            }
                            if(Listen->CallBack(Client->Socket, Client->Buffer, &Length)) {
                                if(Length) {
                                    Length = write(Client->Socket, Client->Buffer, Length);
                                    if (Length < 0) {
                                        close(Client->Socket);
                                        /* ERROR writing to socket */
                                        Listen->Status.push({-5, "Error client writing to socket " + to_string(Client->Socket)});
                                        delete Client;
                                        return;
                                    }
                                }                    
                            }                    
                        }
                    });
                    c.detach(); 
                }
            });
            t.detach();            
        } 
        catch (...) {
            //close(Listen->Client.Socket);
            close(Listen->Server.Socket);
            delete Listen;
            return nullptr;
        }
        return &Listen->Status;
    }
    return nullptr;
}
/*--------------------------------------------------------------------------------------------------------------------*/
}
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
