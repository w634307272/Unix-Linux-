//
// Created by lee on 2021/5/17.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void main(){
    void f(int);
    int i;
    signal (SIGINT, f);
    for(i = 0; i < 5; i++){
        printf("hello\n");
        sleep(1);
    }
}
void f(int signum){
    printf("OUCH! \n");
}
