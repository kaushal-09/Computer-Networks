#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 8080
void main() {
int sock = socket(AF_INET, SOCK_STREAM, 0);
int option = 1;
struct sockaddr_in address;
socklen_t addrlen = sizeof(address);
char buffer[1024] = {0};
char source_file[] = "test.txt";
char fname[] = "test.txt";
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &option,
sizeof(option));if(bind(sock, (struct sockaddr*) &address, sizeof(address)) == -1){
perror("Could not bind to address");
return;
} if(listen(sock, 5) == -
1) {
perror("Error while listening to connections");
return;
} int new_socket =
accept(sock, (
struct sockaddr*) &
address, &
addrlen);
if(new_socket == -1){
perror("Error connecting to client");
exit(EXIT_FAILURE);
}else printf("Connected to client\n");// first send the filename
if(send(new_socket, fname, sizeof(fname), 0) == -1){
perror("Error while sending file");
return;
}
printf("Sending file %s\n\n", source_file);
FILE* f = fopen(source_file, "r");// send the contents of the file
while(fgets(buffer, sizeof(buffer), f)){
printf("Sending %s", buffer);
int sent = send(new_socket, buffer, strlen(buffer),0);
if (sent == -1)
perror("Error while sending\n");
else
printf("Successfully sent [%d bytes]\n\n", sent);
memset(buffer, 0, sizeof(buffer));
}
printf("File transfer complete\n");
fclose(f);
}
