#include "Game.h"

void Game::setChessBoard(ChessBoard* chessboard)
{
	m_ChessBoard = chessboard;
}

ChessBoard* Game::getChessBoard()
{
	return m_ChessBoard;
}

void Game::setMode(Mode mode)
{
	m_Mode = mode;
}

Mode Game::getMode()
{
	return m_Mode;
}

void Game::setValue(int value)
{
	m_Value = value;
}

int Game::getValue()
{
	return m_Value;
}

void Game::setWin(bool win)
{
	m_Win = win;
}

bool Game::getWin()
{
	return m_Win;
}

void Game::setDraw(bool draw)
{
	m_Draw = draw;
}

bool Game::getDraw()
{
	return m_Draw;
}

void Game::setPos(Pos pos)
{
	m_Pos = pos;
}

Pos Game::getPos()
{
	return m_Pos;
}

bool Game::Update_Move(Pos pos)
{
	if (m_ChessBoard->start_pos == m_ChessBoard->NULL_POS)
	{
		Pieces piece = *(Pieces*)(((int*)(m_ChessBoard->getPieces()))[pos.ToNum()]);
		if (piece.type != none && piece.type != passing && piece.color == m_ChessBoard->color)
		{
			m_ChessBoard->start_pos = pos;
			return false;
		}
	}
	else
	{
		if (m_ChessBoard->start_pos == pos)
		{
			m_ChessBoard->start_pos = m_ChessBoard->NULL_POS;
			return false;
		}
		else
		{
			int* list = (int*)m_ChessBoard->getPieces();
			Pieces piece = *(Pieces*)(list[m_ChessBoard->start_pos.ToNum()]);
			m_ChessBoard->end_pos = pos;
			if (m_ChessBoard->move(m_ChessBoard->start_pos, m_ChessBoard->end_pos, m_ChessBoard->color))
			{
				if (m_ChessBoard->color == white && piece.type == pawn)
				{
					if (pos.y == 7)
					{
						setPos(pos);
						setMode(PROM);
					}
				}
				else if (piece.type == pawn)
				{
					if (pos.y == 0)
					{
						setPos(pos);
						setMode(PROM);
					}
				}
				m_ChessBoard->UpdateRepeat(m_ChessBoard->color);
				m_ChessBoard->UpdateFifty();
				if (m_ChessBoard->IsDraw(m_ChessBoard->color))
					Game::setDraw(false);
				if (m_ChessBoard->Checkmate(invert(m_ChessBoard->color)))
				{
					Game::setWin(true);
					invert(&m_ChessBoard->color);
				}
				if (m_ChessBoard->color == black)
					m_ChessBoard->FlipTurn();
				invert(&m_ChessBoard->color);
			}
			return true;
		}
		return false;
	}
}

void Game::ResetValues()
{
	m_ChessBoard->start_pos = m_ChessBoard->NULL_POS;
	m_ChessBoard->castling = false;
	m_ChessBoard->captured_type = none;
}

void Game::Force_Move(Pos start_pos, Pos end_pos)
{
	int* pieces = (int*)m_ChessBoard->getPieces();
	int temp = pieces[start_pos.ToNum()];
	pieces[start_pos.ToNum()] = pieces[end_pos.ToNum()];
	pieces[end_pos.ToNum()] = temp;
}

void Game::AddPiece(Type type, Color color, Pos pos)
{
	int* pieces = (int*)m_ChessBoard->getPieces();
	switch (type)
	{
	case queen: pieces[pos.ToNum()] = (int)(new QUEEN(pos, color)); break;
	case bishop: pieces[pos.ToNum()] = (int)(new BISHOP(pos, color)); break;
	case knight: pieces[pos.ToNum()] = (int)(new KNIGHT(pos, color)); break;
	case rook: pieces[pos.ToNum()] = (int)(new ROOK(pos, color)); break;
	case pawn: pieces[pos.ToNum()] = (int)(new PAWN(pos, color)); break;
	default: break;
	}
}

void Game::RemovePiece(Pos pos)
{
	int* pieces = (int*)m_ChessBoard->getPieces();
	pieces[pos.ToNum()] = (int)nullptr;
}