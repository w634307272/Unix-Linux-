//
// Created by lee on 2021/6/20.
//
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXARGS 20
#define ARGLEN 100

int main(){
    char *arglist[MAXARGS + 1];
    int numargs;
    char argbuf[ARGLEN];
    char *makestring;
    void execute(char *arglist[]);

    numargs = 0;
    while(numargs < MAXARGS){
        printf("Arg[%d]?", numargs);
        if(fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs ++] = makestring(argbuf);
        else{
            if(numargs > 0){
                arglist[numargs] = NULL;
                execute(arglist);
                numargs = 0;
            }
        }
    }
    return 0;
}

void execute(char *arglist[]){
    int pid, exitstatus;

    pid = fork();
    switch (pid) {
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            execvp(arglist[0], arglist);
            perror("execvp failed");
            exit(1);
        default:
            while(wait(&exitstatus) != pid)
                ;
            printf("child exited with status %d, %d\n", exitstatus>>0, exitstatus&0377);
    }
}

char *makestring(char *buf){
    char *cp, *malloc();

    buf[strlen(buf) - 1] = '\0';
    cp = malloc(strlen(buf) + 1);
    if(cp == NULL){
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp, buf);
    return cp;
}

