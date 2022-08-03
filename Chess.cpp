//Ben Bielin, Ethan Lee, Alexander Hu, Tyler Ngo
//Chess.cpp
//This program is the C++ final project, it runs a simple chess program between 2 players
//1/21/2020

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Board
{
private:

	string piece;
	int row;
	int column;
	bool moved;

public:

	Board(string p, int r, int c)
	{
		piece = p;
		row = r;
		column = c;
		moved = false;
	}

	Board(int r, int c)
	{
		piece = " ";
		moved = true;
		row = r;
		column = c;
	}

	Board()
	{
		piece = " ";
		moved = true;
		row = -1;
		column = -1;
	}

	void set_piece(string p)
	{
		piece = p;
	}

	void set_row(int x)
	{
		row = x;
	}
	void set_column(int y)
	{
		column = y;
	}

	void set_moved(bool m)
	{
		moved = m;
	}

	string get_piece()
	{
		return piece;
	}

	int get_row()
	{
		return row;
	}

	int get_column()
	{
		return column;
	}

	bool get_moved()
	{
		return moved;
	}
};

Board square[8][8];

void set_up_board()
{

	square[0][0] = Board("r", 0, 0);
	square[0][1] = Board("n", 0, 1);
	square[0][2] = Board("b", 0, 2);
	square[0][3] = Board("q", 0, 3);
	square[0][4] = Board("k", 0, 4);
	square[0][5] = Board("b", 0, 5);
	square[0][6] = Board("n", 0, 6);
	square[0][7] = Board("r", 0, 7);

	// black pawns
	for (int i = 0; i < 8; i++)
	{
		square[1][i] = Board("p", 1, i);
	}

	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			square[i][j] = Board(i, j);
		}
	}
	// white pawns
	for (int i = 0; i < 8; i++)
	{
		square[6][i] = Board("P", 6, i);
	}

	square[7][0] = Board("R", 0, 0);
	square[7][1] = Board("N", 0, 1);
	square[7][2] = Board("B", 0, 2);
	square[7][3] = Board("Q", 0, 3);
	square[7][4] = Board("K", 0, 4);
	square[7][5] = Board("B", 0, 5);
	square[7][6] = Board("N", 0, 6);
	square[7][7] = Board("R", 0, 7);
}

void print_board(bool white)
{
	if (white)
	{
		cout << "   -------------------------------    " << endl;
		for (int i = 0; i < 7; i++)
		{
			int i_prime = 8 - i;
			cout << i_prime;
			cout << " | ";
			for (int j = 0; j < 8; j++)
			{
				cout << square[i][j].get_piece() + " | ";
			}
			cout << "\n";
			cout << "   -------------------------------    " << endl;
		}
		cout << "1 | ";
		for (int i = 0; i < 8; i++)
		{
			cout << square[7][i].get_piece() + " | ";
		}
		cout << endl;
		cout << "   -------------------------------   " << endl;
		cout << "    a   b   c   d   e   f   g   h    " << endl;
	}
	else
	{
		cout << "   ------------------------------- " << endl;
		for (int i = 0; i < 7; i++)
		{
			int i_prime = i + 1;
			cout << i_prime;
			cout << " | ";
			for (int j = 0; j < 8; j++)
			{
				cout << square[7 - i][7 - j].get_piece() + " | ";
			}
			cout << "\n";
			cout << "   -------------------------------    " << endl;
		}
		cout << "8 | ";
		for (int i = 0; i < 8; i++)
		{
			cout << square[0][7 - i].get_piece() + " | ";
		}
		cout << endl;
		cout << "   ------------------------------- " << endl;
		cout << "    h   g   f   e   d   c   b   a  " << endl;
	}
}

int convert_letter(bool white, string letter)
{
	if (letter == "a")
	{
		return 0;
	}
	else if (letter == "b")
	{
		return 1;
	}
	else if (letter == "c")
	{
		return 2;
	}
	else if (letter == "d")
	{
		return 3;
	}
	else if (letter == "e")
	{
		return 4;
	}
	else if (letter == "f")
	{
		return 5;
	}
	else if (letter == "g")
	{
		return 6;
	}
	else if (letter == "h")
	{
		return 7;
	}
	else
	{
		return -1;
	}
}

void update_board(int start_letter, int start_number, int end_letter, int end_number)
{
	square[end_number][end_letter].set_piece(square[start_number][start_letter].get_piece());
	square[start_number][start_letter].set_piece(" ");
}

string find_king(bool white)
{
	int a, b;
	bool stop = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (white)
			{
				if (square[i][j].get_piece() == "K")
				{
					a = i;
					b = j;
					stop = true;
					break;
				}
			}
			else
			{
				if (square[i][j].get_piece() == "k")
				{
					a = i;
					b = j;
					stop = true;
					break;
				}
			}
		}
		if (stop)
		{
			break;
		}
	}
	return to_string(a) + to_string(b);
}

bool check_path_clear(int start_letter, int start_number, int end_letter, int end_number)
{
	int path_start_number, paired_start_letter;
	if (fmin(start_number, end_number) == start_number)
	{
		path_start_number = start_number;
		paired_start_letter = start_letter;
	}
	else
	{
		path_start_number = end_number;
		paired_start_letter = end_letter;
	}
	int path_length_number = abs(start_number - end_number);
	int path_start_letter = fmin(start_letter, end_letter);
	int path_length_letter = abs(start_letter - end_letter);
	if (path_length_number == 0)
	{
		for (int i = path_start_letter + 1; i < path_start_letter + path_length_letter; i++)
		{
			if (square[path_start_number][i].get_piece() != " ")
			{
				return false;
			}
		}
	}
	else if (path_length_letter == 0)
	{
		for (int i = path_start_number + 1; i < path_start_number + path_length_number; i++)
		{
			if (square[i][path_start_letter].get_piece() != " ")
			{
				return false;
			}
		}
	}
	else
	{
		for (int i = path_start_number + 1; i < path_start_number + path_length_number; i++)
		{
			for (int j = path_start_letter + 1; j < path_start_letter + path_length_letter; j++)
			{
				if (i - path_start_number == abs(j - paired_start_letter))
				{
					if (square[i][j].get_piece() != " ")
					{
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool check_move(bool white, std::string input, int start_letter, int start_number, int end_letter, int end_number)
{
	if (white)
	{
		if (square[start_number][start_letter].get_piece() == "P" && input.substr(0, 1) == "P")
		{
			if (square[end_number][start_letter].get_piece() == " ")
			{
				if (start_letter == end_letter)
				{
					if (start_number - end_number == 1)
					{
						return true;
					}
					else if (start_number - end_number == 2 && square[start_number][start_letter].get_moved() == false)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
			}
			else if (square[end_number][end_letter].get_piece() == "p"
				|| square[end_number][end_letter].get_piece() == "r"
				|| square[end_number][end_letter].get_piece() == "n"
				|| square[end_number][end_letter].get_piece() == "b"
				|| square[end_number][end_letter].get_piece() == "q"
				|| square[end_number][end_letter].get_piece() == "k")
			{
				if (start_number - end_number == 1)
				{
					if (start_letter - end_letter == -1 || start_letter - end_letter == 1)
					{
						return true;
					}
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "R" && input.substr(0, 1) == "R")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "p"
				|| square[end_number][end_letter].get_piece() == "r"
				|| square[end_number][end_letter].get_piece() == "n"
				|| square[end_number][end_letter].get_piece() == "b"
				|| square[end_number][end_letter].get_piece() == "q"
				|| square[end_number][end_letter].get_piece() == "k")
			{
				if (start_number == end_number)
				{
					if (start_letter != end_letter)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
				else if (start_letter == end_letter)
				{
					return check_path_clear(start_letter, start_number, end_letter, end_number);
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "N" && input.substr(0, 1) == "N")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "p"
				|| square[end_number][end_letter].get_piece() == "r"
				|| square[end_number][end_letter].get_piece() == "n"
				|| square[end_number][end_letter].get_piece() == "b"
				|| square[end_number][end_letter].get_piece() == "q"
				|| square[end_number][end_letter].get_piece() == "k")
			{
				if ((abs(start_number - end_number) == 1 && abs(start_letter - end_letter) == 2)
					|| (abs(start_number - end_number) == 2 && abs(start_letter - end_letter) == 1))
				{
					return true;
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "B" && input.substr(0, 1) == "B")
		{
			if (square[end_number][end_letter].get_piece() == " " ||
				square[end_number][end_letter].get_piece() == "p"
				|| square[end_number][end_letter].get_piece() == "r"
				|| square[end_number][end_letter].get_piece() == "n"
				|| square[end_number][end_letter].get_piece() == "b"
				|| square[end_number][end_letter].get_piece() == "q"
				|| square[end_number][end_letter].get_piece() == "k")
			{
				if (abs(start_number - end_number) == abs(start_letter - end_letter))
				{
					if (start_number != end_number)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "Q" && input.substr(0, 1) == "Q")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "p"
				|| square[end_number][end_letter].get_piece() == "r"
				|| square[end_number][end_letter].get_piece() == "n"
				|| square[end_number][end_letter].get_piece() == "b"
				|| square[end_number][end_letter].get_piece() == "q"
				|| square[end_number][end_letter].get_piece() == "k")
			{
				if (start_number == end_number)
				{
					if (start_letter != end_letter)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
				else if (start_letter == end_letter)
				{
					return check_path_clear(start_letter, start_number, end_letter, end_number);
				}
				else if (abs(start_number - end_number) == abs(start_letter - end_letter))
				{
					if (start_number != end_number)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "K" && input.substr(0, 1) == "K")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "p"
				|| square[end_number][end_letter].get_piece() == "r"
				|| square[end_number][end_letter].get_piece() == "n"
				|| square[end_number][end_letter].get_piece() == "b"
				|| square[end_number][end_letter].get_piece() == "q"
				|| square[end_number][end_letter].get_piece() == "k")
			{
				if ((abs(start_number - end_number) == 0 || abs(start_number - end_number) == 1)
					&& (abs(start_letter - end_letter) == 0 || abs(start_letter - end_letter) == 1))
				{
					if (start_number != end_number)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	else
	{
		if (square[start_number][start_letter].get_piece() == "p" && input.substr(0, 1) == "p")
		{
			if (square[end_number][end_letter].get_piece() == " ")
			{
				if (start_letter == end_letter)
				{
					if (start_number - end_number == -1)
					{
						return true;
					}
					else if (start_number - end_number == -2 && square[start_number][start_letter].get_moved() == false)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
			}
			else if (square[end_number][end_letter].get_piece() == "P"
				|| square[end_number][end_letter].get_piece() == "R"
				|| square[end_number][end_letter].get_piece() == "N"
				|| square[end_number][end_letter].get_piece() == "B"
				|| square[end_number][end_letter].get_piece() == "Q"
				|| square[end_number][end_letter].get_piece() == "K")
			{
				if (start_number - end_number == -1)
				{
					if (start_letter - end_letter == -1 || start_letter - end_letter == 1)
					{
						return true;
					}
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "r" && input.substr(0, 1) == "r")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "P"
				|| square[end_number][end_letter].get_piece() == "R"
				|| square[end_number][end_letter].get_piece() == "N"
				|| square[end_number][end_letter].get_piece() == "B"
				|| square[end_number][end_letter].get_piece() == "Q"
				|| square[end_number][end_letter].get_piece() == "K")
			{
				if (start_number == end_number)
				{
					if (start_letter != end_letter)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
				else if (start_letter == end_letter)
				{
					return check_path_clear(start_letter, start_number, end_letter, end_number);
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "n" && input.substr(0, 1) == "n")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "P"
				|| square[end_number][end_letter].get_piece() == "R"
				|| square[end_number][end_letter].get_piece() == "N"
				|| square[end_number][end_letter].get_piece() == "B"
				|| square[end_number][end_letter].get_piece() == "Q"
				|| square[end_number][end_letter].get_piece() == "K")
			{
				if ((abs(start_number - end_number) == 1 && abs(start_letter - end_letter) == 2)
					|| (abs(start_number - end_number) == 2 && abs(start_letter - end_letter) == 1))
				{
					return true;
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "b" && input.substr(0, 1) == "b")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "P"
				|| square[end_number][end_letter].get_piece() == "R"
				|| square[end_number][end_letter].get_piece() == "N"
				|| square[end_number][end_letter].get_piece() == "B"
				|| square[end_number][end_letter].get_piece() == "Q"
				|| square[end_number][end_letter].get_piece() == "K")
			{
				if (abs(start_number - end_number) == abs(start_letter - end_letter))
				{
					if (start_number != end_number)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "q" && input.substr(0, 1) == "q")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "P"
				|| square[end_number][end_letter].get_piece() == "R"
				|| square[end_number][end_letter].get_piece() == "N"
				|| square[end_number][end_letter].get_piece() == "B"
				|| square[end_number][end_letter].get_piece() == "Q"
				|| square[end_number][end_letter].get_piece() == "K")
			{
				if (start_number == end_number)
				{
					if (start_letter != end_letter)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
				else if (start_letter == end_letter)
				{
					return check_path_clear(start_letter, start_number, end_letter, end_number);
				}
				else if (abs(start_number - end_number) == abs(start_letter - end_letter))
				{
					if (start_number != end_number)
					{
						return check_path_clear(start_letter, start_number, end_letter, end_number);
					}
				}
			}
		}
		else if (square[start_number][start_letter].get_piece() == "k" && input.substr(0, 1) == "k")
		{
			if (square[end_number][end_letter].get_piece() == " " || square[end_number][end_letter].get_piece() == "P"
				|| square[end_number][end_letter].get_piece() == "R"
				|| square[end_number][end_letter].get_piece() == "N"
				|| square[end_number][end_letter].get_piece() == "B"
				|| square[end_number][end_letter].get_piece() == "Q"
				|| square[end_number][end_letter].get_piece() == "K")
			{
				if ((abs(start_number - end_number) == 0 || abs(start_number - end_number) == 1)
					&& (abs(start_letter - end_letter) == 0 || abs(start_letter - end_letter) == 1))
				{
					if (start_number != end_number)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
}

string check(bool white, int king2, int king1)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (check_move(!white, square[i][j].get_piece(), j, i, king2, king1))
			{
				return to_string(i) + to_string(j);
			}
		}
	}
	return "false";
}

bool checkmate(bool white)
{
	string king = find_king(white);
	int king1 = stoi(king.substr(0, 1));
	int king2 = stoi(king.substr(1, 1));
	string checking = check(white, king2, king1);
	if (checking != "false")
	{
		int checking1 = stoi(checking.substr(0, 1));
		int checking2 = stoi(checking.substr(1, 1));
		if (king2 != 7 && king1 != 0)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2 + 1, king1 - 1))
			{
				if (check(white, king2 + 1, king1 - 1) == "false")
				{
					return false;
				}
			}
		}
		if (king2 != 7 && king1 != 7)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2 + 1, king1 + 1))
			{
				if (check(white, king2 + 1, king1 + 1) == "false")
				{
					return false;
				}
			}
		}
		if (king2 != 7)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2 + 1, king1))
			{
				if (check(white, king2 + 1, king1) == "false")
				{
					return false;
				}
			}
		}
		if (king2 != 0 && king1 != 7)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2 - 1, king1 + 1))
			{
				if (check(white, king2 - 1, king1 + 1) == "false")
				{
					return false;
				}
			}
		}
		if (king2 != 0 && king1 != 0)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2 - 1, king1 - 1))
			{
				if (check(white, king2 - 1, king1 - 1) == "false")
				{
					return false;
				}
			}
		}
		if (king2 != 0)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2 - 1, king1))
			{
				if (check(white, king2 - 1, king1) == "false")
				{
					return false;
				}
			}
		}
		if (king1 != 7)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2, king1 + 1))
			{
				if (check(white, king2, king1 + 1) == "false")
				{
					return false;
				}
			}
		}
		if (king1 != 0)
		{
			if (check_move(white, square[king1][king2].get_piece(), king2, king1, king2, king1 - 1))
			{
				if (check(white, king2, king1 - 1) == "false")
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

int main()
{
	using namespace std;
	bool white = true;
	string input;
	int start_letter;
	int start_number;
	int end_letter;
	int end_number;
	set_up_board();
	while (true)
	{
		print_board(white);
		if (white)
		{
			if (checkmate(white))
			{
				std::cout << "Checkmate, black wins" << endl;
				break;
			}
			std::cout << "White's turn" << endl;
			std::cout << "Enter the symbol of the piece you want to move followed by" << endl;
			std::cout << "the coordinate pair of the piece you want to move and a dash," << endl;
			std::cout << "then the coordinate pair of the square you want to move to" << endl;
			std::cout << "Ex." << endl;
			std::cout << "Pe2-e4" << endl;
			std::cout << "If you need help, type \"help\"" << endl;
			while (true)
			{
				cin >> input;
				if (input == "help")
				{
					while (true)
					{
						std::cout << "King can move exactly one square horizontally, vertically, or diagonally. " << endl;
						std::cout << "Queen can move any number of vacant squares diagonally, horizontally, or vertically." << endl;
						std::cout << "Rook can move any number of vacant squares vertically or horizontally. It also is moved while castling." << endl;
						std::cout << "Bishop can move any number of vacant squares in any diagonal direction." << endl;
						std::cout << "Knight can move one square along any rank or file and then at an angle." << endl;
						std::cout << "The knight´s movement can also be viewed as an \"L\" or \"7\" laid out at any horizontal or vertical angle." << endl;
						std::cout << "Pawns can move forward one square, if that square is unoccupied." << endl;
						std::cout << "If it has not yet moved, the pawn has the option of moving two squares forward" << endl;
						std::cout << "provided both squares in front of the pawn are unoccupied." << endl;
						std::cout << "A pawn cannot move backward.Pawns are the only pieces that capture differently from how they move." << endl;
						std::cout << "They can capture an enemy piece on either of the two spaces adjacent to the space in front of them" << endl;
						std::cout << "(i.e., the two squares diagonally in front of them) but cannot move to these spaces if they are vacant." << endl;
						std::cout << "The pawn is also involved in the two special moves en passantand promotion." << endl;
						std::cout << "Type \"done\" when you are ready to make your move" << endl;
						cin >> input;
						if (input == "done")
						{
							break;
						}
					}
					print_board(white);
					std::cout << "Please input your move" << endl;
				}
				else
				{
					start_letter = convert_letter(white, input.substr(1, 1));
					start_number = 8 - stoi(input.substr(2, 1));
					end_letter = convert_letter(white, input.substr(4, 1));
					end_number = 8 - stoi(input.substr(5, 1));
					if (start_number != -1 && end_number != -1)
					{
						if (check_move(white, input, start_letter, start_number, end_letter, end_number))
						{
							update_board(start_letter, start_number, end_letter, end_number);
							white = false;
							break;
						}
						else
						{
							print_board(white);
							cout << "Illegal move, input move again" << endl;
						}
					}
				}
			}
			white = false;
		}
		else
		{
			if (checkmate(white))
			{
				cout << "Checkmate, white wins" << endl;
				break;
			}
			std::cout << "Black's turn" << endl;
			std::cout << "Enter the symbol of the piece you want to move followed by" << endl;
			std::cout << "the coordinate pair of the piece you want to move and a dash," << endl;
			std::cout << "then the coordinate pair of the square you want to move to" << endl;
			std::cout << "Ex." << endl;
			std::cout << "pe7-e5" << endl;
			std::cout << "If you need help, type \"help\"" << endl;
			while (true)
			{
				cin >> input;
				if (input == "help")
				{
					while (true)
					{
						std::cout << "King can move exactly one square horizontally, vertically, or diagonally. " << endl;
						std::cout << "Queen can move any number of vacant squares diagonally, horizontally, or vertically." << endl;
						std::cout << "Rook can move any number of vacant squares vertically or horizontally. It also is moved while castling." << endl;
						std::cout << "Bishop can move any number of vacant squares in any diagonal direction." << endl;
						std::cout << "Knight can move one square along any rank or file and then at an angle." << endl;
						std::cout << "The knight´s movement can also be viewed as an \"L\" or \"7\" laid out at any horizontal or vertical angle." << endl;
						std::cout << "Pawns can move forward one square, if that square is unoccupied." << endl;
						std::cout << "If it has not yet moved, the pawn has the option of moving two squares forward" << endl;
						std::cout << "provided both squares in front of the pawn are unoccupied." << endl;
						std::cout << "A pawn cannot move backward.Pawns are the only pieces that capture differently from how they move." << endl;
						std::cout << "They can capture an enemy piece on either of the two spaces adjacent to the space in front of them" << endl;
						std::cout << "(i.e., the two squares diagonally in front of them) but cannot move to these spaces if they are vacant." << endl;
						std::cout << "The pawn is also involved in the two special moves en passantand promotion." << endl;
						std::cout << "Type \"done\" when you are ready to make your move" << endl;
						cin >> input;
						if (input == "done")
						{
							break;
						}
					}
					print_board(white);
					std::cout << "Please input your move" << endl;
				}
				else
				{
					start_letter = convert_letter(white, input.substr(1, 1));
					start_number = 8 - stoi(input.substr(2, 1));
					end_letter = convert_letter(white, input.substr(4, 1));
					end_number = 8 - stoi(input.substr(5, 1));
					if (start_number != -1 && end_number != -1)
					{
						if (check_move(white, input, start_letter, start_number, end_letter, end_number))
						{
							update_board(start_letter, start_number, end_letter, end_number);
							white = true;
							break;
						}
						else
						{
							print_board(white);
							cout << "Illegal move, input move again" << endl;
						}
					}
				}
			}
			white = true;
		}
	}
}
