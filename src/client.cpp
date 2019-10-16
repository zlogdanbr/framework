/*
*	-----------------------------------------------------------------
*	Implementacao do  client de envio de dados
*	
*	Daniel V. Gomes daniel.vasconcelosgomes@gmail.com
*	http://danielvgomes.webs.com/
*       ------------------------------------------------------------------
*       ssssiiiipppppppddmmyyyyhhmmsshhmm ... ssssiiiipppppppddmmyyyyhhmmsshhmm
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <string>
#include <iostream>

using namespace std;

void error(const char *msg);
int SendData( int sockfd, char* Frame );
int HelpFilePrint( int& args, const char* host );
int ConnectToserver( int portno, char* Host );
void Disconnect( int sockfd );

int HelpFilePrint( int& argc, const char* host )
{
    if (argc < 4 ) 
    {
       fprintf(stderr, "Por favor usar o formato: %s hostname port ssssiiiipppppppddmmyyyyhhmmsshhmm ] \n", host);
       fprintf(stderr, "Voce pode tambem enviar varias mensagens em seguida separando por espaco:\n");
       fprintf(stderr, "ssssiiiipppppppddmmyyyyhhmmsshhmm ssssiiiipppppppddmmyyyyhhmmsshhmm");
       fprintf(stderr, "... ssssiiiipppppppddmmyyyyhhmmsshhmm \n");
       return -1;
    }
    
    return 0;
}

void VerificaPlacaVazia(char* placa )
{
	if ( memcmp( placa+8, "XXXXXXX", 7) == 0 )
	{
		char vazio[] = "       ";
		memcpy( placa+8, vazio, 7 );
	}
}

int main(int argc, char *argv[])
{
    int portno;

    if ( HelpFilePrint( argc, argv[0] ) < 0 ) 
    {
       exit(0);
    }

    portno = atoi(argv[2]);

    for( int i = 3 ; i < argc ; i++ )
    {
            int socketid = ConnectToserver( portno, argv[1] );
	    VerificaPlacaVazia( argv[i] );
	    printf( "%s\n", argv[i] );
	    SendData( socketid, argv[i] );
            Disconnect(socketid);
    }

    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int ConnectToserver( int portno, char* Host )
{
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    server = gethostbyname(Host);

    if (server == NULL) 
    {
        fprintf(stderr,"ERROR, no such host\n");
        return -1;
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy(	(char *)server->h_addr,
         	(char *)&serv_addr.sin_addr.s_addr,
         	server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    return sockfd;
}


int SendData( int sockfd, char* Frame )
{

    if ( Frame == NULL )
	return -1;
    
    char buffer[ 256 ];

    memset( buffer, 0x00, sizeof( buffer ));
    strncpy( buffer , Frame, strlen(Frame) );

    int n = write(sockfd,buffer,strlen(buffer));
    if (n < 0)
         error("ERROR writing to socket");

    bzero(buffer,256);

    n = read(sockfd,buffer,255);
    if (n < 0)
         error("ERROR reading from socket");
    printf("%s\n",buffer);

    return 1;


}

void Disconnect(int sockfd)
{
    close(sockfd);
}


