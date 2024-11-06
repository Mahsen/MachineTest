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
    Last Update : 2024/11/6
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
#include "../Core/Defines.hpp"
#include "../Module/TCP.hpp"
/************************************************** Defineds **********************************************************/
#define MAIN_UI_ROOT                                     "../UI"
#define MAIN_UI_PAGE_DEFAULT                             "/index.html"
/************************************************** Names *************************************************************/
using namespace std;
using namespace net;
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
TCP *tcp;
/************************************************** Functions *********************************************************/
bool Core_CallBack (int Socket, char* Data, int* Length) {
    Print(Data);

    tcp->Close(Socket);
    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool UI_CallBack (int Socket, char* Data, int* Length) {

    string Line = "";
    ifstream file;
    struct stat info;
    string filename = MAIN_UI_ROOT + string(MAIN_UI_PAGE_DEFAULT);

    //Print(Data);

    if(strstr(Data, "GET /")) {
        vector<string> ParameterGET = split(string(Data), " ");
        
        if(ParameterGET[1].size() > 1) {
            filename = MAIN_UI_ROOT + ParameterGET[1];
            Print("Request file name is " + filename);
        }
        if(stat(filename.c_str(), &info) == 0) {
            sprintf(Data, "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: %ld\n\n", info.st_size);
            *Length = strlen(Data);
            tcp->Send(Socket, Data, strlen(Data));
            file.open(filename);  
            while (getline(file, Line)) {
                tcp->Send(Socket, (char*)Line.c_str(), Line.length());
            }
            file.close();

            *Length = 0;
            tcp->Close(Socket);
            return true;
        }
    }

    sprintf(Data, "HTTP/1.1 403 OK\nContent-Type:text/html\nContent-Length: 0\n\n");
    *Length = strlen(Data);
    tcp->Send(Socket, Data, strlen(Data));


    *Length = 0;
    tcp->Close(Socket);
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
