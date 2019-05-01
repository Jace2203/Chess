#pragma once

#include <iostream>

#include "Pieces.h"

class ChessBoard
{
private:
	bool turn;

	Pos* white_pieces;
	Pos* black_pieces;
	int white_length;
	int black_length;
	Pos passant[2];
	int* pieces[64];

	Type* white_type_repeat_first = new Type[64];
	Color* white_color_repeat_first = new Color[64];
	Type* white_type_repeat_second = new Type[64];
	Color* white_color_repeat_second = new Color[64];
	int w_repeat_first;
	int w_repeat_second;
	Type* black_type_repeat_first = new Type[64];
	Color* black_color_repeat_first = new Color[64];
	Type* black_type_repeat_second = new Type[64];
	Color* black_color_repeat_second = new Color[64];
	int b_repeat_first;
	int b_repeat_second;

	int fifty = 0;
	Type last_moved;
	bool captured;

public:
	Pos NULL_POS = Pos(-1, -1);

	Pos start_pos;
	Pos end_pos;
	Type captured_type;
	bool castling;

	Color color;

	ChessBoard() = default;
	~ChessBoard();
	void init();
	ChessBoard* Copy();
	void CopyPieces(Color color);
	void FlipTurn() { turn = !turn; }
	
	void p_move(Pos pos, Pos new_pos);
	bool move(Pos pos, Pos new_pos, Color color);

	void* getPieces() { return pieces; }

	void UpdatePassant();

	void RemovePiece(Color color, Pos pos);

	Pos FindKing(Color color);
	bool Check(Color color);
	bool Checkmate(Color color);
	void Promotion(Pos pos, Type type);
	void UpdateRepeat(Color color);
	void UpdateFifty();
	bool IsDraw(Color color);

	int CalculatePoint(Color color);

	int Minimax_Max(Color color,  int total, int count = 0);
	int Minimax_Min(Color color,  int total, int count = 0);
};

int Transform_Pos(Pos pos1, Pos pos2);
std::ostream& operator<<(std::ostream& stream, ChessBoard& chessboard);