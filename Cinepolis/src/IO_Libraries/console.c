
#include "console.h"
#include <stdio.h>
#include <windows.h>

static void SetConsoleColor(WORD color);


//CONSOLE WINDOW

int GetConsoleWindowSize(int* width, int* height){
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return 0;
}


void SetConsoleWindowSize(int width, int height)
{
    COORD coord;
    coord.X = width;
    coord.Y = 500;

    SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = height - 1;
    rect.Right = width - 1;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(hConsole, coord);            // Set Buffer Size
    SetConsoleWindowInfo(hConsole, TRUE, &rect);            // Set Window Size
}



//CONSOLE COLORS

static void SetConsoleColor(WORD color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void SetConsoleStandardColor(void){
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void SetConsoleMenuTitleColor(void){
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void SetConsoleEnterOptionColor(void){
	SetConsoleColor(FOREGROUND_GREEN);
}

void SetConsoleErrorColor(void){
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED);
}

void SetConsoleLogoColor(void){
	SetConsoleColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}

void SetConsoleWhite(void){
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);
}


void printConsoleColorSampler(void){
	SetConsoleColor(0);
	printf("BLACK\n");
	SetConsoleColor(FOREGROUND_BLUE);
	printf("DARKBLUE\n");
	SetConsoleColor(FOREGROUND_GREEN);
	printf("DARKGREEN\n");
	SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("DARKCYAN\n");
	SetConsoleColor(FOREGROUND_RED);
	printf("DARKRED\n");
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE);
	printf("DARKMAGENTA\n");
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
	printf("DARKYELLOW\n");
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("DARKGRAY\n");
	SetConsoleColor(FOREGROUND_INTENSITY);
	printf("GRAY\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	printf("BLUE\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	printf("GREEN\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("CYAN\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	printf("RED\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	printf("MAGENTA\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	printf("YELLOW\n");
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("WHITE\n");
}


void SetTakenSeatColor(void){
	SetConsoleRedColor();
}

void SetFreeSeatColor(void){
	SetConsoleGreenColor();
}

void SetReservedSeatColor(void){
	SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN);
}

void SetConsoleRedColor(void){
	SetConsoleErrorColor();
}

void SetConsoleGreenColor(void){
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}

void SetConsoleYellowColor(void){
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
}

void SetConsoleColor_DarkCyan(void){
	SetConsoleColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

