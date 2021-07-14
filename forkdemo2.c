//
// Created by lee on 2021/5/28.
//
#include <stdio.h>
#include <unistd.h>

void main(){
    printf("my pid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("my pid is %d\n", getpid());
}
