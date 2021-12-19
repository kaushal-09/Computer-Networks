#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080
int main() {
int sock = socket(AF_INET, SOCK_STREAM, 0);
long val;
struct sockaddr_in address;
char buffer[1024] = {0};
address.sin_family = AF_INET;
address.sin_port = htons(PORT);
if(inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) == -1){
perror("Invalid IP value");
exit(EXIT_FAILURE);
} if(connect(sock,(struct sockaddr*) &
address, sizeof(address)) == -
1){perror("Connection Error");
exit(EXIT_FAILURE);
}else printf("Connected to server\n");
// Get file name from server
if(read(sock, buffer, sizeof(buffer)) == -1){
perror("Could not read filename from server");
exit(EXIT_FAILURE);
}printf("Receiving file %s\n", buffer);
FILE *f =fopen(buffer, "w");
// printf("%ld", read(sock, buffer, sizeof(buffer)));
while((val = read(sock, buffer, sizeof(buffer)))){
if (val == -1) {perror("Error reading the content");
break;
}
printf("Received %s", buffer);
for(int i = 0; i < val; i++)
fputc(buffer[i], f);
fputc('\0', f);
memset(buffer, 0, sizeof(buffer));
}
if (val == 0)
printf("File transfer complete\n");
else
printf("Incomplete Transfer\n");
fclose(f);
}
