/************************************************** Description *******************************************************/
/*
    File : main.cpp
    Programmer : Mohammad Lotfi
    Used : Site
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
#include "Defines.hpp"
#include "TCP.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
using namespace std;
using namespace net;
/************************************************** Variables *********************************************************/
std::mutex Mutex_print;
/************************************************** Opjects ***********************************************************/
TCP *tcp;
/************************************************** Functions *********************************************************/
void Print(string str) {
    /* Lock untile return of block */
    std::lock_guard<std::mutex> guard(Mutex_print);
    /* Show on console */
    std::cout << str << endl;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool Core_CallBack (int Socket, char* Data, int* Length) {
    Print(Data);
    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool UI_CallBack (int Socket, char* Data, int* Length) {

    string Line = "";
    ifstream file;
    struct stat info;
    string filename = "index.html";

    stat(filename.c_str(), &info); 

    sprintf(Data, "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: %ld\n\n", info.st_size);
    *Length = strlen(Data);
    tcp->Send(Socket, Data, strlen(Data));
    file.open(filename);  
    while (getline(file, Line)) {
        tcp->Send(Socket, (char*)Line.c_str(), Line.length());
    }
    file.close();

    *Length = 0;
    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv) {
    /* Sample */
    // sudo ./main -p 1020
    /* Check arguments */
    if(argc < 2) {
        Print("ERROR: Number of arguments is below than 2");
    }
    try
    {
        /* Select jobs */
        for(int Index=1; Index<argc; Index++) {
            if(strcmp(argv[Index], "-p")==0) {
                Index++;
                int Port = atoi(argv[Index]);           
                tcp = new TCP();
                std::queue<TCP::struct_Listen::struct_Status> * UI_Status = tcp->AddListen(Port, UI_CallBack); 
                std::queue<TCP::struct_Listen::struct_Status> * Core_Status = tcp->AddListen(Port+1, Core_CallBack);                               
                if(Core_Status && UI_Status) {
                    while (true) {
                        if(!UI_Status->empty()) {
                            Print("UI Messege : [" + UI_Status->front().Messege + "] Error : [" + to_string(UI_Status->front().Error) + "]");  
                            UI_Status->pop();
                        } 
                        if(!Core_Status->empty()) {
                            Print("Core Messege : [" + Core_Status->front().Messege + "] Error : [" + to_string(Core_Status->front().Error) + "]");  
                            Core_Status->pop();
                        }                                                
                    }
                }
                else {
                    Print("ERROR: Create server!");
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
	 /* Exit */
     return 0; 
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
