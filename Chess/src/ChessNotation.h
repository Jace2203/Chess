#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "deco.h"
#include "Pieces.h"
#include "Game.h"

class ChessNotation
{
public:
	char** list = new char*[500];
	int* list_length = new int[500];
	int length = 0;
	int MAX = 0;

	bool ReadFromFile();
	void ReadIn(Pos start, Pos end, bool castling, Type capture);
	void backward();
	void forward();
	void WriteOutFile();

	void clear();
};