#include "GamePlay.h"
#include <filesystem>
#include <cstring>
#include <cstdio>

bool constVar::isMute = false;
bool constVar::isHard = false;

int runCLI(int argc, char* argv[]) {
	int startX = 32, startY = 28;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--start") == 0 && i + 1 < argc) {
			sscanf(argv[i + 1], "%d,%d", &startX, &startY);
			i++;
		}
	}

	Player player(Pos(startX, startY));
	printf("start: %d,%d\n", player.getX(), player.getY());

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "--moveUp") == 0) {
			player.MoveUp();
			printf("moveUp: %d,%d\n", player.getX(), player.getY());
		} else if (strcmp(argv[i], "--moveDown") == 0) {
			player.MoveDown();
			printf("moveDown: %d,%d\n", player.getX(), player.getY());
		} else if (strcmp(argv[i], "--moveLeft") == 0) {
			player.MoveLeft();
			printf("moveLeft: %d,%d\n", player.getX(), player.getY());
		} else if (strcmp(argv[i], "--moveRight") == 0) {
			player.MoveRight();
			printf("moveRight: %d,%d\n", player.getX(), player.getY());
		}
	}

	return 0;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		return runCLI(argc, argv);
	}
	initTerminal();
	GamePlay game;
	game.displayConsole();
	game.drawMenu();
	cleanupTerminal();
	return 0;
}
