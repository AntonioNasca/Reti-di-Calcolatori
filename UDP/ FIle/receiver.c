/* UDP Receiver */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char* argv[])
{ 
  int sockfd;
  struct sockaddr_in local_addr, remote_addr;
  socklen_t len = sizeof(struct sockaddr_in);
  char buffer[300];
  FILE *fp;
  fp=fopen("testo.txt","a");
  
   
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
  
    

    printf("Aspetto il messaggio:\n");
    
    //fprintf(fp,"%d\n",end);
   
    for(;;)
    { 
        recvfrom(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr *) &remote_addr,&len);
        printf("%s",buffer); 
       
    }
    
    
    
}
