//
// Created by lee on 2021/5/17.
//
#include <stdio.h>
#include <curses.h>

void main(){
    int i;

    initscr();
    clear();
    for(i = 0; i < LINES; i++){
        move(i, i+i);
        if(i % 2 == 1)
            standout();
        addstr("Hello, world");
        if(i % 2 == 1)
            standend();
    }
    refresh();
    getch();
    endwin();
}

