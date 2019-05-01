#include "Chessboard.h"

#include <Windows.h>
#include <functional>
#include <cmath>

static PASSING* _passing = new PASSING();
static NONE* _none = new NONE();

ChessBoard::~ChessBoard()
{

}

void ChessBoard::init()
{
	passant[0] = NULL_POS;
	passant[1] = NULL_POS;
	for (int i = 0; i < 64; i++)
	{
		pieces[i] = (int*)_none;
	}

	white_pieces = new Pos[16];
	black_pieces = new Pos[16];
	white_length = 16;
	black_length = 16;

	pieces[0] = (int*)new ROOK(Pos(0), white);
	white_pieces[0] = Pos(0);
	pieces[1] = (int*)new KNIGHT(Pos(1), white);
	white_pieces[1] = Pos(1);
	pieces[2] = (int*)new BISHOP(Pos(2), white);
	white_pieces[2] = Pos(2);
	pieces[3] = (int*)new QUEEN(Pos(3), white);
	white_pieces[3] = Pos(3);
	pieces[4] = (int*)new KING(Pos(4), white);
	white_pieces[4] = Pos(4);
	pieces[5] = (int*)new BISHOP(Pos(5), white);
	white_pieces[5] = Pos(5);
	pieces[6] = (int*)new KNIGHT(Pos(6), white);
	white_pieces[6] = Pos(6);
	pieces[7] = (int*)new ROOK(Pos(7), white);
	white_pieces[7] = Pos(7);
	for (int i = 0; i < 8; i++)
	{
		pieces[i + 8] = (int*)new PAWN(Pos(i + 8), white);
		white_pieces[i + 8] = Pos(i + 8);
		pieces[i + 48] = (int*)new PAWN(Pos(i + 48), black);
		black_pieces[i] = Pos(i + 48);
	}
	pieces[56] = (int*)new ROOK(Pos(56), black);
	black_pieces[8] = Pos(56);
	pieces[57] = (int*)new KNIGHT(Pos(57), black);
	black_pieces[9] = Pos(57);
	pieces[58] = (int*)new BISHOP(Pos(58), black);
	black_pieces[10] = Pos(58);
	pieces[59] = (int*)new QUEEN(Pos(59), black);
	black_pieces[11] = Pos(59);
	pieces[60] = (int*)new KING(Pos(60), black);
	black_pieces[12] = Pos(60);
	pieces[61] = (int*)new BISHOP(Pos(61), black);
	black_pieces[13] = Pos(61);
	pieces[62] = (int*)new KNIGHT(Pos(62), black);
	black_pieces[14] = Pos(62);
	pieces[63] = (int*)new ROOK(Pos(63), black);
	black_pieces[15] = Pos(63);

	color = white;
	start_pos = NULL_POS;
	end_pos = NULL_POS;

	turn = false;

	w_repeat_first = 0;
	w_repeat_second = 0;
	b_repeat_first = 0;
	b_repeat_second = 0;

	fifty = 0;
	last_moved = none;
	captured = false;
	captured_type = none;
}

ChessBoard* ChessBoard::Copy()
{
	int count_w = 0;
	int count_b = 0;
	ChessBoard* result = new ChessBoard(*this);
	result->white_pieces = new Pos[16];
	result->black_pieces = new Pos[16];
	for (int i = 0; i < 64; i++)
	{
		if (pieces[i] != (int*)_none)
		{
			Pieces* temp = new Pieces(*(Pieces*)pieces[i]);
			result->pieces[i] = (int*)temp;
			if (temp->color == white)
			{
				result->white_pieces[count_w] = temp->position;
				count_w++;
			}
			else if (temp->color == black)
			{
				result->black_pieces[count_b] = temp->position;
				count_b++;
			}
		}
	}

	result->white_length = count_w;
	result->black_length = count_b;

	return result;
}

void ChessBoard::CopyPieces(Color color)
{	
	if (color == white)
	{
		if (turn)
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					white_type_repeat_second[i] = none;
				}
				else
				{
					white_type_repeat_second[i] = ((Pieces*)pieces[i])->type;
				}
				if (((Pieces*)pieces[i])->type == passing || ((Pieces*)pieces[i])->type == none)
				{
					white_color_repeat_second[i] = white;
				}
				else
				{
					white_color_repeat_second[i] = ((Pieces*)pieces[i])->color;
				}
			}
		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					white_type_repeat_first[i] = none;
				}
				else
				{
					white_type_repeat_first[i] = ((Pieces*)pieces[i])->type;
				}
				if (((Pieces*)pieces[i])->type == passing || ((Pieces*)pieces[i])->type == none)
				{
					white_color_repeat_first[i] = white;
				}
				else
				{
					white_color_repeat_first[i] = ((Pieces*)pieces[i])->color;
				}
			}
		}
	}
	else
	{
		if (turn)
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					white_type_repeat_second[i] = none;
				}
				else
				{
					white_type_repeat_second[i] = ((Pieces*)pieces[i])->type;
				}
				if (((Pieces*)pieces[i])->type == passing || ((Pieces*)pieces[i])->type == none)
				{
					white_color_repeat_second[i] = white;
				}
				else
				{
					white_color_repeat_second[i] = ((Pieces*)pieces[i])->color;
				}
			}
		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					black_type_repeat_first[i] = none;
				}
				else
				{
					black_type_repeat_first[i] = ((Pieces*)pieces[i])->type;
				}
				if (((Pieces*)pieces[i])->type == passing || ((Pieces*)pieces[i])->type == none)
				{
					black_color_repeat_first[i] = white;
				}
				else
				{
					black_color_repeat_first[i] = ((Pieces*)pieces[i])->color;
				}
			}
		}
	}
}

void ChessBoard::p_move(Pos pos, Pos new_pos)
{
	pieces[new_pos.ToNum()] = pieces[pos.ToNum()];
	pieces[pos.ToNum()] = (int*)_none;
}

bool ChessBoard::move(Pos pos, Pos new_pos, Color color)
{
	Color* new_color = new Color;
	if (((Pieces*)pieces[new_pos.ToNum()])->type != none)
	{
		new_color = &((Pieces*)pieces[new_pos.ToNum()])->color;
	}
	else
	{
		*new_color = invert(color);
	}

	if (((Pieces*)pieces[new_pos.ToNum()])->type == king)
	{
		return false;
	}

	switch (((Pieces*)pieces[pos.ToNum()])->type)
	{
		case none: return false;
		case king:
		{
			KING* piece = (KING*)pieces[pos.ToNum()];
			if (piece->checkValid(pieces, new_pos, *new_color) && piece->color == color)
			{
				ChessBoard* board = Copy();
				if (abs(pos.x - new_pos.x) == 2)
				{
					if (pos.x > new_pos.x)
					{
						ROOK* Rook = (ROOK*)pieces[0 + pos.y * 8];

						if (color == white)
						{
							for (int i = 0; i < white_length; i++)
							{
								if (board->white_pieces[i] == pos)
								{
									board->white_pieces[i] = new_pos;
									break;
								}
							}
						}
						else
						{
							for (int i = 0; i < black_length; i++)
							{
								if (board->black_pieces[i] == pos)
								{
									board->black_pieces[i] = new_pos;
									break;
								}
							}
						}
						board->p_move(Rook->position, Pos(pos.x - 1, pos.y));
						((Pieces*)(board->pieces[Rook->position.ToNum()]))->position = Pos(pos.x - 1, pos.y);
						((Pieces*)(board->pieces[Rook->position.ToNum()]))->moved = true;
					}
					else
					{
						ROOK* Rook = (ROOK*)pieces[7 + pos.y * 8];

						if (color == white)
						{
							for (int i = 0; i < white_length; i++)
							{
								if (board->white_pieces[i] == pos)
								{
									board->white_pieces[i] = new_pos;
									break;
								}
							}
						}
						else
						{
							for (int i = 0; i < black_length; i++)
							{
								if (board->black_pieces[i] == pos)
								{
									board->black_pieces[i] = new_pos;
									break;
								}
							}
						}
						board->p_move(Rook->position, Pos(pos.x + 1, pos.y));
						((Pieces*)(board->pieces[Rook->position.ToNum()]))->position = Pos(pos.x + 1, pos.y);
						((Pieces*)(board->pieces[Rook->position.ToNum()]))->moved = true;
					}
				}
				else if (((Pieces*)board->pieces[new_pos.ToNum()])->type != none && ((Pieces*)board->pieces[new_pos.ToNum()])->type != passing)
				{
					board->captured = true;
					board->RemovePiece(invert(color), new_pos);

				}

				if (color == white)
				{
					for (int i = 0; i < white_length; i++)
					{
						if (board->white_pieces[i] == pos)
						{
							board->white_pieces[i] = new_pos;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_length; i++)
					{
						if (board->black_pieces[i] == pos)
						{
							board->black_pieces[i] = new_pos;
							break;
						}
					}
				}
				board->p_move(pos, new_pos);
				((Pieces*)board->pieces[piece->position.ToNum()])->position = new_pos;
				((Pieces*)board->pieces[piece->position.ToNum()])->moved = true;
				board->UpdatePassant();
				board->last_moved = king;
				if (!board->Check(invert(color)))
				{
					if (abs(pos.x - new_pos.x) == 2)
					{
						if (pos.x > new_pos.x)
						{
							ROOK* Rook = (ROOK*)pieces[0 + pos.y * 8];

							if (color == white)
							{
								for (int i = 0; i < white_length; i++)
								{
									if (white_pieces[i] == pos)
									{
										white_pieces[i] = new_pos;
										break;
									}
								}
							}
							else
							{
								for (int i = 0; i < black_length; i++)
								{
									if (black_pieces[i] == pos)
									{
										black_pieces[i] = new_pos;
										break;
									}
								}
							}
							p_move(Rook->position, Pos(pos.x - 1, pos.y));
							Rook->position = Pos(pos.x - 1, pos.y);
							Rook->moved = true;
							castling = true;
						}
						else
						{
							ROOK* Rook = (ROOK*)pieces[7 + pos.y * 8];

							if (color == white)
							{
								for (int i = 0; i < white_length; i++)
								{
									if (white_pieces[i] == pos)
									{
										white_pieces[i] = new_pos;
										break;
									}
								}
							}
							else
							{
								for (int i = 0; i < black_length; i++)
								{
									if (black_pieces[i] == pos)
									{
										black_pieces[i] = new_pos;
										break;
									}
								}
							}
							p_move(Rook->position, Pos(pos.x + 1, pos.y));
							Rook->position = Pos(pos.x + 1, pos.y);
							Rook->moved = true;
						}
					}
					else if (((Pieces*)pieces[new_pos.ToNum()])->type != none && ((Pieces*)pieces[new_pos.ToNum()])->type != passing)
					{
						captured = true;
						RemovePiece(invert(color), new_pos);

					}

					if (color == white)
					{
						for (int i = 0; i < white_length; i++)
						{
							if (white_pieces[i] == pos)
							{
								white_pieces[i] = new_pos;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_length; i++)
						{
							if (black_pieces[i] == pos)
							{
								black_pieces[i] = new_pos;
								break;
							}
						}
					}
					p_move(pos, new_pos);
					piece->position = new_pos;
					piece->moved = true;
					UpdatePassant();
					last_moved = king;
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case queen:
		{
			QUEEN* piece = (QUEEN*)pieces[pos.ToNum()];
			if (piece->checkValid(pieces, new_pos, *new_color) && piece->color == color)
			{
				ChessBoard* board = Copy();
				if (((Pieces*)board->pieces[new_pos.ToNum()])->type != none && ((Pieces*)board->pieces[new_pos.ToNum()])->type != passing)
				{
					board->captured = true;
					board->RemovePiece(invert(color), new_pos);
				}

				if (color == white)
				{
					for (int i = 0; i < white_length; i++)
					{
						if (board->white_pieces[i] == pos)
						{
							board->white_pieces[i] = new_pos;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_length; i++)
					{
						if (board->black_pieces[i] == pos)
						{
							board->black_pieces[i] = new_pos;
							break;
						}
					}
				}
				board->p_move(pos, new_pos);
				((Pieces*)board->pieces[piece->position.ToNum()])->position = new_pos;
				((Pieces*)board->pieces[piece->position.ToNum()])->moved = true;
				board->UpdatePassant();
				board->last_moved = queen;
				if (!board->Check(invert(color)))
				{
					if (((Pieces*)pieces[new_pos.ToNum()])->type != none && ((Pieces*)pieces[new_pos.ToNum()])->type != passing)
					{
						captured = true;
						RemovePiece(invert(color), new_pos);
					}

					if (color == white)
					{
						for (int i = 0; i < white_length; i++)
						{
							if (white_pieces[i] == pos)
							{
								white_pieces[i] = new_pos;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_length; i++)
						{
							if (black_pieces[i] == pos)
							{
								black_pieces[i] = new_pos;
								break;
							}
						}
					}
					p_move(pos, new_pos);
					piece->position = new_pos;
					piece->moved = true;
					UpdatePassant();
					last_moved = queen;
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case bishop:
		{
			BISHOP* piece = (BISHOP*)pieces[pos.ToNum()];
			if (piece->checkValid(pieces, new_pos, *new_color) && piece->color == color)
			{
				ChessBoard* board = Copy();
				if (((Pieces*)board->pieces[new_pos.ToNum()])->type != none && ((Pieces*)board->pieces[new_pos.ToNum()])->type != passing)
				{
					board->captured = true;
					board->RemovePiece(invert(color), new_pos);
				}

				if (color == white)
				{
					for (int i = 0; i < white_length; i++)
					{
						if (board->white_pieces[i] == pos)
						{
							board->white_pieces[i] = new_pos;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_length; i++)
					{
						if (board->black_pieces[i] == pos)
						{
							board->black_pieces[i] = new_pos;
							break;
						}
					}
				}
				board->p_move(pos, new_pos);
				((Pieces*)board->pieces[piece->position.ToNum()])->position = new_pos;
				((Pieces*)board->pieces[piece->position.ToNum()])->moved = true;
				board->UpdatePassant();
				board->last_moved = bishop;
				if (!board->Check(invert(color)))
				{
					if (((Pieces*)pieces[new_pos.ToNum()])->type != none && ((Pieces*)pieces[new_pos.ToNum()])->type != passing)
					{
						captured = true;
						RemovePiece(invert(color), new_pos);
					}

					if (color == white)
					{
						for (int i = 0; i < white_length; i++)
						{
							if (white_pieces[i] == pos)
							{
								white_pieces[i] = new_pos;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_length; i++)
						{
							if (black_pieces[i] == pos)
							{
								black_pieces[i] = new_pos;
								break;
							}
						}
					}
					p_move(pos, new_pos);
					piece->position = new_pos;
					piece->moved = true;
					UpdatePassant();
					last_moved = bishop;
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case knight:
		{
			KNIGHT* piece = (KNIGHT*)pieces[pos.ToNum()];
			if (piece->checkValid(pieces, new_pos, *new_color) && piece->color == color)
			{
				ChessBoard* board = Copy();
				if (((Pieces*)board->pieces[new_pos.ToNum()])->type != none && ((Pieces*)board->pieces[new_pos.ToNum()])->type != passing)
				{
					board->captured = true;
					board->RemovePiece(invert(color), new_pos);
				}

				if (color == white)
				{
					for (int i = 0; i < white_length; i++)
					{
						if (board->white_pieces[i] == pos)
						{
							board->white_pieces[i] = new_pos;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_length; i++)
					{
						if (board->black_pieces[i] == pos)
						{
							board->black_pieces[i] = new_pos;
							break;
						}
					}
				}
				board->p_move(pos, new_pos);
				((Pieces*)board->pieces[piece->position.ToNum()])->position = new_pos;
				((Pieces*)board->pieces[piece->position.ToNum()])->moved = true;
				board->UpdatePassant();
				board->last_moved = knight;
				if (!board->Check(invert(color)))
				{
					if (((Pieces*)pieces[new_pos.ToNum()])->type != none && ((Pieces*)pieces[new_pos.ToNum()])->type != passing)
					{
						captured = true;
						RemovePiece(invert(color), new_pos);
					}

					if (color == white)
					{
						for (int i = 0; i < white_length; i++)
						{
							if (white_pieces[i] == pos)
							{
								white_pieces[i] = new_pos;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_length; i++)
						{
							if (black_pieces[i] == pos)
							{
								black_pieces[i] = new_pos;
								break;
							}
						}
					}
					p_move(pos, new_pos);
					piece->position = new_pos;
					piece->moved = true;
					UpdatePassant();
					last_moved = knight;
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case rook:
		{
			ROOK* piece = (ROOK*)pieces[pos.ToNum()];
			if (piece->checkValid(pieces, new_pos, *new_color) && piece->color == color)
			{
				ChessBoard* board = Copy();
				if (((Pieces*)board->pieces[new_pos.ToNum()])->type != none && ((Pieces*)board->pieces[new_pos.ToNum()])->type != passing)
				{
					board->captured = true;
					board->RemovePiece(invert(color), new_pos);
				}

				if (color == white)
				{
					for (int i = 0; i < white_length; i++)
					{
						if (board->white_pieces[i] == pos)
						{
							board->white_pieces[i] = new_pos;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_length; i++)
					{
						if (board->black_pieces[i] == pos)
						{
							board->black_pieces[i] = new_pos;
							break;
						}
					}
				}
				board->p_move(pos, new_pos);
				((Pieces*)board->pieces[piece->position.ToNum()])->position = new_pos;
				((Pieces*)board->pieces[piece->position.ToNum()])->moved = true;
				board->UpdatePassant();
				board->last_moved = rook;
				if (!board->Check(invert(color)))
				{
					if (((Pieces*)pieces[new_pos.ToNum()])->type != none && ((Pieces*)pieces[new_pos.ToNum()])->type != passing)
					{
						captured = true;
						RemovePiece(invert(color), new_pos);
					}

					if (color == white)
					{
						for (int i = 0; i < white_length; i++)
						{
							if (white_pieces[i] == pos)
							{
								white_pieces[i] = new_pos;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_length; i++)
						{
							if (black_pieces[i] == pos)
							{
								black_pieces[i] = new_pos;
								break;
							}
						}
					}
					p_move(pos, new_pos);
					piece->position = new_pos;
					piece->moved = true;
					UpdatePassant();
					last_moved = rook;
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
		case pawn:
		{
			PAWN* piece = (PAWN*)pieces[pos.ToNum()];
			if (piece->checkValid(pieces, new_pos, *new_color) && piece->color == color)
			{
				ChessBoard* board = Copy();
				if (((Pieces*)board->pieces[new_pos.ToNum()])->type == passing)
				{
					Pos temp = Pos(new_pos.x, new_pos.y - int(color));
					board->pieces[temp.ToNum()] = (int*)_none;
					board->captured = true;
					board->RemovePiece(invert(color), temp);
				}
				else if (((Pieces*)board->pieces[new_pos.ToNum()])->type != none)
				{
					board->captured = true;
					board->RemovePiece(invert(color), new_pos);
				}
				if (abs(pos.y - new_pos.y) == 2)
				{
					board->pieces[pos.x + (pos.y + int(color)) * 8] = (int*)_passing;
					board->passant[1] = Pos(pos.x, pos.y + int(color));
				}

				if (color == white)
				{
					for (int i = 0; i < white_length; i++)
					{
						if (board->white_pieces[i] == pos)
						{
							board->white_pieces[i] = new_pos;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_length; i++)
					{
						if (board->black_pieces[i] == pos)
						{
							board->black_pieces[i] = new_pos;
							break;
						}
					}
				}					
				board->p_move(pos, new_pos);
				((Pieces*)board->pieces[piece->position.ToNum()])->position = new_pos;
				((Pieces*)board->pieces[piece->position.ToNum()])->moved = true;
				board->UpdatePassant();
				board->last_moved = pawn;
				if (!board->Check(invert(color)))
				{
					if (((Pieces*)pieces[new_pos.ToNum()])->type == passing)
					{
						Pos temp = Pos(new_pos.x, new_pos.y - int(color));
						pieces[temp.ToNum()] = (int*)_none;
						captured = true;
						RemovePiece(invert(color), temp);
					}
					else if (((Pieces*)pieces[new_pos.ToNum()])->type != none)
					{
						captured = true;
						RemovePiece(invert(color), new_pos);
					}
					if (abs(pos.y - new_pos.y) == 2)
					{
						pieces[pos.x + (pos.y + int(color)) * 8] = (int*)_passing;
						passant[1] = Pos(pos.x, pos.y + int(color));
					}

					if (color == white)
					{
						for (int i = 0; i < white_length; i++)
						{
							if (white_pieces[i] == pos)
							{
								white_pieces[i] = new_pos;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_length; i++)
						{
							if (black_pieces[i] == pos)
							{
								black_pieces[i] = new_pos;
								break;
							}
						}
					}
					p_move(pos, new_pos);
					piece->position = new_pos;
					piece->moved = true;
					UpdatePassant();
					last_moved = pawn;
					return true;
				}
			}
			else
			{
				return false;
			}
			break;
		}
	}
	return false;
}

void ChessBoard::UpdatePassant()
{
	Pos temp = passant[0];
	if (temp != NULL_POS)
	{
		if (pieces[passant[0].ToNum()] == (int*)_passing)
			pieces[passant[0].ToNum()] = (int*)_none;
	}
	passant[0] = passant[1];
	passant[1] = NULL_POS;
}

void ChessBoard::RemovePiece(Color color, Pos pos)
{
	bool found = false;
	if (color == white)
	{
		for (int i = 0; i < white_length; i++)
		{
			if (found)
			{
				white_pieces[i - 1] = white_pieces[i];
			}
			else
			{
				if (white_pieces[i] == pos)
				{
					found = true;
					captured_type = ((Pieces*)(pieces[white_pieces[i].ToNum()]))->type;
				}
			}
		}
		if (found)
		{
			white_length--;
		}
	}
	else if (color == black)
	{
		for (int i = 0; i < black_length; i++)
		{
			if (found)
			{
				black_pieces[i - 1] = black_pieces[i];
			}
			else
			{
				if (black_pieces[i] == pos)
				{
					found = true;
					captured_type = ((Pieces*)(pieces[black_pieces[i].ToNum()]))->type;
				}
			}
		}
		if (found)
		{
			black_length--;
		}
	}
}

Pos ChessBoard::FindKing(Color color)
{
	Pos* list = nullptr;
	int length;
	Pos result;
	if (color == white)
	{
		list = white_pieces;
		length = white_length;
	}
	else
	{
		list = black_pieces;
		length = black_length;
	}

	for (int i = 0; i < length; i++)
	{
		Pieces* temp = (Pieces*)pieces[list[i].ToNum()];
		if (temp->type == king)
		{
			result = list[i];
			break;
		}
	}
	return result;
}

bool ChessBoard::Check(Color color)
{
	Pos target = FindKing(invert(color));
	Pos* list = nullptr;
	int length;
	if (color == white)
	{
		list = white_pieces;
		length = white_length;
	}
	else
	{
		list = black_pieces;
		length = black_length;
	}
	for (int k = 0; k < length; k++)
	{
		Pos pos = list[k];
		Pieces* piece = (Pieces*)pieces[pos.ToNum()];
		switch (piece->type)
		{
		case king:
		{
			break;
		}
		case queen:
		{
			if (pos.x == target.x)
			{
				if (pos.y > target.y)
				{
					bool temp = true;
					for (int i = pos.y - 1; i > target.y; i--)
					{
						if (((Pieces*)pieces[pos.x + i * 8])->type != none && ((Pieces*)pieces[pos.x + i * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
				else
				{
					bool temp = true;
					for (int i = pos.y + 1; i < target.y; i++)
					{
						if (((Pieces*)pieces[pos.x + i * 8])->type != none && ((Pieces*)pieces[pos.x + i * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
			}
			else if (pos.y == target.y)
			{
				if (pos.x > target.x)
				{
					bool temp = true;
					for (int i = pos.x - 1; i > target.x; i--)
					{
						if (((Pieces*)pieces[i + pos.y * 8])->type != none && ((Pieces*)pieces[i + pos.y * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
				else
				{
					bool temp = true;
					for (int i = pos.x + 1; i < target.x; i++)
					{
						if (((Pieces*)pieces[i + pos.y * 8])->type != none && ((Pieces*)pieces[i + pos.y * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
			}
			else if (abs(pos.x - target.x) == abs(pos.y - target.y))
			{
				if (pos.x > target.x)
				{
					if (pos.y > target.y)
					{
						bool temp = true;
						for (int i = 1; i < pos.y - target.y; i++)
						{
							if (((Pieces*)pieces[pos.x - i + (pos.y - i) * 8])->type != none && ((Pieces*)pieces[pos.x - i + (pos.y - i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
					else
					{
						bool temp = true;
						for (int i = 1; i < target.y - pos.y; i++)
						{
							if (((Pieces*)pieces[pos.x - i + (pos.y + i) * 8])->type != none && ((Pieces*)pieces[pos.x - i + (pos.y + i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
				}
				else
				{
					if (pos.y > target.y)
					{
						bool temp = true;
						for (int i = 1; i < pos.y - target.y; i++)
						{
							if (((Pieces*)pieces[pos.x + i + (pos.y - i) * 8])->type != none && ((Pieces*)pieces[pos.x + i + (pos.y - i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
					else
					{
						bool temp = true;
						for (int i = 1; i < target.y - pos.y; i++)
						{
							if (((Pieces*)pieces[pos.x + i + (pos.y + i) * 8])->type != none && ((Pieces*)pieces[pos.x + i + (pos.y + i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
				}
			}
			break;
		}
		case bishop:
		{
			if (abs(pos.x - target.x) == abs(pos.y - target.y))
			{
				if (pos.x > target.x)
				{
					if (pos.y > target.y)
					{
						bool temp = true;
						for (int i = 1; i < pos.y - target.y; i++)
						{
							if (((Pieces*)pieces[pos.x - i + (pos.y - i) * 8])->type != none && ((Pieces*)pieces[pos.x - i + (pos.y - i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
					else
					{
						bool temp = true;
						for (int i = 1; i < target.y - pos.y; i++)
						{
							if (((Pieces*)pieces[pos.x - i + (pos.y + i) * 8])->type != none && ((Pieces*)pieces[pos.x - i + (pos.y + i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
				}
				else
				{
					if (pos.y > target.y)
					{
						bool temp = true;
						for (int i = 1; i < pos.y - target.y; i++)
						{
							if (((Pieces*)pieces[pos.x + i + (pos.y - i) * 8])->type != none && ((Pieces*)pieces[pos.x + i + (pos.y - i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
					else
					{
						bool temp = true;
						for (int i = 1; i < target.y - pos.y; i++)
						{
							if (((Pieces*)pieces[pos.x + i + (pos.y + i) * 8])->type != none && ((Pieces*)pieces[pos.x + i + (pos.y + i) * 8])->type != passing)
							{
								temp = false;
								break;
							}
						}
						if (temp)
							return true;
					}
				}
			}
			break;
		}
		case knight:
		{
			if (((abs(pos.y - target.y) == 1) && (abs(pos.x - target.x) == 2)) || ((abs(pos.y - target.y) == 2) && (abs(pos.x - target.x) == 1)))
				return true;
			break;
		}
		case rook:
		{
			if (pos.x == target.x)
			{
				if (pos.y > target.y)
				{
					bool temp = true;
					for (int i = pos.y - 1; i > target.y; i--)
					{
						if (((Pieces*)pieces[pos.x + i * 8])->type != none && ((Pieces*)pieces[pos.x + i * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
				else
				{
					bool temp = true;
					for (int i = pos.y + 1; i < target.y; i++)
					{
						if (((Pieces*)pieces[pos.x + i * 8])->type != none && ((Pieces*)pieces[pos.x + i * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
			}
			else if (pos.y == target.y)
			{
				if (pos.x > target.x)
				{
					bool temp = true;
					for (int i = pos.x - 1; i > target.x; i--)
					{
						if (((Pieces*)pieces[i + pos.y * 8])->type != none && ((Pieces*)pieces[i + pos.y * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
				else
				{
					bool temp = true;
					for (int i = pos.x + 1; i < target.x; i++)
					{
						if (((Pieces*)pieces[i + pos.y * 8])->type != none && ((Pieces*)pieces[i + pos.y * 8])->type != passing)
						{
							temp = false;
							break;
						}
					}
					if (temp)
						return true;
				}
			}
			break;
		}
		case pawn:
		{
			if (abs(pos.x - target.x) == 1)
			{
				if (pos.y + 1 * int(color) == target.y)
				{
					return true;
				}
			}
			break;
		}
		}
	}

	return false;
}

bool ChessBoard::Checkmate(Color color)
{
	int length;
	Pos* list;
	if (color == white)
	{
		length = white_length;
		list = white_pieces;
	}
	else
	{
		length = black_length;
		list = black_pieces;
	}

	for (int i = 0; i < length; i++)
	{
		Pos pos = list[i];
		Pieces piece = *(Pieces*)pieces[pos.ToNum()];

		switch (piece.type)
		{
		case king:
		{
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8) && (pos.y + j >= 0) && (pos.y + j < 8))
					{
						ChessBoard board = *Copy();
						if (board.move(pos, Pos(pos.x + i, pos.y + j), piece.color))
						{
							if (!board.Check(invert(color)))
							{
								
								return false;
							}
						}
						
					}
				}
			}
			break;
		}
		case queen:
		{
			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(i, pos.y), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, i), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y - i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y + i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y - i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y + i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}
			break;
		}
		case bishop:
		{
			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y - i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y + i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y - i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y + i), piece.color))
					{
						if (!board.Check(invert(color)))
						{
							
							return false;
						}
					}
					
				}
			}
			break;
		}
		case knight:
		{
			if ((pos.x + 2 < 8) && (pos.y + 1 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 2, pos.y + 1), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x + 1 < 8) && (pos.y + 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 1, pos.y + 2), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x - 2 >= 0) && (pos.y + 1 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 2, pos.y + 1), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x - 1 >= 0) && (pos.y + 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 1, pos.y + 2), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x + 2 < 8) && (pos.y - 1 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 2, pos.y - 1), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x + 1 < 8) && (pos.y - 2 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 1, pos.y - 2), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x - 2 >= 0) && (pos.y - 1 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 2, pos.y - 1), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.x - 1 >= 0) && (pos.y - 2 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 1, pos.y - 2), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}
			break;
		}
		case rook:
		{
			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(i, pos.y), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, i), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}
			break;
		}
		case pawn:
		{
			if ((pos.y + int(piece.color) * 2 >= 0) && (pos.y + int(piece.color) * 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, pos.y + int(piece.color) * 2), piece.color))
				{
					if (!board.Check(invert(color)))
					{
						
						return false;
					}
				}
				
			}

			if ((pos.y + int(piece.color) >= 0) && (pos.y + int(piece.color) < 8))
			{
				for (int i = -1; i < 2; i++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8))
					{
						ChessBoard board = *Copy();
						if (board.move(pos, Pos(pos.x + i, pos.y + int(piece.color)), piece.color))
						{
							if (!board.Check(invert(color)))
							{
								
								return false;
							}
						}
						
					}
				}
			}
			break;
		}
		}
	}
	return true;
}

void ChessBoard::Promotion(Pos pos, Type type)
{
	std::cout << "Promotion!!!" << std::endl;
	((Pieces*)pieces[pos.ToNum()])->type = type;
}

void ChessBoard::UpdateRepeat(Color color)
{
	if (color == white)
	{
		if (turn)
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					if (white_type_repeat_second[i] != none || white_color_repeat_second[i] != white)
					{
						CopyPieces(color);
						w_repeat_second = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type == none)
				{
					if (white_type_repeat_second[i] != none || white_color_repeat_second[i] != white)
					{
						CopyPieces(color);
						w_repeat_second = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type != white_type_repeat_second[i] || ((Pieces*)pieces[i])->color != white_color_repeat_second[i])
				{
					CopyPieces(color);
					w_repeat_second = 1;
					return;
				}
			}
			w_repeat_second += 1;
		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					if (white_type_repeat_first[i] != none || white_color_repeat_first[i] != white)
					{
						CopyPieces(color);
						w_repeat_first = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type == none)
				{
					if (white_type_repeat_first[i] != none || white_color_repeat_first[i] != white)
					{
						CopyPieces(color);
						w_repeat_first = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type != white_type_repeat_first[i] || ((Pieces*)pieces[i])->color != white_color_repeat_first[i])
				{
					CopyPieces(color);
					w_repeat_first = 1;
					return;
				}
			}
			w_repeat_first += 1;
		}
	}
	else
	{
		if (turn)
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					if (black_type_repeat_second[i] != none || black_color_repeat_second[i] != white)
					{
						CopyPieces(color);
						b_repeat_second = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type == none)
				{
					if (black_type_repeat_second[i] != none || black_color_repeat_second[i] != white)
					{
						CopyPieces(color);
						b_repeat_second = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type != black_type_repeat_second[i] || ((Pieces*)pieces[i])->color != black_color_repeat_second[i])
				{
					CopyPieces(color);
					b_repeat_second = 1;
					return;
				}
			}
			b_repeat_second += 1;
		}
		else
		{
			for (int i = 0; i < 64; i++)
			{
				if (((Pieces*)pieces[i])->type == passing)
				{
					if (black_type_repeat_first[i] != none || black_color_repeat_first[i] != white)
					{
						CopyPieces(color);
						b_repeat_first = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type == none)
				{
					if (black_type_repeat_first[i] != none || black_color_repeat_first[i] != white)
					{
						CopyPieces(color);
						b_repeat_first = 1;
						return;
					}
				}
				else if (((Pieces*)pieces[i])->type != black_type_repeat_first[i] || ((Pieces*)pieces[i])->color != black_color_repeat_first[i])
				{
					CopyPieces(color);
					b_repeat_first = 1;
					return;
				}
			}
			b_repeat_first += 1;
		}
	}
}

void ChessBoard::UpdateFifty()
{
	if (captured)
	{
		fifty = 1;
	}
	else if (last_moved == pawn)
	{
		fifty = 1;
	}
	else
	{
		fifty += 1;
	}
	captured = false;
}

bool ChessBoard::IsDraw(Color color)
{
	//MessageBox(NULL, "Stalemate", "Draw", MB_OK);

	// Theefold Repetition : identical position
	
	if (w_repeat_first == 3 || w_repeat_second == 3 || b_repeat_first == 3 || b_repeat_second == 3)
	{
		MessageBox(NULL, "Threefold Repetition", "Draw", MB_OK);
		return true;
	}

	// Fifty Move

	if (fifty == 100)
	{
		MessageBox(NULL, "Fifty-move", "Draw", MB_OK);
		return true;
	}
	
	// Stalemate : player on turn	- no legal move		- no checkmate

	Pos* list;
	int length;

	if (color == white)
	{
		list = white_pieces;
		length = white_length;
	}
	else
	{
		list = black_pieces;
		length = black_length;
	}

	for (int i = 0; i < length; i++)
	{
		Pos pos = list[i];
		Type type = (*(Pieces*)pieces[pos.ToNum()]).type;

		switch (type)
		{
		case king:
		{
			KING piece = *(KING*)pieces[pos.ToNum()];
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8) && (pos.y + j >= 0) && (pos.y + j < 8))
					{
						Pos new_pos = Pos(pos.x + i, pos.y + i);
						Color* new_color = new Color;
						if (pieces[new_pos.ToNum()] != (int*)_none)
						{
							new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
						}
						else
						{
							*new_color = invert(color);
						}

						if (!piece.checkValid(pieces, new_pos, *new_color))
						{
							return false;
						}
					}
				}
			}
			break;
		}
		case queen:
		{
			QUEEN piece = *(QUEEN*)pieces[pos.ToNum()];

			for (int i = 0; i < 8; i++)
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			for (int i = 0; i < 8; i++)
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}
			break;
		}
		case bishop:
		{
			BISHOP piece = *(BISHOP*)pieces[pos.ToNum()];

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					Pos new_pos = Pos(pos.x + i, pos.y + i);
					Color* new_color = new Color;
					if (pieces[new_pos.ToNum()] != (int*)_none)
					{
						new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
					}
					else
					{
						*new_color = invert(color);
					}

					if (!piece.checkValid(pieces, new_pos, *new_color))
					{
						return false;
					}
				}
			}
			break;
		}
		case knight:
		{
			KNIGHT piece = *(KNIGHT*)pieces[pos.ToNum()];

			if ((pos.x + 2 < 8) && (pos.y + 1 < 8))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x + 1 < 8) && (pos.y + 2 < 8))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x - 2 >= 0) && (pos.y + 1 < 8))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x - 1 >= 0) && (pos.y + 2 < 8))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x + 2 < 8) && (pos.y - 1 >= 0))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x + 1 < 8) && (pos.y - 2 >= 0))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x - 2 >= 0) && (pos.y - 1 >= 0))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.x - 1 >= 0) && (pos.y - 2 >= 0))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}
			break;
		}
		case rook:
		{
			ROOK piece = *(ROOK*)pieces[pos.ToNum()];

			for (int i = 0; i < 8; i++)
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			for (int i = 0; i < 8; i++)
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}
			break;
		}
		case pawn:
		{
			PAWN piece = *(PAWN*)pieces[pos.ToNum()];

			if ((pos.y + int(piece.color) >= 0) && (pos.y + int(piece.color) < 8))
			{
				Pos new_pos = Pos(pos.x + i, pos.y + i);
				Color* new_color = new Color;
				if (pieces[new_pos.ToNum()] != (int*)_none)
				{
					new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
				}
				else
				{
					*new_color = invert(color);
				}

				if (!piece.checkValid(pieces, new_pos, *new_color))
				{
					return false;
				}
			}

			if ((pos.y + int(piece.color) * 2 >= 0) && (pos.y + int(piece.color) * 2 < 8))
			{
				for (int i = -1; i < 2; i++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8))
					{
						Pos new_pos = Pos(pos.x + i, pos.y + i);
						Color* new_color = new Color;
						if (pieces[new_pos.ToNum()] != (int*)_none)
						{
							new_color = (Color*)((int*)pieces[new_pos.ToNum()] + 3);
						}
						else
						{
							*new_color = invert(color);
						}

						if (!piece.checkValid(pieces, new_pos, *new_color))
						{
							return false;
						}
					}
				}
			}
			break;
		}
		}
	}

	MessageBox(NULL, "Stalemate", "Draw", MB_OK);
	return true;
}

int ChessBoard::CalculatePoint(Color color)
{
	int result = 0;
	for (int i = 0; i < white_length; i++)
	{
		switch (((Pieces*)(pieces[white_pieces[i].ToNum()]))->type)
		{
		default: break;
		case queen: result += 9; break;
		case rook: result += 5; break;
		case bishop: result += 3; break;
		case knight: result += 3; break;
		case pawn: result += 1; break;
		}
	}

	for (int i = 0; i < black_length; i++)
	{
		switch (((Pieces*)(pieces[black_pieces[i].ToNum()]))->type)
		{
		default: break;
		case queen: result -= 9; break;
		case rook: result -= 5; break;
		case bishop: result -= 3; break;
		case knight: result -= 3; break;
		case pawn: result -= 1; break;
		}
	}

	if (color == white)
	{
		if (Check(white))
			result += 100;
		else if (Check(black))
			result -= 100;
	}
	else
	{
		result = 0 - result;
		if (Check(black))
			result += 100;
		else if (Check(white))
			result -= 100;
	}

	return result;
}

int ChessBoard::Minimax_Max(Color color, int total, int count)
{
	int result = -1000;

	int position;

	if (count == total || Checkmate(white) || Checkmate(black))
	{
		return CalculatePoint(color);
	}

	int length;
	Pos* list;
	if (color == white)
	{
		length = white_length;
		list = white_pieces;
	}
	else
	{
		length = black_length;
		list = black_pieces;
	}

	for (int i = 0; i < length; i++)
	{
		Pos pos = list[i];
		Pieces piece = *(Pieces*)pieces[pos.ToNum()];

		switch (piece.type)
		{
		case king:
		{
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8) && (pos.y + j >= 0) && (pos.y + j < 8))
					{
						ChessBoard board = *Copy();
						if (board.move(pos, Pos(pos.x + i, pos.y + j), piece.color))
						{
							int temp = board.Minimax_Min(invert(color), total, count + 1);
							if (temp > result)
							{
								result = temp;
								position = Transform_Pos(pos, Pos(pos.x + i, pos.y + j));
							}
						}
						
					}
				}
			}
			break;
		}
		case queen:
		{
			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(i, pos.y), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(i, pos.y));
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, i), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x, i));
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y + i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y + i));
						}
					}
					
				}
			}
			break;
		}
		case bishop:
		{
			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y + i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Min(invert(color), total, count + 1);
						if (temp > result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y + i));
						}
					}
					
				}
			}
			break;
		}
		case knight:
		{
			if ((pos.x + 2 < 8) && (pos.y + 1 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 2, pos.y + 1), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 2, pos.y + 1));
					}
				}
				
			}

			if ((pos.x + 1 < 8) && (pos.y + 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 1, pos.y + 2), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 1, pos.y + 2));
					}
				}
				
			}

			if ((pos.x - 2 >= 0) && (pos.y + 1 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 2, pos.y + 1), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 2, pos.y + 1));
					}
				}
				
			}

			if ((pos.x - 1 >= 0) && (pos.y + 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 1, pos.y + 2), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 1, pos.y + 2));
					}
				}
				
			}

			if ((pos.x + 2 < 8) && (pos.y - 1 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 2, pos.y - 1), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 2, pos.y - 1));
					}
				}
				
			}

			if ((pos.x + 1 < 8) && (pos.y - 2 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 1, pos.y - 2), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 1, pos.y - 2));
					}
				}
				
			}

			if ((pos.x - 2 >= 0) && (pos.y - 1 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 2, pos.y - 1), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 2, pos.y - 1));
					}
				}
				
			}

			if ((pos.x - 1 >= 0) && (pos.y - 2 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 1, pos.y - 2), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 1, pos.y - 2));
					}
				}
				
			}
			break;
		}
		case rook:
		{
			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(i, pos.y), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(i, pos.y));
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, i), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x, i));
					}
				}
				
			}
			break;
		}
		case pawn:
		{
			if ((pos.y + int(piece.color) * 2 >= 0) && (pos.y + int(piece.color) * 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, pos.y + int(piece.color) * 2), piece.color))
				{
					int temp = board.Minimax_Min(invert(color), total, count + 1);
					if (temp > result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x, pos.y + int(piece.color) * 2));
					}
				}
				
			}

			if ((pos.y + int(piece.color) >= 0) && (pos.y + int(piece.color) < 8))
			{
				for (int i = -1; i < 2; i++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8))
					{
						ChessBoard board = *Copy();
						if (board.move(pos, Pos(pos.x + i, pos.y + int(piece.color)), piece.color))
						{
							int temp = board.Minimax_Min(invert(color), total, count + 1);
							if (temp > result)
							{
								result = temp;
								position = Transform_Pos(pos, Pos(pos.x + i, pos.y + int(piece.color)));
							}
						}
						
					}
				}
			}
			break;
		}
		}
	}

	if (count == 0)
		return position;

	return result;
}

int ChessBoard::Minimax_Min(Color color, int total, int count)
{
	int result = 1000;

	int position;

	if (count == total || Checkmate(white) || Checkmate(black))
	{
		return CalculatePoint(color);
	}

	int length;
	Pos* list;
	if (color == white)
	{
		length = white_length;
		list = white_pieces;
	}
	else
	{
		length = black_length;
		list = black_pieces;
	}

	for (int i = 0; i < length; i++)
	{
		Pos pos = list[i];
		Pieces piece = *(Pieces*)pieces[pos.ToNum()];

		switch (piece.type)
		{
		case king:
		{
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					if ((pos.x + i >= 0) && (pos.x + i < 8) && (pos.y + j >= 0) && (pos.y + j < 8))
					{
						ChessBoard board = *Copy();
						if (board.move(pos, Pos(pos.x + i, pos.y + j), piece.color))
						{
							int temp = board.Minimax_Max(invert(color), total, count + 1);
							if (temp < result)
							{
								result = temp;
								position = Transform_Pos(pos, Pos(pos.x + i, pos.y + j));
							}
						}
						
					}
				}
			}
			break;
		}
		case queen:
		{
			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(i, pos.y), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(i, pos.y));
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, i), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x, i));
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y + i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y + i));
						}
					}
					
				}
			}
			break;
		}
		case bishop:
		{
			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x - i >= 0) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x - i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x - i, pos.y + i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y - i >= 0))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y - i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y - i));
						}
					}
					
				}
			}

			for (int i = 0; i < 8; i++)
			{
				if ((pos.x + i < 8) && (pos.y + i < 8))
				{
					ChessBoard board = *Copy();
					if (board.move(pos, Pos(pos.x + i, pos.y + i), piece.color))
					{
						int temp = board.Minimax_Max(invert(color), total, count + 1);
						if (temp < result)
						{
							result = temp;
							position = Transform_Pos(pos, Pos(pos.x + i, pos.y + i));
						}
					}
					
				}
			}
			break;
		}
		case knight:
		{
			if ((pos.x + 2 < 8) && (pos.y + 1 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 2, pos.y + 1), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 2, pos.y + 1));
					}
				}
				
			}

			if ((pos.x + 1 < 8) && (pos.y + 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 1, pos.y + 2), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 1, pos.y + 2));
					}
				}
				
			}

			if ((pos.x - 2 >= 0) && (pos.y + 1 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 2, pos.y + 1), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 2, pos.y + 1));
					}
				}
				
			}

			if ((pos.x - 1 >= 0) && (pos.y + 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 1, pos.y + 2), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 1, pos.y + 2));
					}
				}
				
			}

			if ((pos.x + 2 < 8) && (pos.y - 1 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 2, pos.y - 1), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 2, pos.y - 1));
					}
				}
				
			}

			if ((pos.x + 1 < 8) && (pos.y - 2 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x + 1, pos.y - 2), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x + 1, pos.y - 2));
					}
				}
				
			}

			if ((pos.x - 2 >= 0) && (pos.y - 1 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 2, pos.y - 1), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 2, pos.y - 1));
					}
				}
				
			}

			if ((pos.x - 1 >= 0) && (pos.y - 2 >= 0))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x - 1, pos.y - 2), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x - 1, pos.y - 2));
					}
				}
				
			}
			break;
		}
		case rook:
		{
			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(i, pos.y), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(i, pos.y));
					}
				}
				
			}

			for (int i = 0; i < 8; i++)
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, i), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x, i));
					}
				}
				
			}
			break;
		}
		case pawn:
		{
			if ((pos.y + int(piece.color) * 2 >= 0) && (pos.y + int(piece.color) * 2 < 8))
			{
				ChessBoard board = *Copy();
				if (board.move(pos, Pos(pos.x, pos.y + int(piece.color) * 2), piece.color))
				{
					int temp = board.Minimax_Max(invert(color), total, count + 1);
					if (temp < result)
					{
						result = temp;
						position = Transform_Pos(pos, Pos(pos.x, pos.y + int(piece.color) * 2));
					}
				}
				
			}

			if ((pos.y + int(piece.color) >= 0) && (pos.y + int(piece.color) < 8))
			{
				for (int i = -1; i < 2; i++)
				{
					if ((pos.x + i <= 0) && (pos.x + i < 8))
					{
						ChessBoard board = *Copy();
						if (board.move(pos, Pos(pos.x + i, pos.y + int(piece.color)), piece.color))
						{
							int temp = board.Minimax_Max(color, total, count + 1);
							if (temp < result)
							{
								result = temp;
								position = Transform_Pos(pos, Pos(pos.x + i, pos.y + int(piece.color)));
							}
						}
					}
				}
			}
			break;
		}
		}
	}

	if (count == 0)
		return position;

	return result;
}

int Transform_Pos(Pos pos1, Pos pos2)
{
	return pos1.x * 1000 + pos1.y * 100 + pos2.x * 10 + pos2.y;
}

std::ostream& operator<<(std::ostream& stream, ChessBoard& chessboard)
{
	int* pieces = (int*)chessboard.getPieces();
	for (int i = 7; i >= 0; i--)
	{
		for (int j = 0; j < 8; j++)
		{
			Type temp = /*pieces[i * 8 + j].type*/ *(Type*)((int*)pieces[i * 8 + j] + 2);
			stream << ((temp != none) && (temp != passing) ? " " : "\0") << (temp != passing ? int(temp) : -1) << ' ';
		}
		stream << std::endl;
	}

	return stream;
}