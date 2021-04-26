#include<iostream>
#include<string>
#include "server_tcp.cpp"
#include "client_tcp.cpp"

int main(){

    std::cout<<"Enter s/c";
    std::string s;
    std::cin>>s;
    if(s=="s"){
        int sock = PrepareServer();
        char * x = "hello";
        int r = SendtoClient(sock, x, 5);
        if(r!=-1){
            std::cout<<"Sent";
        }
        else{
            std::cout<<"Failed";
        }
    }
    else{
        int sock = PrepareClient();
        std::string r = ClientListen(sock);
        std::cout<<r;
    }

    return 0;
}