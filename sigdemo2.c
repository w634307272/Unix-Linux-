//
// Created by lee on 2021/5/17.
//
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void main(){
    signal(SIGINT, SIG_IGN);
    printf("you can not stop me! \n");
    while(1){
        sleep(1);
        printf("hahaha\n");
    }
}
