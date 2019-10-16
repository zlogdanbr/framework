
/*
*	-----------------------------------------------------------------
*	Implementacao do modulo de acesso a rede, criacao de sockets e threads
*
*	Daniel V. Gomes daniel.vasconcelosgomes@gmail.com
*	http://danielvgomes.webs.com/
*       ------------------------------------------------------------------
*/

#include "../include/com.h"
#include "../include/log.h"
#include "../include/db.h"

extern LogData& log;

// Construtor do servidor
SocketCom::SocketCom( int port )
{
    sockfd = 0;
    //newsockfd = 0;
    this->port = port;
    memset( _b, 0x00, sizeof( _b ));

    // Inicializa vetor para sockets clientes
    for (int i = 0; i < MAXCLIENTS; i++)
    {
        client_socket[i] = 0;
    }

    opt = TRUE;

    max_sd = 0;

    log.StartLoging();
}

// Fecha o socket do servidor
void SocketCom::CloseServer()
{
     log.StopLoging();
     close(sockfd);
}


// Operacao de leitura de dados na porta 2000
// e posterior atualizacao no banco
void SocketCom::SafeBufferOperation(const char* orig)
{
    	pthread_mutex_init(&lock, NULL);
    	pthread_mutex_lock(&lock);

    	pthread_mutex_unlock(&lock);
    	pthread_mutex_destroy(&lock);
}

// Erro de comunicacao
void SocketCom::error(const char *msg) const
{
    perror(msg);
    exit(1);
}

void SocketCom::CloseClient()
{
     //close(newsockfd);
}

// Leitura do socket
void SocketCom::ReadSocket( char* dest, int sze )
{
     log.LogMsg("Inicio do servico. \n");
     char buffer[ BUFFER ];
     memset( buffer, 0x00, sizeof( buffer ));
     WaitMsg( buffer );// aguarda conectar
}


// Configura o socket
int SocketCom::SetSocketBack()
{
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0)
     {
#ifdef _DEBUG
        error("Erro ao tentar abrir socket...");
#endif
	log.LogMsg("Erro ao tentar abrir socket. \n");
        return -1;
     }

     bzero((char *) &serv_addr, sizeof(serv_addr));

     //set master socket to allow multiple connections , this is just a good habit, it will work without this
     if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
     {
	 log.LogMsg("Erro criar socket mestre \n");
	 return -1;
     }

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(this->port);

     if (bind(sockfd, (struct sockaddr *) &serv_addr,  sizeof(serv_addr)) < 0)
     {
#ifdef _DEBUG
        error("Erro ao tentar fazer bind...");
#endif
        log.LogMsg("Erro ao fazer bind \n");
        return -1;
     }

     return 0;
}


// Server propriamente dito
int SocketCom::WaitMsg( char* buffer )
{
	    int sd = 0;
            int new_socket  = 0;

	    int activity = 0;

	    listen(sockfd,5);
            log.LogMsg("Aguardando...\n");
	    clilen = sizeof(cli_adrdr);

	    while(TRUE)
	    {
		//clear the socket set
		FD_ZERO(&readfds);

		//add master socket to set
		FD_SET(sockfd, &readfds);
		max_sd = sockfd;

		//add child sockets to set
		for ( int i = 0 ; i < MAXCLIENTS ; i++)
		{
		    //socket descriptor
		    sd = client_socket[i];

		    //if valid socket descriptor then add to read list
		    if(sd > 0)
		        FD_SET( sd , &readfds);

		    //highest file descriptor number, need it for the select function
		    if(sd > max_sd)
		        max_sd = sd;
		}

		//wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
		activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

		if ((activity < 0) && (errno!=EINTR))
		{
		    log.LogMsg("Erro no select \n");
		}

		//If something happened on the master socket , then its an incoming connection
		if (FD_ISSET(sockfd, &readfds))
		{
		    new_socket = accept( sockfd, (struct sockaddr *) &serv_addr, &clilen );

		    if ( new_socket < 0 )
		    {
			log.LogMsg("Erro no accept \n");
			return -1;
		    }

		    //add new socket to array of sockets
		    for (int i = 0; i < MAXCLIENTS; i++)
		    {
		        //if position is empty
		        if( client_socket[i] == 0 )
		        {
		            client_socket[i] = new_socket;
		            log.LogMsg("Msg Lida \n");;
		            break;
		        }
		    }
		}

		//else its some IO operation on some other socket :)
		for (int i = 0; i < MAXCLIENTS; i++)
		{
		    sd = client_socket[i];

		    if (FD_ISSET( sd , &readfds))
		    {
		        //Check if it was for closing , and also read the incoming message
		        if ( doprocessing( sd ) == 0)
		        {

		            //Close the socket and mark as 0 in list for reuse
		            close( sd );
		            client_socket[i] = 0;
		        }

		    }
		}
	    }

            return 0;

}

// Processa o stream de dados vindos da rede na porta 2000
int SocketCom::doprocessing(int sock )
{
    int n;
    char buffer[BUFFER];

    bzero(buffer,BUFFER);

    n = read(sock,buffer,255);

    if ( n == 0 )
    {
        return -1;
    }

    SafeBufferOperation( buffer );

    if (n < 0)
    {
#ifdef _DEBUG
        perror("Erro ao tentar ler o socket");
#endif
	log.LogMsg("Erro ao tentar ler cliente \n");
        return -1;
    }

    n = write(sock,"[ ACK ENVIO OK ] \n",18);

    if (n < 0)
    {
#ifdef _DEBUG
        perror("Erro ao enviar resposta ao cliente...");
#endif
        log.LogMsg("Erro ao enviar ACK\n");
        return -1;
    }

    return 0;

}







