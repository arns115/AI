#include "Game1.h"
#include <iostream>
#include <utility>
#include <string>
#include <cstdlib>  
#include <thread>   
#include <chrono>   
#include <vector>
#include <random> 

Game1::Game1(): m_gameFinished(false), m_delayTime(1000), player1(0), player2(0), state(0){

  std::freopen("best_move.txt", "r", stdin);
  long long currentState, row, column;
  while(std::cin >> currentState && std::cin >> row && std::cin >> column){
    best_move[currentState] = {row, column};
  }
  std::fclose(stdin);
  std::freopen("/dev/tty", "r", stdin);
  std::cin.clear();          

}

void Game1::Start() {
  difficulty = m_gameUI.ReadDifficulty();
  who_starts = m_gameUI.ReadStartingPlayer();
  for (int i = 0; i <= 4; i++)
    for (int j = 0; j <= 4; j++) m_boardState[i][j] = 0;

  PlayerTurn();
}

void Game1::isGameFinished(){
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

void Game1::makeMove(int player, int row, int column){
  if(player == 1){
    m_boardState[row][column] = 1;
    int pos = 4 * (row - 1) + column - 1;
    player1 |= (1LL << pos);
    state |= (1LL << pos); 
  }
  else{
    m_boardState[row][column] = 2;
    int pos = 4 * (row - 1) + column - 1;
    player2 |= (1LL << pos);
    state |= (1LL << (pos + 16)); 
  }
}


void Game1::PlayerTurn() {
  //if player starts the game (is circle) and computer is cross
  if(who_starts == 1){
    do {
      bool error = false;
      m_gameUI.PrintBoard(m_boardState);
      isGameFinished();
      if(m_gameFinished){
        std::cout << "Player 2 (Computer) is the winner" << std::endl;
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
        makeMove(1, playerMove.first, playerMove.second);
        system("clear");  
        m_gameUI.PrintBoard(m_boardState);
        isGameFinished();
        if(m_gameFinished){
          std::cout << "Player 1 (You) is the winner" << std::endl;
          break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(m_delayTime));  
        AITurn();
      }
      system("clear");  
  
    } while (true);
  }
  //if computer starts the game (is circle) and player is cross
  else{
    do {
      m_gameUI.PrintBoard(m_boardState);
      if(m_gameFinished){
        std::cout << "Player 2 (You) is the winner" << std::endl;
        break;
      }
      system("clear");  
      AITurn();
      m_gameUI.PrintBoard(m_boardState);
      isGameFinished();
      if(m_gameFinished){
        std::cout << "Player 1 (Computer) is the winner" << std::endl;
        break;
      }
      bool error = false;
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
        makeMove(2, playerMove.first, playerMove.second);
        isGameFinished();
        std::this_thread::sleep_for(std::chrono::milliseconds(m_delayTime));  
      }
      system("clear");  
  
    } while (true);
  }

}

void Game1::AITurn() {
  // this finds a random move
  std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::vector<std::pair<int, int>> positions;
  for(int i = 1; i <= 4; i++){
    for(int j = 1; j <= 4; j++){
      if(m_boardState[i][j] == 0){
        positions.push_back({i, j});
      }
    }
  }
  int random_play = std::uniform_int_distribution<int>(0, (int)positions.size())(rng);
  // fully random moves
  if(difficulty == 1){
    if(who_starts == 1){
      makeMove(2, positions[random_play].first, positions[random_play].second);
    }
    else{
      makeMove(1, positions[random_play].first, positions[random_play].second);
    }
  }
  // tries to draw or win the game
  else if(difficulty == 2){
    std::vector<long long> winning_states = {14, 7, 224, 112, 3584, 1792, 57344, 28672, 4368, 273, 8736, 546, 17472, 1092, 34944, 2184, 1057, 33824, 4672, 584, 292, 9344, 2114, 16912};	
    if(who_starts == 1){
      for(long long state_win: winning_states){
        // this would mean player1 (human) is one move away from winning so computers stops the win
        if(__builtin_popcount(player1 & state_win) == 2 && (player2 & state_win) == 0){
          long long moveToSave = (player1 & state_win) ^ (state_win);
          for(int i = 1; i <= 4; i++){
            for(int j = 1; j <= 4; j++){
              if((1 << (4 * (i - 1) + j - 1)) == moveToSave){
                makeMove(2, i, j);
                return;
              }
            }
          }
        }
      }
      // this would mean player2 (computer) is one move away from winning so computers wins
      for(long long state_win: winning_states){
        if(__builtin_popcount(player2 & state_win) == 2 && (player1 & state_win) == 0){
          long long moveToWin = (player2 & state_win) ^ (state_win);
          for(int i = 1; i <= 4; i++){
            for(int j = 1; j <= 4; j++){
              if((1 << (4 * (i - 1) + j - 1)) == moveToWin){
                makeMove(2, i, j);
                return;
              }
            }
          }
        }
      }
      //tries to play the center or plays random square if center is occupied
      for(auto [row, column]: positions){
        if((row == 2 && (column == 2 || column == 3)) || (row == 3 && (column == 2 || column == 3))){
          makeMove(2, row, column);
          return;
        }
      }
      //makes random move if center occupied
      makeMove(2, positions[random_play].first, positions[random_play].second);
    }
    else{
      for(long long state_win: winning_states){
        // this would mean player2 (human) is one move away from winning so computers stops the win
        if(__builtin_popcount(player2 & state_win) == 2 && (player1 & state_win) == 0){
          long long moveToSave = (player2 & state_win) ^ (state_win);
          for(int i = 1; i <= 4; i++){
            for(int j = 1; j <= 4; j++){
              if((1 << (4 * (i - 1) + j - 1)) == moveToSave){
                makeMove(1, i, j);
                return;
              }
            }
          }
        }
      }
      // this would mean player1 (computer) is one move away from winning so computers wins
      for(long long state_win: winning_states){
        if(__builtin_popcount(player1 & state_win) == 2 && (player2 & state_win) == 0){
          long long moveToWin = (player1 & state_win) ^ (state_win);
          for(int i = 1; i <= 4; i++){
            for(int j = 1; j <= 4; j++){
              if((1 << (4 * (i - 1) + j - 1)) == moveToWin){
                makeMove(1, i, j);
                return;
              }
            }
          }
        }
      }
      //tries to play the center or plays random square if center is occupied
      for(auto [row, column]: positions){
        if((row == 2 && (column == 2 || column == 3)) || (row == 3 && (column == 2 || column == 3))){
          makeMove(1, row, column);
          return;
        }
      }
      //makes random move if center occupied
      makeMove(1, positions[random_play].first, positions[random_play].second);
    }
  }
  // minimax mode
  else{
    auto [row, column] = best_move[state];
    if(who_starts == 1){
      makeMove(2, row, column);
    }
    else{
      makeMove(1, row, column);
    }
  }
}
