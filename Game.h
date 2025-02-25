#pragma once
#include "UI.h"

class Game {
public:
	Game();
	void Start();

private:
	void PlayerTurn();
	void AITurn();

private:
	UI m_gameUI;
	int m_boardState[5][5];
	bool m_gameFinished;
	unsigned int m_delayTime;
};

