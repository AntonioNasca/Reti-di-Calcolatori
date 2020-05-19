#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 512

void somma(char *stringa)
{
   int sum=0;

   //Sommo da string a int--> Codice ASCII-'0'->>INT
   for(int i=0;i<strlen(stringa);i++)
   sum+=stringa[i]-'0';

   printf("La somma e':%d\n",sum);

   //Pulisco
   for(int i=0;i<strlen(stringa);i++)
   stringa[i]=' ';
   
   //Converto da int a char 
   sprintf(stringa,"%d",sum);
   
}


int main(int argc, char *argv[])
{
    char buffer[BUF_SIZE];
    int fd, newfd;
    struct sockaddr_in local, client;
    socklen_t len;
    int n_letti;


    if(argc != 2)
    {
		  fprintf(stderr, "uso: %s <porta d'ascolto>\n", argv[0]);
		  exit(1);
    }

    if((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
		  fprintf(stderr, "errore nell'apertura della socket\n");
		  exit(1);
    }

    memset(buffer, 0, BUF_SIZE);
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_port = htons(atoi(argv[1]));

    if((bind(fd, (struct sockaddr *) &local, sizeof(local))) < 0)
    {
		  fprintf(stderr, "errore nel binding\n");
		  exit(1);
    }
    
    listen(fd, 6);

    while(1)
    {
        len = sizeof(client);
		    newfd = accept(fd, (struct sockaddr *) &client, &len);

        int pid = fork();
	    
      	if(pid == -1)
		    {
			    close(newfd);
		    	continue;
		    }	

		    //figlio, si occupa della singola connessione
        if(pid == 0)
        {
			    close(fd);

			    n_letti = recv(newfd, buffer, BUF_SIZE-1, 0);

			    if(n_letti == 0) 
			    return 0;       
                 	
			    buffer[n_letti] = 0;
			    printf("ho ricevuto la stringa %s da %s:%d\n", buffer, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
						
	        somma(buffer);
	        printf("sto inviando al client la stringa %s\n\n", buffer);
	        send(newfd, buffer, strlen(buffer), 0);
			    break;
		    }

        //padre, si occupa di accettare le richieste di connessione 
        else
            close(newfd);
    }
    
    return 0;
}
