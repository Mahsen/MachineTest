#ifndef __DEFINES_HPP
#define __DEFINES_HPP
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <experimental/filesystem>
#include <mutex>  
#include <queue>
#include <vector>  
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <future>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/unistd.h>
#include <netdb.h>
//----------------------------------------------------------
using namespace std;
//----------------------------------------------------------
void Print(string str);
std::vector<std::string> split(std::string s, std::string delimiter);
//----------------------------------------------------------
#endif