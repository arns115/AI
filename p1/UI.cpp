#include "UI.h"
#include <iostream>

std::pair<size_t, size_t> UI::ReadMove() {
	std::pair<size_t, size_t> move;
	std::cout << "Choose row number for your move:" << std::endl;
	std::cin >> move.first;
	std::cout << "Choose column number for your move:" << std::endl;
	std::cin >> move.second;

	return move;
}

int UI::ReadDifficulty() {
	int dif;
  std::cout << "What difficulty would you like to play with?" << std::endl;
  std::cout << "1) Easy" << std::endl;
  std::cout << "2) Medium" << std::endl;
  std::cout << "3) Hard" << std::endl;
	std::cin >> dif;

	return dif;
}

int UI::ReadStartingPlayer() {
	int start;
  std::cout << "Who starts?" << std::endl;
  std::cout << "1) You" << std::endl;
  std::cout << "2) Computer" << std::endl;
	std::cin >> start;

	return start;
}


void UI::PrintBoard(int(&state)[5][5]) {
	for (unsigned int row = 1; row <= 4 * m_rowHeight; row++) {
		for (unsigned int col = 1; col < 4 * m_colWidth; col++) {
			char delim = ' ';
			int relativeRow = (row + m_rowHeight - 1) / m_rowHeight;
			int relativeCol = (col + m_colWidth - 1) / m_colWidth;

			// Board characters
			if (col % m_colWidth == 0) delim = '|';
			else if (row % m_rowHeight == 0 && row < 4 * m_rowHeight) delim = '_';

			// Player characters
			else if (state[relativeRow][relativeCol] == 1) {
				if ((row % m_rowHeight == 2 || row % m_rowHeight == 4)
					&& col % m_colWidth >= 4 && col % m_colWidth <= 6) delim = 'O';
				else if (row % m_rowHeight == 3
					&& (col % m_colWidth == 3 || col % m_colWidth == 7)) delim = 'O';
			}
			else if (state[relativeRow][relativeCol] == 2) {
				if (col % m_colWidth == 4) {
					if (row % m_rowHeight == 2) delim = '\\';
					else if (row % m_rowHeight == 4) delim = '/';
				}
				else if (col % m_colWidth == 6) {
					if (row % m_rowHeight == 2) delim = '/';
					else if (row % m_rowHeight == 4) delim = '\\';
				}
				else if (col % m_colWidth == 5 && row % m_rowHeight == 3) delim = '\\';
			}

			std::cout << delim;

		}
		std::cout << '\n';
	}
}