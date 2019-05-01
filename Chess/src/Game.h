#pragma once

#include "deco.h"
#include "Chessboard.h"

class Game
{
	static ChessBoard* m_ChessBoard;
	static Mode m_Mode;
	static int m_Value;
	static bool m_Win;
	static bool m_Draw;
	static Pos m_Pos;
public:
	static void setChessBoard(ChessBoard* chessboard);
	static ChessBoard* getChessBoard();
	static void setMode(Mode mode);
	static void setValue(int value);
	static void setWin(bool win);
	static void setDraw(bool draw);
	static void setPos(Pos pos);
	static Mode getMode();
	static int getValue();
	static bool getWin();
	static bool getDraw();
	static Pos getPos();
	static bool Update_Move(Pos pos);

	static void ResetValues();
	static void Force_Move(Pos start_pos, Pos end_pos);
	static void AddPiece(Type type, Color color, Pos pos);
	static void RemovePiece(Pos pos);
};