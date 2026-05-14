#include "GamePlay.h"
#include <filesystem>

bool constVar::isMute = false;
bool constVar::isHard = false;
int main() {
	initTerminal();
	GamePlay game;
	game.displayConsole();
	game.drawMenu();
	cleanupTerminal();
	return 0;
}
