/*
*	-----------------------------------------------------------------
*	Modulo de acesso a rede, criacao de sockets e threads
*	Daniel V. Gomes daniel.vasconcelosgomes@gmail.com
*	http://danielvgomes.webs.com/
*       ------------------------------------------------------------------
*/
#ifndef _SERVER_
#define _SERVER_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <errno.h>

#include <sqlite3.h> 


#define PORT_USED 2000
#define BUFFER 256
#define SPACE_CHAR 0x20
#define MAXFRAMEMSG 33
#define MAXCLIENTS 30
#define TRUE	1

using namespace std;

/*--------------------------------------------------------------------------------------------
*		Sockets
*		Classe que cria um socket
---------------------------------------------------------------------------------------------*/
class SocketCom
{
public:
    SocketCom( int port );
    void ReadSocket( char* dest, int sze );
    void CloseServer();
    int SetSocketBack();
private:
    int getPort() const{ return this->port ;};
    void SafeBufferOperation(const char* orig);
    int doprocessing(int sock);    
    int WaitMsg( char* buffer );
    void error(const char *msg) const;
    void CloseClient();

    socklen_t clilen;  
    fd_set readfds;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_adrdr;
    pthread_mutex_t lock;
    int client_socket[MAXCLIENTS];
    char _b[ BUFFER ];
    int port;
    int opt;
    int max_sd;
    int sockfd;

};

#endif


