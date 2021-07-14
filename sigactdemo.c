//
// Created by lee on 2021/5/28.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#define INPUTLEN 100

void main(){
    struct sigaction newhandler;
    sigset_t blocked;
    void inthandler();
    char x[INPUTLEN];

    newhandler.sa_handler = inthandler;

    newhandler.sa_flags = SA_RESETHAND;//函数调用时被重置

    sigemptyset(&blocked);
    sigaddset(&blocked, SIGQUIT);
    newhandler.sa_mask = blocked;

    if(sigaction(SIGINT, &newhandler, NULL) == -1)
        perror("sigaction");
    else
        while(1){
            fgets(x, INPUTLEN, stdin);
            printf("input : %s", x);
        }
}

void inthandler(int s){
    printf("Called with signal %d\n", s);
    sleep(s);
    printf("done handling signal %d\n", s);
}
