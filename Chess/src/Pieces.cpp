#include "Pieces.h"

#include <iostream>
#include <cmath>

static PASSING* _passing = new PASSING();
static NONE* _none = new NONE();

KING::KING(Pos p, Color c)
{
	type = king;
	position = p;
	color = c;
}

bool KING::checkValid(void* pieces, Pos new_pos, Color new_color)
{
	if (position == new_pos)
		return false;
	if (color == new_color)
		return false;

	int* board = (int*)pieces;

	if ((position.x + 1 == new_pos.x || position.x - 1 == new_pos.x) || (position.y + 1 == new_pos.y || position.y - 1 == new_pos.y))
	{
		return true;
	}
	else if (position.x + 2 == new_pos.x)
	{
		if (((Pieces*)board[7 + position.y * 8])->moved == false)
		{
			for (int i = position.x + 1; i < 7; i++)
			{
				if (((Pieces*)board[i + position.y * 8])->type != none)
				{
					return false;
				}
			}
			return true;
		}
	}
	else if (position.x - 2 == new_pos.x)
	{
		if (((Pieces*)board[0 + position.y * 8])->moved == false)
		{
			for (int i = 1; i < position.x; i++)
			{
				if (((Pieces*)board[i + position.y * 8])->type != none)
				{
					return false;
				}
			}
			return true;
		}
	}

	return false;
}

QUEEN::QUEEN(Pos p, Color c)
{
	type = queen;
	position = p;
	color = c;
}

bool QUEEN::checkValid(void* pieces, Pos new_pos, Color new_color)
{
	if (position == new_pos)
		return false;
	if (color == new_color)
		return false;

	int* board = (int*)pieces;

	if (position.x == new_pos.x)
	{
		if (position.y > new_pos.y)
		{
			for (int i = position.y - 1; i > new_pos.y; i--)
			{
				if (((Pieces*)board[new_pos.x + i * 8])->type != none && ((Pieces*)board[new_pos.x + i * 8])->type != passing)
					return false;
			}
		}
		else
		{
			for (int i = position.y + 1; i < new_pos.y; i++)
			{
				if (((Pieces*)board[new_pos.x + i * 8])->type != none && ((Pieces*)board[new_pos.x + i * 8])->type != passing)
					return false;
			}
		}
		return true;
	}
	else if (position.y == new_pos.y)
	{
		if (position.x > new_pos.x)
		{
			for (int i = position.x - 1; i > new_pos.x; i--)
			{
				if (((Pieces*)board[i + new_pos.y * 8])->type != none && ((Pieces*)board[i + new_pos.y * 8])->type != passing)
					return false;
			}
		}
		else
		{
			for (int i = position.x + 1; i < new_pos.x; i++)
			{
				if (((Pieces*)board[i + new_pos.y * 8])->type != none && ((Pieces*)board[i + new_pos.y * 8])->type != passing)
					return false;
			}
		}
		return true;
	}
	else if (abs(position.x - new_pos.x) == abs(position.y - new_pos.y))
	{
		if (position.x > new_pos.x)
		{
			if (position.y > new_pos.y)
			{
				for (int i = 1; i < position.y - new_pos.y; i++)
				{
					if (((Pieces*)board[position.x - i + (position.y - i) * 8])->type != none && ((Pieces*)board[position.x - i + (position.y - i) * 8])->type != passing)
						return false;
				}
			}
			else
			{
				for (int i = 1; i < new_pos.y - position.y; i++)
				{
					if (((Pieces*)board[position.x - i + (position.y + i) * 8])->type != none && ((Pieces*)board[position.x - i + (position.y + i) * 8])->type != passing)
						return false;
				}
			}
		}
		else
		{
			if (position.y > new_pos.y)
			{
				for (int i = 1; i < position.y - new_pos.y; i++)
				{
					if (((Pieces*)board[position.x + i + (position.y - i) * 8])->type != none && ((Pieces*)board[position.x + i + (position.y - i) * 8])->type != passing)
						return false;
				}
			}
			else
			{
				for (int i = 1; i < new_pos.y - position.y; i++)
				{
					if (((Pieces*)board[position.x + i + (position.y + i) * 8])->type != none && ((Pieces*)board[position.x + i + (position.y + i) * 8])->type != passing)
						return false;
				}
			}
		}
		return true;
	}
	return false;
}

BISHOP::BISHOP(Pos p, Color c)
{
	type = bishop;
	position = p;
	color = c;
}

bool BISHOP::checkValid(void* pieces, Pos new_pos, Color new_color)
{
	if (position == new_pos)
		return false;
	if (color == new_color)
		return false;

	int* board = (int*)pieces;

	if (abs(position.x - new_pos.x) == abs(position.y - new_pos.y))
	{
		if (position.x > new_pos.x)
		{
			if (position.y > new_pos.y)
			{
				for (int i = 1; i < position.y - new_pos.y; i++)
				{
					if (((Pieces*)board[position.x - i + (position.y - i) * 8])->type != none && ((Pieces*)board[position.x - i + (position.y - i) * 8])->type != passing)
						return false;
				}
			}
			else
			{
				for (int i = 1; i < new_pos.y - position.y; i++)
				{
					if (((Pieces*)board[position.x - i + (position.y + i) * 8])->type != none && ((Pieces*)board[position.x - i + (position.y + i) * 8])->type != passing)
						return false;
				}
			}
		}
		else
		{
			if (position.y > new_pos.y)
			{
				for (int i = 1; i < position.y - new_pos.y; i++)
				{
					if (((Pieces*)board[position.x + i + (position.y - i) * 8])->type != none && ((Pieces*)board[position.x + i + (position.y - i) * 8])->type != passing)
						return false;
				}
			}
			else
			{
				for (int i = 1; i < new_pos.y - position.y; i++)
				{
					if (((Pieces*)board[position.x + i + (position.y + i) * 8])->type != none && ((Pieces*)board[position.x + i + (position.y + i) * 8])->type != passing)
						return false;
				}
			}
		}
		return true;
	}
	return false;
}

KNIGHT::KNIGHT(Pos p, Color c)
{
	type = knight;
	position = p;
	color = c;
}

bool KNIGHT::checkValid(void* pieces, Pos new_pos, Color new_color)
{
	if (position == new_pos)
		return false;
	if (color == new_color)
		return false;

	if (((abs(position.y - new_pos.y) == 1) && (abs(position.x - new_pos.x) == 2)) || ((abs(position.y - new_pos.y) == 2) && (abs(position.x - new_pos.x) == 1)))
		return true;
	else
		return false;
}

ROOK::ROOK(Pos p, Color c)
{
	type = rook;
	position = p;
	color = c;
}

bool ROOK::checkValid(void* pieces, Pos new_pos, Color new_color)
{
	if (position == new_pos)
		return false;
	if (color == new_color)
		return false;

	int* board = (int*)pieces;

	if (position.x == new_pos.x)
	{
		if (position.y > new_pos.y)
		{
			for (int i = position.y - 1; i > new_pos.y; i--)
			{
				if (((Pieces*)board[new_pos.x + i * 8])->type != none && ((Pieces*)board[new_pos.x + i * 8])->type != passing)
					return false;
			}
		}
		else
		{
			for (int i = position.y + 1; i < new_pos.y; i++)
			{
				if (((Pieces*)board[new_pos.x + i * 8])->type != none && ((Pieces*)board[new_pos.x + i * 8])->type != passing)
					return false;
			}
		}
		return true;
	}
	else if (position.y == new_pos.y)
	{
		if (position.x > new_pos.x)
		{
			for (int i = position.x - 1; i > new_pos.x; i--)
			{
				if (((Pieces*)board[i + new_pos.y * 8])->type != none && ((Pieces*)board[i + new_pos.y * 8])->type != passing)
					return false;
			}
		}
		else
		{
			for (int i = position.x + 1; i < new_pos.x; i++)
			{
				if (((Pieces*)board[i + new_pos.y * 8])->type != none && ((Pieces*)board[i + new_pos.y * 8])->type != passing)
					return false;
			}
		}
		return true;
	}

	return false;
}

PAWN::PAWN(Pos p, Color c)
{
	type = pawn;
	position = p;
	color = c;
}

bool PAWN::checkValid(void* pieces, Pos new_pos, Color new_color)
{
	if (position == new_pos)
		return false;
	if (color == new_color)
		return false;

	int* board = (int*)pieces;

	if (position.x == new_pos.x)
	{
		if (abs(position.y - new_pos.y) > 2)
		{
			return false;
		}
		else if (position.y + 2 * int(color) == new_pos.y)
		{
			if (!moved)
			{
				for (int i = 1; i <= 2; i++)
				{
					if (((Pieces*)board[position.x + (position.y + i * int(color)) * 8])->type != none)
					{
						return false;
					}
				}
				return true;
			}
		}
		else if (position.y + int(color) == new_pos.y && ((Pieces*)board[new_pos.ToNum()])->type == none)
		{
			return true;
		}
	}
	else if (abs(position.x - new_pos.x) == 1)
	{
		if (position.y + 1 * int(color) == new_pos.y)
		{
			if (((Pieces*)board[new_pos.ToNum()])->type != none)
			{
				return true;
			}
		}
	}
	return false;
}