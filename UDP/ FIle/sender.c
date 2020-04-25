/* UDP Sender */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{ 
  int sockfd; 
  struct sockaddr_in remote_addr;
  char buffer[300], c[4]={"fine"};
  socklen_t len = sizeof(struct sockaddr_in);
  
  FILE *fp;
  fp = fopen("testo.txt", "r");

  
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

  //INVIO IL FILE DI TEST
    if (fp)
    {
        
        while (!feof(fp))
        { 
            //Invio ogni riga del file
            if (fgets(buffer, 300, fp) != NULL)
            sendto(sockfd,buffer,300, 0, (struct sockaddr *) &remote_addr, sizeof(remote_addr));   
             
             
            else
            {
                printf("errore!");
                break;
            }
          
        }
      
        fclose(fp);
         
    }
    sendto(sockfd,c,sizeof(c), 0, (struct sockaddr *) &remote_addr, sizeof(remote_addr)); 
    printf("Finito\n");
  
}
