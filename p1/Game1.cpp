#include "Game1.h"
#include <iostream>
#include <utility>
#include <string>
#include <cstdlib>  
#include <thread>   
#include <chrono>   
#include <vector>
#include <random> 

Game1::Game1(): m_gameFinished(false), m_delayTime(1000), player1(0), player2(0), state(0){}

void Game1::Start() {
  difficulty = m_gameUI.ReadDifficulty();
  for (int i = 0; i <= 4; i++)
    for (int j = 0; j <= 4; j++) m_boardState[i][j] = 0;

  PlayerTurn();
}

void Game1::is_game_finished(){
  std::vector<long long> winning_states = {14, 7, 224, 112, 3584, 1792, 57344, 28672, 4368, 273, 8736, 546, 17472, 1092, 34944, 2184, 1057, 33824, 4672, 584, 292, 9344, 2114, 16912};	
  for(long long win_state: winning_states){
    if(((player1 & win_state) == win_state) || ((player2 & win_state) == win_state)){
      m_gameFinished = 1;
      break;
    }
  }
  if(__builtin_popcount(state) == 16){
    m_gameFinished = 1;
  }
}

void Game1::PlayerTurn() {

  do {
    bool error = false;
    m_gameUI.PrintBoard(m_boardState);
    is_game_finished();
    if(m_gameFinished){
      std::cout << "Player 2 is the winner" << std::endl;
      break;
    }
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
      std::this_thread::sleep_for(std::chrono::milliseconds(m_delayTime));  
    }
    else {
      m_boardState[playerMove.first][playerMove.second] = 1;
      int pos = 4 * (playerMove.first - 1) + playerMove.second - 1;
      player1 |= (1 << pos);
      state |= (1 << pos); 
      system("clear");  
      m_gameUI.PrintBoard(m_boardState);
      is_game_finished();
      if(m_gameFinished){
        std::cout << "Player 1 is the winner" << std::endl;
        break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(m_delayTime));  
      AITurn();
    }
    system("clear");  

  } while (true);

}

void Game1::AITurn() {
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::vector<std::pair<int, int>> positions;
  if(difficulty == 1){
    for(int i = 1; i <= 4; i++){
      for(int j = 1; j <= 4; j++){
        if(m_boardState[i][j] == 0){
          positions.push_back({i, j});
        }
      }
    }
    int play = std::uniform_int_distribution<int>(0, (int)positions.size())(rng);
    m_boardState[positions[play].first][positions[play].second] = 2;
    // change this for when you reverse player
    int pos = 4 * (positions[play].first - 1) + positions[play].second - 1;
    player2 |= (1 << pos);
    state |= (1 << (pos + 16));
  }
  else if(difficulty == 2){

  }
  else{

  }
}
