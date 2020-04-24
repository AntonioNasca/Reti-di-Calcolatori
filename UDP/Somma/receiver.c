/* UDP Receiver */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char* argv[])
{ 
  int sockfd,sum=0,n;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  
   
  if(argc < 2)
  {  printf("Sto ascoltando dalla porta");
   return 0;
  }  
  
  if((sockfd=socket(PF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nErrore nell'apertura del socket ... exit!");
    return -1;
  }

 memset(&local_addr,0,sizeof(local_addr));
 memset(&remote_addr,0,sizeof(remote_addr));

 local_addr.sin_family = AF_INET;
 local_addr.sin_port = htons(atoi(argv[1]));
   

bind(sockfd, (struct sockaddr *) &local_addr, len);
  
  //Ricevo dati dal sender

    recvfrom(sockfd,&n,sizeof(int),0,(struct sockaddr *) &remote_addr,&len);
    printf("I numeri da sommare sono %d\n",n);

    int buffer[n];

    recvfrom(sockfd,&buffer,n*sizeof(int),0,(struct sockaddr *) &remote_addr,&len);

    //Somma

    for(int i=0;i<n;i++)
    sum+=buffer[i];

  //Invio la somma al server

    sendto(sockfd,&sum,sizeof(int),0,(struct sockaddr *)&remote_addr,sizeof(remote_addr));
    printf("Ho finito\n");
    
}