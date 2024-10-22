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
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
void Print(string str) {
    /* Lock untile return of block */
    std::lock_guard<std::mutex> guard(Mutex_print);
    /* Show on console */
    std::cout << str << endl;
}
/*--------------------------------------------------------------------------------------------------------------------*/
bool CallBack (int Socket, char* Data, int* Length) {
    Print(Data);
    //sprintf(Data, "I see\r\n");

    int Page_Length;

    ifstream file("index.html");
    string Line = "";
    char Page_Data[10240];
    memset(Page_Data, 0, sizeof(Page_Data));
    while (getline(file, Line)) {
        strcat(Page_Data, Line.c_str());
        Page_Length += Line.length();
    }
    sprintf(Data, "HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: %d\n\n", Page_Length);
    *Length = strlen(Data);
    strcpy(&Data[*Length], Page_Data);
    *Length += Page_Length;
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
                TCP *tcp = new TCP();
                std::queue<TCP::struct_Listen::struct_Status> * Status = tcp->AddListen(Port, CallBack);
                if(Status) {
                    while (true) {
                        if(!Status->empty()) {
                            Print("Messege : [" + Status->front().Messege + "] Error : [" + to_string(Status->front().Error) + "]");  
                            Status->pop();
                        }                        
                    }
                }
                else {
                    Print("ERROR: AddListen");
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
