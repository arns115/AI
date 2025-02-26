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
	void is_game_finished();

private:
	UI m_gameUI;
	int m_boardState[5][5];
	int difficulty;
	long long player1;
	long long player2;
	long long state;
	bool m_gameFinished;
	unsigned int m_delayTime;
	std::map<long long, long long> best_move;
};

