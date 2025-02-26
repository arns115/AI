#pragma once
#include "UI.h"
#include <map>

class Game1 {
public:
	Game1();
	void Start();

private:
	void PlayerTurn();
	void AITurn();
	void isGameFinished();
  void playerMove();
  void makeMove(int, int, int);

private:
	UI m_gameUI;
	int m_boardState[5][5];
	int difficulty;
	int who_starts;
	long long player1;
	long long player2;
	long long state;
	bool m_gameFinished;
	unsigned int m_delayTime;
	std::map<long long, std::pair<int, int>> best_move;
};

