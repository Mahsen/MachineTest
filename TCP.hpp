#ifndef __TCP_HPP
#define __TCP_HPP
//----------------------------------------------------------
#include "Defines.hpp"
#include "AdvancedTypes.hpp"
//----------------------------------------------------------
namespace net {
using namespace std;
#define TCP_SIZEOF_BUFFER                                  512
#define TCP_SIZEOF_LISTEN                                  4
//----------------------------------------------------------
class TCP {
	private:        
        int Socket;
        public : struct struct_Listen {
			public : struct struct_Status {
				int Error;
				string Messege;
			};
			std::queue<struct_Status> Status;
			struct struct_Server {
				int Socket;
				struct sockaddr_in Addr;
			} Server;
			struct struct_Client {
				int Socket;
				struct sockaddr_in Addr;
				char Buffer[TCP_SIZEOF_BUFFER];
			};			
			bool (*CallBack)(int Socket, char* Data, int* Length);
		};    
	public:	        						
		std::queue<struct_Listen::struct_Status> * AddListen(int Port, bool (*CallBack)(int Socket, char* Data, int* Length));	
		bool Send(int Socket, char* Data, int Length);
};
//----------------------------------------------------------
}
#endif
