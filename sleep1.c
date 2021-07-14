//
// Created by lee on 2021/5/21.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void main(){
    void wakeup(int);

    printf("about to sleep for 4 seconds\n");
    signal(SIGALRM, wakeup);
    alarm(4);
    pause();
    printf("Morning so soon？\n");
}

void wakeup(int signum){
#ifndef SHHHH
    printf("Alarm received from kernel\n");
#endif
}

