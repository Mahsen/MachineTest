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
    Last Update : 2024/11/26
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
#define MAIN_UI_PAGE_LOGIN                               "/login.html"
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
bool UI_CallBack (int Socket, char* Data, int* Length) {

    string Line = "";
    ifstream file;
    struct stat info;
    string filename = string(Local_Path) + MAIN_UI_ROOT + string(MAIN_UI_PAGE_DEFAULT);

    //Print(Data);

    if(strstr(Data, "GET /")) {
        vector<string> ParameterGET = split(string(Data), " ");
        
        if(ParameterGET[1].size() > 1) {
            filename = string(Local_Path) + MAIN_UI_ROOT + ParameterGET[1];
            Print("Request file name is " + filename);
        }        
        if(stat(filename.c_str(), &info) == 0) {
            Print("success load file name is " + filename);
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
        Print("faild load file name is " + filename);
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

    if (getcwd(Local_Path, sizeof(Local_Path)) != NULL) {
        Print("Current working dir : " + string(Local_Path));
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
                Print("Change Current working dir: " + string(Local_Path));
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
