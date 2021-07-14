//
// Created by lee on 2021/5/16.
//
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
void main(){
    struct termios info;
    int rv;

    rv = tcgetattr(0, &info);
    if(rv == -1){
        perror("tcgetattr");
        exit(1);
    }
    if(info.c_lflag & ECHO)
        printf("echo is on, since its bit is 1\n");
    else
        printf("echo is off, since its bit is 0\n");

}
