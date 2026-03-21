#include <sys/socket.h>
#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        perror("socket");
        return 1;
    }
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    struct sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = INADDR_ANY;
    int v = bind(fd, (sockaddr*) &addr, sizeof(addr));
    if(v < 0){
        perror("bind");
        return 1;
    }
    int l = listen(fd,SOMAXCONN);
    if(l < 0){
        perror("listen");
        return 1;
    }
    while(true){
        sockaddr_in client {};
        socklen_t len = sizeof(client);
        int connfd = accept(fd, (sockaddr*) &client, &len);
        if(connfd < 0){
            continue;
        }
        close(connfd);
    }
}