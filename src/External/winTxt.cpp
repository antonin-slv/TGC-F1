#include "winTxt.h"
#include <cassert>
#include <stdlib.h>
#include <stdarg.h>
#include <iostream>
#include <stdio.h>

#if _WIN32
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include <windows.h>
#include <conio.h>
#else
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#endif

void termMove(int x, int y) // deplace le curseur du terminal
{
#ifdef _WIN32
    // Deplace le curseur en haut a gauche du terminal
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD origine = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(console, origine);
#else
    char t[16];
    sprintf(t, "\033[%d;%dH", y, x);
    printf("%s",t);
#endif

}

void termClear()  // efface le terminal
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void termInit()      // configure la saisie : ne pas afficher les caracteres tapes
{
#ifdef _WIN32
    HANDLE console = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode; GetConsoleMode(console, &mode);
    SetConsoleMode(console, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
#else
    struct termios ttystate;
    bool state = true;

    //get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    if (state) {
        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
    }
    else {
        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
    }
    //set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif
}

WinTXT::WinTXT (int dx, int dy) {
    dimx = dx;
    dimy = dy;
    win = new char[dimx*dimy];
    clear();
    termInit();
}

void WinTXT::clear (char c) {
    for(int i=0;i<dimx;++i)
        for(int j=0;j<dimy;++j)
            print(i,j,c);
}

void WinTXT::print (int x, int y, char c) {
    if (x<0) return;
    if (y<0) return;
    if (x>=dimx) return;
    if (y>=dimy) return;
    win[y*dimx+x] = c;
}

void WinTXT::print (int x, int y, char* c) {
    int i=0;
    while (c[i]!='\0') {print(x+i,y,c[i]);++i;}
}

void WinTXT::draw (int x, int y) {
    termMove(0,0);
    for(int j=0;j<dimy;++j) {
        for(int i=0;i<dimx;++i)
            printf("%c",win[j*dimx+i]);
        printf("\n");
    }
    termMove(0,dimy);
}

#if not defined _WIN32
int kbhit() {
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}
#endif

void WinTXT::pause() {
#ifdef _WIN32
    system("pause");
#else
    printf("Appuyer sur une touche\n");
    while(!kbhit());
#endif
}

char WinTXT::getCh() { // lire un caractere si une touche a ete pressee
    char touche=0;
#ifdef _WIN32
    if (kbhit())
    {
        DWORD mode;
        DWORD n;
        HANDLE consoleI = GetStdHandle(STD_INPUT_HANDLE);
        GetConsoleMode(consoleI, &mode);
        SetConsoleMode(consoleI, mode & ~ENABLE_LINE_INPUT & ~ENABLE_ECHO_INPUT);
        ReadConsole(consoleI, &touche, 1, &n, NULL);
    }
#else
    if (kbhit())
        touche = fgetc(stdin);
#endif
    return touche;
}
