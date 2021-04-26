// Client side C/C++ program to demonstrate Socket programming
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <iostream>



#define PORT 8080
   
// int main(int argc, char *argv[])
// {
//     int sock = 0, valread;
//     struct sockaddr_in serv_addr;
//     std::string hello = "Hello from client";
//     char buffer[1024] = {0};
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         printf("\n Socket creation error \n");
//         return -1;
//     }
   
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT);
       
//     // Convert IPv4 and IPv6 addresses from text to binary form
//     if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
//     {
//         printf("\nInvalid address/ Address not supported \n");
//         return -1;
//     }
   
//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//     {
//         printf("\nConnection Failed \n");
//         return -1;
//     }
//     // int isExit = 0;
//     // do {
//     //         recv(sock, buffer, strlen(buffer), 0);
//     //         printf("%s ",buffer);
//     //         if (*buffer == '#') {
//     //             *buffer = '*';
//     //             isExit = 1;
//     //         }
//     //     } while (*buffer != '*');

//         // do {
//         //     printf("\nServer: ");
//         //     do {
//         //         scanf("%s",&buffer[0]);
//         //         send(sock, buffer, strlen(buffer), 0);
//         //         if (*buffer == '#') {
//         //             send(sock, buffer, strlen(buffer), 0);
//         //             *buffer = '*';
//         //             isExit = 1;
//         //         }
//         //     } while (*buffer != '*');

//         //     printf("Client: ");
//         //     do {
//         //         recv(sock, buffer, strlen(buffer), 0);
//         //         printf("%s ",buffer);
//         //         if (*buffer == '#') {
//         //             *buffer == '*';
//         //             isExit = 1;
//         //         }
//         //     } while (*buffer != '*');
//         // } while (!isExit);
//     send(sock , hello , (hello).size() , 0 );
//     printf("Hello message sent\n");
//     valread = read( sock , buffer, 1024);
//     printf("%s\n",buffer );
//     return 0;
// }

int PrepareClient(){
    
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    //std::string hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    return sock;
}

int SendToServer(int sock, char * hello, int length){
    return send(sock , hello , length , 0 );
}

std::string ClientListen(int sock){
    char buffer[1024]={0};
    char errorbuffer[1024] = {0};
    int valread = read( sock , buffer, 1024);
    if(valread == -1){
        return errorbuffer;
    }
    return buffer;
}