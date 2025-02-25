#include "Game.h"
#include <iostream>
#include <utility>
#include <string>
#include <Windows.h>
#include <stdlib.h>

Game::Game(): m_gameFinished(false), m_delayTime(1000) { Start(); }

void Game::Start() {
	for (int i = 0; i <= 4; i++)
		for (int j = 0; j <= 4; j++) m_boardState[i][j] = 0;

	PlayerTurn();
}

void Game::PlayerTurn() {
	do {
		bool error = false;
		m_gameUI.PrintBoard(m_boardState);
		std::pair<size_t, size_t> playerMove = m_gameUI.ReadMove();
		std::string errorMsg;
		if (playerMove.first < 1 || playerMove.first > 4
			|| playerMove.second < 1 || playerMove.second > 4) {
			error = true;
			errorMsg = "Invalid row and/or column, must be within board's range";
		}
		else if (m_boardState[playerMove.first][playerMove.second]) {
			error = true;
			errorMsg = "A move has already been made in that square";
		}

		if (error) {
			std::cout << errorMsg << std::endl;
			Sleep(m_delayTime);
		}
		else {
			m_boardState[playerMove.first][playerMove.second] = 1;
			system("cls");
			m_gameUI.PrintBoard(m_boardState);
			Sleep(m_delayTime);
			AITurn();
		}
		system("cls");

	} while (!m_gameFinished);
}

void Game::AITurn() {
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++) 
			if (m_boardState[i][j] == 0) {
				m_boardState[i][j] = 2;
				return;
			}
}