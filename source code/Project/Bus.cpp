#include "Bus.h"
#include "Map.h"
Bus::Bus()
{
	s = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		s[i] = new char[8];
	}

	s[0][0] = '+';
	for (int i = 1; i < 7; i++)
		s[0][i] = '-';
	s[0][7] = '+';

	s[1][0] = '|';
	for (int i = 1; i < 8; i++)
	{
		if (i == 6)s[1][i] = '[';
		else if (i == 7)s[1][i] = '|';
		else
			s[1][i] = ' ';
	}

	s[2][0] = '+';
	for (int i = 1; i < 7; i++) {
		if (i == 1 || i == 6)
			s[2][i] = 'O';
		else
			s[2][i] = '-';
	}
	s[2][7] = '+';
}

Bus::Bus(Pos pos) : Enemy(pos)
{
	s = new char* [3];
	for (int i = 0; i < 3; i++)
	{
		s[i] = new char[8];
	}

	s[0][0] = '+';
	for (int i = 1; i < 7; i++)
		s[0][i] = '-';
	s[0][7] = '+';

	s[1][0] = '|';
	for (int i = 1; i < 8; i++)
	{
		if (i == 6)s[1][i] = '[';
		else if (i == 7)s[1][i] = '|';
		else
			s[1][i] = ' ';
	}

	s[2][0] = '+';
	for (int i = 1; i < 7; i++) {
		if (i == 1 || i == 6)
			s[2][i] = 'O';
		else
			s[2][i] = '-';
	}
	s[2][7] = '+';
}

char** Bus::shape()
{
	return s;
}

void Bus::testShape()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			gotoXY(j, i);
			cout << s[i][j];
		}
	}
}

int Bus::getType()
{
	return 2;
}

void Bus::sound()
{
	playSound("Sound/CarBus.wav");
}

Bus::~Bus()
{
	for (int i = 0; i < 3; i++)
		delete[] s[i];
	delete[] s;
}
