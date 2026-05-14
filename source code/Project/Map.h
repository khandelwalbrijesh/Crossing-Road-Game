#pragma once
#include <iostream>
#include "Player.h"
#include "Car.h"
#include "Bus.h"
#include "Enemy.h"
#include "Level.h"
#include "Road.h"
#include <fstream>
using namespace std;

#define Border_Vertical "\xe2\x96\x88"
#define Border_Down "\xe2\x96\x84"
#define Border_Up "\xe2\x96\x80"
#define Border_mid "\xe2\x96\xa0"
#define Square_Piece "\xe2\x96\xa0"

#define HORIZONTAL_PALE_PIECE "\xe2\x95\x90"
#define VERTICAL_PALE_PIECE "\xe2\x95\x91"
#define UP_LEFT_CORNER_PALE_PIECE "\xe2\x95\x94"
#define UP_RIGHT_CORNER_PALE_PIECE "\xe2\x95\x97"
#define DOWN_LEFT_CORNER_PALE_PIECE "\xe2\x95\x9a"
#define DOWN_RIGHT_CORNER_PALE_PIECE "\xe2\x95\x9d"

#define LOADING_BLOCK "\xe2\x96\x93"

#define Left_Map 3
#define Right_Map 58
#define Up_Map 3
#define Down_Map 32

class Map {
private:
	const int width = 113, height = 32;
	Player player;
	Road roadData;
	Level level;
	int t = 0;
	bool checkPause;
public:
	Map();
	~Map() = default;

	void drawMap();
	void checkMap();
	void deletePlayer();
	void drawPlayer();
	void UpdatePositionPlayer(char c);
	void initializeNewState();
	void randomNewState();
	int draw(Pos pos, char** shape, int w, int h);
	void isDead();
	void saveGame(string file);
	bool loadGame(string file);
	void WriteFileBin(int p, ofstream& fileout);
	int ReadFileBin(ifstream& filein);
	bool isWin();
	bool isEnd();
	void nextLevel();
	void printLoseGame();
	bool printLevelUp();
	void printCongrats();
	int getLevel();
};
