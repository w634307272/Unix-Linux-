//
// Created by lee on 2021/7/14.
//
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>

#define HOSTLEN 20
#define BACKLOG 1
#define PORTNUM 13000
#define oops(msg)  {perror(msg); exit(1);}


int make_server_socket_q(int, int);

int make_server_socket(int portnum){
    return make_server_socket_q(portnum, BACKLOG);
}

int make_server_socket_q(int portnum, int backlog){
    struct sockaddr_in saddr;
    struct hostent *hp;
    char hostname[HOSTLEN];
    int sock_id;

    sock_id = socket(PF_INET, SOCK_STREAM,0);
    if(sock_id == -1)
        return -1;
    bzero((void*)&saddr, sizeof(saddr));
    gethostname(hostname, HOSTLEN);
    hp = gethostbyname(hostname);

    bcopy((void *)hp -> h_addr, (void *)&saddr.sin_addr, hp -> h_length);
    saddr.sin_port = htons(portnum);
    saddr.sin_family = AF_INET;
    if(bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) != 0)
        return -1;
    if(listen(sock_id, backlog) != 0)
        return -1;
    return sock_id;
}

int connect_to_server(char *host, int portnum){
    int sock;
    struct sockaddr_in servadd;
    struct hostent *hp;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        return -1;
    bzero(&servadd, sizeof(servadd));
    hp = gethostbyname(host);
    if(hp == NULL)
        return -1;
    bcopy(hp -> h_addr, (struct sockaddr *)&servadd.sin_addr, hp->h_length);
    servadd.sin_port = htons(portnum);
    servadd.sin_family = AF_INET;

    if(connect(sock, (struct sockaddr *)&servadd, sizeof(servadd)) != 0)
        return -1;
    return sock;
}

void main(){
    int sock, fd;
    void child_waiter(int), process_request(int);
    signal(SIGCHLD, child_waiter);
    if((sock = make_server_socket(PORTNUM)))
        oops("make_server_socket");
    while(1){
        fd = accept(sock, NULL, NULL);
        if(fd == -1)
            break;
        process_request(fd);
        close(fd);
    }
}

void child_waiter(int signum){
    wait(NULL);
}

void process_request(int fd){
    if(fork() == 0){
        dup2(fd, 1);
        close(fd);
        execlp("data", "date", NULL);
        oops("execlp date");
    }
}