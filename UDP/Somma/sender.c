/* UDP Sender */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ 
  int sockfd;
  struct sockaddr_in remote_addr;

  socklen_t len = sizeof(struct sockaddr_in);
  int n,sum;
  
  
  if(argc < 3)
  {  printf("Use: sender IP_dest PORT_dest");
   return 0;
  }  
  
  if((sockfd=socket(PF_INET,SOCK_DGRAM,0)) <0)
  { printf("\nError in socket opening ... exit!");
    return -1;
  }
  
  memset(&remote_addr,0,len);
  remote_addr.sin_family = AF_INET;
  inet_pton(AF_INET, argv[1], &(remote_addr.sin_addr)); 
  remote_addr.sin_port=htons(atoi(argv[2]));


      printf("Quanti numeri vuoi sommare?\n");
      scanf("%d",&n);
      int buffer[n];

    for(int i=0;i<n;i++)
    {
      printf("\nInserisci il numero:\n");
      scanf("%d",&buffer[i]);
    }

    sendto(sockfd,&n, sizeof(int), 0, (struct sockaddr *) &remote_addr, sizeof(remote_addr));
    sendto(sockfd,buffer, n*sizeof(int), 0, (struct sockaddr *) &remote_addr, sizeof(remote_addr));
    
    //Ricevere
    recvfrom(sockfd,&sum,sizeof(int),0, (struct sockaddr *) &remote_addr, &len);
    printf("La somma=%d\n",sum);
    
}