//
// Created by lee on 2021/5/16.
//
#include <stdio.h>
#include <termios.h>
#include <stdlib.h>

//#define oops(s, x){perror(s); exit(x);}

void oops(char *s, int x);

void main(int argc, char **argv){
    struct termios info;
    if (argc == 1)
        exit(0);
    if(tcgetattr(0, &info) == -1)
        oops("tcgettattr", 1);
    if(argv[1][0] == 'y')
        info.c_lflag |= ECHO;
    else
        info.c_lflag &= ~ECHO;

    if(tcsetattr(0, TCSANOW, &info) == -1)
        oops("tcsetattr", 2);
}

void oops(char *s, int x){
    perror(s);
    exit(x);
}

