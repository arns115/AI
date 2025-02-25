#pragma once
#include <utility>

class UI {
public:
	void PrintBoard(int(&state)[5][5]);
	std::pair<size_t, size_t> ReadMove();

private:
	const unsigned int m_colWidth = 10;
	const unsigned int m_rowHeight = 5;
};

