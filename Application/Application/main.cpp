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
    Last Update : 2024/12/14
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
#define MAIN_UI_ROOT                                     "/../UI"
#define MAIN_UI_PAGE_DEFAULT                             "/index.html"
#define MAIN_UI_PAGE_LOGIN                               "/login.html"
#define MAIN_UI_PAGE_RUNABLE                             ".dll"
/************************************************** Names *************************************************************/
using namespace std;
using namespace net;
/************************************************** Variables *********************************************************/
char Local_Path[128];
union IPv4
{
    in_addr_t s_addr;
    struct {
        unsigned char b[4];
    } _U8;
};
union IPv4 Local_IP;
std::mutex Mutex_UI_CallBack;
/************************************************** Opjects ***********************************************************/
TCP *tcp;
/************************************************** Functions *********************************************************/
bool getMyIP(IPv4 *myIP) {
    char szBuffer[1024];

    if(gethostname(szBuffer, sizeof(szBuffer)) == -1) {
      return false;
    }

    struct hostent *host = gethostbyname(szBuffer);
    if(host == NULL) {
      return false;
    }

    //Obtain the computer's IP
    myIP->s_addr = ((struct in_addr *)(host->h_addr))->s_addr;

    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool Core_CallBack (int Socket, char* Data, int* Length) {
    Print(Data);

    tcp->Close(Socket);
    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
string GetContentType(string filename) {
    if(filename.substr(filename.find_last_of(".") + 1) == "html") {
        return "text/html";
    }
    else if(filename.substr(filename.find_last_of(".") + 1) == "css") {
        return "text/css";
    }
    else if(filename.substr(filename.find_last_of(".") + 1) == "js") {
        return "text/javascript";
    }
    else if(filename.substr(filename.find_last_of(".") + 1) == "ico") {
        return "image/x-icon";
    }
    else if(filename.substr(filename.find_last_of(".") + 1) == "jpeg") {
        return "image/jpeg";
    }
    else if(filename.substr(filename.find_last_of(".") + 1) == "png") {
        return "image/png";
    }
    else {
        return "text/plain";
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool UI_CallBack (int Socket, char* Data, int* Length) {

    /* Lock untile return of block */
    std::lock_guard<std::mutex> guard(Mutex_UI_CallBack);

    string Line = "";
    ifstream file;
    struct stat info;
    string filename = string(Local_Path) + MAIN_UI_ROOT + string(MAIN_UI_PAGE_DEFAULT);

    //Print(Data);
    Print("\r\n---------------------------------------------------\r\n");

    if(strstr(Data, "GET /")) {
        vector<string> ParameterGET = split(string(Data), " ");
        if(strstr(ParameterGET[1].c_str() , MAIN_UI_PAGE_RUNABLE) > 0) {            
            ParameterGET = split(ParameterGET[1], "?");
            Print("Proccess Run " + ParameterGET[0]);
            Print("Parameter" + ParameterGET[1]);
            Print("Proccess End ");
            
            sprintf(Data, "HTTP/1.1 200 OK\nContent-Type:application/json\nContent-Length: %ld\n\n", ParameterGET[1].length());
            tcp->Send(Socket, Data, strlen(Data));
            tcp->Send(Socket, (char*)ParameterGET[1].c_str(), strlen(ParameterGET[1].c_str()));
            
            *Length = 0;
            return true;
        }
        else {
            if(ParameterGET[1].size() > 1) {
                filename = string(Local_Path) + MAIN_UI_ROOT + ParameterGET[1];
                Print("Request File " + filename);
            }        
            if(stat(filename.c_str(), &info) == 0) {
                Print("Open File " + filename);
                sprintf(Data, "HTTP/1.1 200 OK\nContent-Type:%s\nContent-Length: %ld\n\n", GetContentType(filename).c_str(), info.st_size);
                //Print("Header File " + string(Data));
                Print("Write Socket " + to_string(Socket));
                tcp->Send(Socket, Data, strlen(Data));
                file.open(filename);  
                while (getline(file, Line)) {
                    tcp->Send(Socket, (char*)Line.c_str(), Line.length());
                    tcp->Send(Socket, (char*)"\n", 1);
                }
                file.close();
                Print("Close File " + filename);
                *Length = 0;
                //tcp->Close(Socket);
                //Print("Close Socket " + to_string(Socket));            
                return true;
            }
        }
        Print("Faild File " + filename);
        sprintf(Data, "HTTP/1.1 403 OK\nContent-Type:text/html\nContent-Length: 0\n\n");
        *Length = strlen(Data);
        tcp->Send(Socket, Data, strlen(Data));
    }
    /*else if(strstr(Data, "POST /")) {
        Print(Data);
        *Length = 113;
        if(tcp->Receive(Socket, Data, Length)) {
            Print(Data);
        }
        
    }*/
    else {
        Print("Request not access");
    }

    *Length = 0;
    //usleep(100000);    
    tcp->Close(Socket);
    Print("Close Socket " + to_string(Socket));
    return true;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char **argv) {
    /* Sample */
    // sudo ./main -p 1020
    /* Check arguments */

    if (getcwd(Local_Path, sizeof(Local_Path)) != NULL) {
        Print("Direction " + string(Local_Path));
    } else {
    Print("ERROR: getcwd() error");
        return 0;
    }


    if (getMyIP(&Local_IP)) {
        char str[32];
        sprintf(str, "%d.%d.%d.%d", Local_IP._U8.b[0], Local_IP._U8.b[1], Local_IP._U8.b[2], Local_IP._U8.b[3]);
        Print("Local IP : " + string(str));
    } else {
        Print("ERROR: gethostname() error");
    }

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
            else if(strcmp(argv[Index], "-s")==0) {
                strcpy(Local_Path, argv[Index+1]);
                Print("Change Direction " + string(Local_Path));
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
