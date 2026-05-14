#pragma once
#include <iostream>
#include <time.h>
#include <algorithm>

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")
#else
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <chrono>
#include <thread>
#include <csignal>
#include <cstdio>
#endif

#define ColorCode_Back			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define default_ColorCode		7

#define KEY_UP    300
#define KEY_DOWN  301
#define KEY_LEFT  302
#define KEY_RIGHT 303
#define KEY_ESC   27
#define KEY_ENTER 13

void clrscr();
void gotoXY(int column, int line);
void txtColor(int color);
void FixConsoleWindow();
void Nocursortype();

void initTerminal();
void cleanupTerminal();
int readKey();
bool keyPressed();
void portableSleep(int ms);
void playSound(const char* file, bool loop = false);
void stopSound();

class constVar {
public:
	static bool isMute;
	static bool isHard;
};
