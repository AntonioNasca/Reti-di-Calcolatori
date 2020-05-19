#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>  //contiene la definizione di sockaddr_in

#define BUF_SIZE 512

int main(int argc, char *argv[])
{
    int str_length, sockfd,quantita;
    char stringa[BUF_SIZE];

    struct sockaddr_in server;
    
    if(argc != 3)
    {
    	fprintf(stderr, "uso: %s <indirizzo_IP> <numero_di_porta>\n", argv[0]);
    	exit(1);
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
    	printf("errore nell'apertura della socket... esco!\n");
    	exit(1);
    }

    memset(&server, 0, sizeof(server));
    memset(stringa, 0, BUF_SIZE);
    server.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(server.sin_addr));
    server.sin_port = htons(atoi(argv[2]));

    connect(sockfd, (struct sockaddr *) &server, sizeof(server));
     
   // printf("inserisci la stringa da invertire: ");
    //scanf("%s", stringa);

    str_length = strlen(stringa);

    
    printf("Beninissimo cominciamo a digitare numeri\n");

   
    printf("Inserisci la sequenza dei numeri da inviare %s:");
    scanf("%s",stringa); 

    printf("Sto mandando la stringa: %s\n",stringa);
   
    str_length =strlen(stringa);
    
    send(sockfd,stringa, quantita, 0);
    int n = recv(sockfd, stringa, str_length, 0);
    
    if(n == 0)
    {
		  printf("Nessuna somma indietro\n");
		  return 0;
    }

    stringa[n] = 0;
    
    
    printf("La somma e' %s\n",stringa);

    return 0;
}
