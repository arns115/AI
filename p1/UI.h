#pragma once
#include <utility>

class UI {
public:
	void PrintBoard(int(&state)[5][5]);
	std::pair<std::size_t, std::size_t> ReadMove();
	int ReadDifficulty();
	int ReadStartingPlayer();

private:
	const unsigned int m_colWidth = 10;
	const unsigned int m_rowHeight = 5;
};

