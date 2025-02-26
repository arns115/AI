#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll inf = 1e17;

vector<ll> winning_states = {14, 7, 224, 112, 3584, 1792, 57344, 28672, 4368, 273, 8736, 546, 17472, 1092, 34944, 2184, 1057, 33824, 4672, 584, 292, 9344, 2114, 16912};

vector<pair<ll, ll>> possible_states[17];

ll state_win(ll player1, ll player2, ll depth){
  for(ll state: {14, 7, 224, 112, 3584, 1792, 57344, 28672, 4368, 273, 8736, 546, 17472, 1092, 34944, 2184, 1057, 33824, 4672, 584, 292, 9344, 2114, 16912}){
    if((player1 & state) == state){
      return 100 - depth;
    }
    if((player2 & state) == state){
      return -100 + depth;
    }
  }
  return 0;
}

map<ll, ll> calculated;
map<ll, ll> best_move;

vector<int> cnt_bits(1 << 16);
vector<vector<int>> bits_off(1 << 16);

int main(){
  freopen("best_move.txt", "w", stdout);
  for(int i = 0; i < (1 << 16); i++){
    cnt_bits[i] = __builtin_popcount(i);
    for(int j = 0; j < 16; j++){
      if((i & (1 << j)) == 0){
        bits_off[i].push_back(j);
      }
    }
  }
  for(int i = 0; i < (1 << 16); i++){
    for(int j = 0; j < (1 << 16); j++){
      int cnt_player1 = cnt_bits[i];
      int cnt_player2 = cnt_bits[j];
      if(cnt_player1 < cnt_player2 || cnt_player1 - cnt_player2 > 1){
        continue;
      }
      if(i & j) continue;
      possible_states[cnt_player1 + cnt_player2].push_back({i, j});
    }
  }
  for(int i = 16; i >= 0; i--){
    for(auto [x, y]: possible_states[i]){
      ll best_pos = -1, mn = inf, mx = -inf;
      ll cur_board = (x | y);
      ll identificator_of_state = (x | (y << 16));
      ll value_of_cur_turn = state_win(x, y, i);
      if(value_of_cur_turn != 0 || i == 16){
        calculated[identificator_of_state] = value_of_cur_turn;
        best_move[identificator_of_state] = identificator_of_state;
        continue;
      }
      ll turn = cnt_bits[x] + cnt_bits[y];
      turn %= 2;
      if(turn == 0){
        for(int pos: bits_off[cur_board]){
          ll x1 = (x | (1 << pos));
          ll z = calculated[(x1 | (y << 16))];
          if(z > mx){
            best_pos = (x1 | (y << 16));
            mx = z;
          }
        }
        calculated[identificator_of_state] = mx;
        best_move[identificator_of_state] = best_pos;
      }
      else{
        for(int pos: bits_off[cur_board]){
          ll y1 = (y | (1 << pos));
          ll z = calculated[(x | (y1 << 16))];
          if(z < mn){
            best_pos = (x | (y1 << 16));
            mn = z;
          }
        }
        calculated[identificator_of_state] = mn;
        best_move[identificator_of_state] = best_pos;
      }
    }
  }
  for(auto [x, y]: best_move){
    cout << x << " " << y << endl;
  } 
}