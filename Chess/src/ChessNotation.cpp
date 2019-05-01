#include "ChessNotation.h"

bool ChessNotation::ReadFromFile()
{
	length = -1;
	std::ifstream infile;
	std::string line;
	infile.open("Input.txt");
	while (std::getline(infile, line))
	{
		length += 1;
		list[length] = new char[line.length() + 1];
		strcpy_s(list[length], line.length() + 1, line.c_str());
		list_length[length] = line.length();
	}
	MAX = length;
	for (int i = 0; i <= MAX; i++)
	{
		int j = 0;
		if (list[i][j] >= 'B' && list[i][j] <= 'R')
			j += 1;

		if (list[i][j] >= 'a' && list[i][j] <= 'h')
		{
			Pos start_pos = Pos(int(list[i][j]) - int('a'), int(list[i][j + 1]) - int('1'));
			Game::Update_Move(start_pos);
			Pos end_pos = Pos(int(list[i][j + 2]) - int('a'), int(list[i][j + 3]) - int('1'));
			if (!Game::Update_Move(end_pos))
			{
				Game::ResetValues();
				return false;
			}
			Game::ResetValues();
		}
		else
		{
			if (i % 2 == 0)
			{
				if (line[i + 3] == '-')
				{
					Game::Update_Move(Pos(4, 0));
					if (!Game::Update_Move(Pos(2, 0)))
					{
						Game::ResetValues();
						return false;
					}
					Game::ResetValues();
				}
				else
				{
					Game::Update_Move(Pos(4, 0));
					if (!Game::Update_Move(Pos(6, 0)))
					{
						Game::ResetValues();
						return false;
					}
					Game::ResetValues();
				}
			}
			else
			{
				if (line[i + 3] == '-')
				{
					Game::Update_Move(Pos(4, 7));
					if (!Game::Update_Move(Pos(2, 7)))
					{
						Game::ResetValues();
						return false;
					}
					Game::ResetValues();
				}
				else
				{
					Game::Update_Move(Pos(4, 7));
					if (!Game::Update_Move(Pos(6, 7)))
					{
						Game::ResetValues();
						return false;
					}
					Game::ResetValues();
				}
			}
		}
	}
	return true;
}

void ChessNotation::ReadIn(Pos start, Pos end, bool castling, Type capture)
{
	if (end == Game::getChessBoard()->NULL_POS)
		return;

	std::string str;
	int i = 0;

	switch (capture)
	{
		case none: break;
		case king: break;
		case queen: str += 'Q';
		case bishop: str += 'B'; break;
		case knight: str += 'K'; break;
		case rook: str += 'R'; break;
		case pawn: str += 'P'; break;
		default: break;
	}

	if (castling)
	{
		if (start.x > end.x)
		{
			str += "0-0";
		}
		else
		{
			str += "0-0-0";
		}
	}
	else
	{
		str += (char)(int('a') + start.x);
		str += (char)(int('1') + start.y);
		str += (char)(int('a') + end.x);
		str += (char)(int('1') + end.y);
	}

	list[length] = new char[str.length() + 1];
	strcpy_s(list[length], str.length() + 1, str.c_str());
	list_length[length] = str.length();

	length += 1;
	if (length > MAX)
	{
		MAX = length;
	}
}

void ChessNotation::backward()
{
	if (length == 0)
		return;

	Pos start_pos;
	Pos end_pos;
	Type capture = none;

	std::string line = list[length - 1];

	int i = 0;

	switch (line[i])
	{
	case 'Q': capture = queen; i++; break;
	case 'B': capture = bishop; i++; break;
	case 'K': capture = knight; i++; break;
	case 'R': capture = rook; i++; break;
	case 'P': capture = pawn; i++; break;
	}

	if (line[i] >= 'a' && line[i] <= 'h')
	{
		start_pos = Pos(int(line[i]) - int('a'), int(line[i + 1]) - int('1'));
		end_pos = Pos(int(line[i + 2]) - int('a'), int(line[i + 3]) - int('1'));
		Game::Force_Move(end_pos, start_pos);
	}
	else
	{
		if ((length - 1) % 2 == 0)
		{
			if (line[i + 3] == '-')
			{
				start_pos = Pos(4, 0);
				end_pos = Pos(2, 0);
				Game::Force_Move(end_pos, start_pos);
				start_pos = Pos(0, 0);
				end_pos = Pos(3, 0);
				Game::Force_Move(end_pos, start_pos);
			}
			else
			{
				start_pos = Pos(4, 0);
				end_pos = Pos(6, 0);
				Game::Force_Move(end_pos, start_pos);
				start_pos = Pos(7, 0);
				end_pos = Pos(5, 0);
				Game::Force_Move(end_pos, start_pos);
			}
		}
		else
		{
			if (line[i + 3] == '-')
			{
				start_pos = Pos(4, 7);
				end_pos = Pos(2, 7);
				Game::Force_Move(end_pos, start_pos);
				start_pos = Pos(0, 7);
				end_pos = Pos(3, 7);
				Game::Force_Move(end_pos, start_pos);
			}
			else
			{
				start_pos = Pos(4, 7);
				end_pos = Pos(6, 7);
				Game::Force_Move(end_pos, start_pos);
				start_pos = Pos(7, 7);
				end_pos = Pos(5, 7);
				Game::Force_Move(end_pos, start_pos);
			}
		}
	}

	if (capture != none)
	{
		if (length % 2 == 0)
			Game::AddPiece(capture, white, end_pos);
		else
			Game::AddPiece(capture, black, end_pos);
	}

	length -= 1;
}

void ChessNotation::forward()
{
	if (length == MAX)
		return;

	Pos start_pos;
	Pos end_pos;
	Type capture = none;

	std::string line = list[length + 1];

	int i = 0;

	switch (line[i])
	{
	case 'Q': capture = queen; i++; break;
	case 'B': capture = bishop; i++; break;
	case 'K': capture = knight; i++; break;
	case 'R': capture = rook; i++; break;
	case 'P': capture = pawn; i++; break;
	}

	if (line[i] >= 'a' && line[i] <= 'h')
	{
		start_pos = Pos(int(line[i]) - int('a'), int(line[i + 1]) - int('0'));
		end_pos = Pos(int(line[i + 2]) - int('a'), int(line[i + 3]) - int('0'));
		Game::Force_Move(start_pos, end_pos);
	}
	else
	{
		if ((length + 1) % 2 == 0)
		{
			if (line[i + 3] == '-')
			{
				start_pos = Pos(4, 0);
				end_pos = Pos(2, 0);
				Game::Force_Move(start_pos, end_pos);
				start_pos = Pos(0, 0);
				end_pos = Pos(3, 0);
				Game::Force_Move(start_pos, end_pos);
			}
			else
			{
				start_pos = Pos(4, 0);
				end_pos = Pos(6, 0);
				Game::Force_Move(start_pos, end_pos);
				start_pos = Pos(7, 0);
				end_pos = Pos(5, 0);
				Game::Force_Move(start_pos, end_pos);
			}
		}
		else
		{
			if (line[i + 3] == '-')
			{
				start_pos = Pos(4, 7);
				end_pos = Pos(2, 7);
				Game::Force_Move(start_pos, end_pos);
				start_pos = Pos(0, 7);
				end_pos = Pos(3, 7);
				Game::Force_Move(start_pos, end_pos);
			}
			else
			{
				start_pos = Pos(4, 7);
				end_pos = Pos(6, 7);
				Game::Force_Move(start_pos, end_pos);
				start_pos = Pos(7, 7);
				end_pos = Pos(5, 7);
				Game::Force_Move(start_pos, end_pos);
			}
		}
	}

	if (capture != none)
	{
		Game::RemovePiece(start_pos);
	}

	length += 1;
}

void ChessNotation::WriteOutFile()
{
	std::ofstream outfile;
	outfile.open("Output.txt");
	for (int i = 0; i < MAX; i++)
	{
		outfile << list[i] << std::endl;
	}
	outfile.close();
}

void ChessNotation::clear()
{
	for (int i = 0; i < MAX; i++)
	{
		delete[] list[i];
	}
	length = 0;
	MAX = 0;
}