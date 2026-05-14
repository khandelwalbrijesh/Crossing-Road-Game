#include "Console.h"

#ifdef _WIN32

void gotoXY(int col, int row)
{
	COORD coord;
	coord.X = col;
	coord.Y = row;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void clrscr() {
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
void Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}
void txtColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color+(15*16));
}

void initTerminal() {}
void cleanupTerminal() {}

int readKey() {
	int c = _getch();
	if (c == 0 || c == 224) {
		c = _getch();
		switch (c) {
		case 72: return KEY_UP;
		case 80: return KEY_DOWN;
		case 75: return KEY_LEFT;
		case 77: return KEY_RIGHT;
		default: return c;
		}
	}
	return c;
}

bool keyPressed() {
	return _kbhit() != 0;
}

void portableSleep(int ms) {
	Sleep(ms);
}

void playSound(const char* file, bool loop) {
	if (!file) { PlaySound(NULL, NULL, SND_ASYNC); return; }
	DWORD flags = SND_FILENAME | SND_ASYNC;
	if (loop) flags |= SND_LOOP;
	PlaySoundA(file, NULL, flags);
}

void stopSound() {
	PlaySound(NULL, NULL, SND_ASYNC);
}

#else

static struct termios orig_termios;
static bool terminal_initialized = false;

static void signalHandler(int sig) {
	cleanupTerminal();
	signal(sig, SIG_DFL);
	raise(sig);
}

void initTerminal() {
	if (!isatty(STDIN_FILENO)) return;
	tcgetattr(STDIN_FILENO, &orig_termios);
	struct termios raw = orig_termios;
	raw.c_iflag &= ~(ICRNL | IXON);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
	setvbuf(stdout, NULL, _IONBF, 0);
	terminal_initialized = true;
	signal(SIGINT, signalHandler);
	signal(SIGTERM, signalHandler);
	atexit(cleanupTerminal);
}

void cleanupTerminal() {
	if (!terminal_initialized) return;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
	printf("\033[?25h");
	printf("\033[0m");
	printf("\033[2J\033[H");
	fflush(stdout);
	terminal_initialized = false;
}

void gotoXY(int col, int row) {
	printf("\033[%d;%dH", row + 1, col + 1);
}

void clrscr() {
	printf("\033[2J\033[H");
}

void txtColor(int color) {
	static const int fgMap[] = {
		30, 34, 32, 36, 31, 35, 33, 37,
		90, 94, 92, 96, 91, 95, 93, 97
	};
	if (color == 155) {
		printf("\033[96;100m");
	} else if (color == 15) {
		printf("\033[0m");
	} else if (color >= 0 && color < 16) {
		printf("\033[%dm", fgMap[color]);
	} else {
		printf("\033[0m");
	}
}

void Nocursortype() {
	printf("\033[?25l");
}

void FixConsoleWindow() {
}

bool keyPressed() {
	fd_set readfds;
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0;
}

int readKey() {
	unsigned char c;
	if (read(STDIN_FILENO, &c, 1) != 1) return -1;
	if (c == 27) {
		fd_set readfds;
		struct timeval tv;
		tv.tv_sec = 0;
		tv.tv_usec = 50000;
		FD_ZERO(&readfds);
		FD_SET(STDIN_FILENO, &readfds);
		if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) > 0) {
			unsigned char seq;
			if (read(STDIN_FILENO, &seq, 1) == 1 && seq == '[') {
				if (read(STDIN_FILENO, &seq, 1) == 1) {
					switch (seq) {
					case 'A': return KEY_UP;
					case 'B': return KEY_DOWN;
					case 'C': return KEY_RIGHT;
					case 'D': return KEY_LEFT;
					}
				}
			}
		}
		return KEY_ESC;
	}
	return c;
}

void portableSleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void playSound(const char* file, bool loop) {
	(void)file;
	(void)loop;
}

void stopSound() {
}

#endif
