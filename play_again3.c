//
// Created by lee on 2021/5/17.
//
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define ASK "Do you want another transaction"
#define TRIES 3
#define SLEEPTIME 3
#define BEEP putchar('\a')

int get_response(char *question, int maxtries);
char get_ok_char();
void set_cr_noecho_mode();
void set_nodelay_mode();
void tty_mode(int how);

int main(){
    int response;
    tty_mode(0);
    set_cr_noecho_mode();
    set_nodelay_mode();
    response = get_response(ASK, TRIES);
    tty_mode(1);
    return response;
}

int get_response(char *question, int maxtries){
    int input;
    printf("%s (y/n)", question);
    fflush(stdout);
    while(1){
        sleep(SLEEPTIME);
        input = tolower(get_ok_char());
        if(input == 'y')
            return 0;
        if(input == 'n')
            return 0;
        if(maxtries-- == 0)
            return 2;
        BEEP;
    }
}
char get_ok_char(){
    int c;
    while((c = getchar()) != EOF && strchr("yYnN", c) == NULL)
        ;
    return c;
}
void set_cr_noecho_mode(){
    struct termios ttystate;
    tcgetattr(0, &ttystate);
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &ttystate);
}

void set_nodelay_mode(){
    int termflags;
    termflags = fcntl(0, F_GETFL); //F_GETFL 取得文件描述词状态旗标，此旗标为open（）的参数
    termflags |= O_NDELAY;
}

void tty_mode(int how){
    static struct termios original_mode;
    static int oringial_flags;
    if(how == 0){
        tcgetattr(0, &original_mode);
        oringial_flags = fcntl(0, F_GETFL);
    }
    else{
        tcsetattr(0, TCSANOW, &original_mode);
        fcntl(0, F_SETFL, oringial_flags);
    }
}
