#pragma once

#include "deco.h"

class Pieces
{
public:
	Pos position;
	Type type;
	Color color;
	bool moved = false;
};

class PASSING : public Pieces
{
public:
	PASSING() { type = passing; }
};

class NONE : public Pieces
{
public:
	NONE() { type = none; }
};

class KING : public Pieces
{
public:
	KING(Pos p, Color c);

	bool checkValid(void* pieces, Pos new_pos, Color new_color);
};

class QUEEN : public Pieces
{
public:
	QUEEN(Pos p, Color c);

	bool checkValid(void* pieces, Pos new_pos, Color new_color);
};

class BISHOP : public Pieces
{
public:
	BISHOP(Pos p, Color c);

	bool checkValid(void* pieces, Pos new_pos, Color new_color);
};

class KNIGHT : public Pieces
{
public:
	KNIGHT(Pos p, Color c);

	bool checkValid(void* pieces, Pos new_pos, Color new_color);
};

class ROOK : public Pieces
{
public:
	ROOK(Pos p, Color c);

	bool checkValid(void* pieces, Pos new_pos, Color new_color);
};

class PAWN : public Pieces
{
public:
	PAWN(Pos p, Color c);

	bool checkValid(void* pieces, Pos new_pos, Color new_color);
};