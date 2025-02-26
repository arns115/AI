#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<ll, ll> best_move;

vector<ll> winning_states = {14, 7, 224, 112, 3584, 1792, 57344, 28672, 4368, 273, 8736, 546, 17472, 1092, 34944, 2184, 1057, 33824, 4672, 584, 292, 9344, 2114, 16912};

void print_state(ll x){
  ll p1 = (x & ((1 << 16) - 1)), p2 = (x >> 16);
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      if(p1 & (1 << (4 * i + j))){
        cout << 1;
      }
      else if(p2 & (1 << (4 * i + j))){
        cout << 2;
      }#include <bits/stdc++.h>
      using namespace std;
      
      typedef long long ll;
      
      map<ll, ll> best_move;
      
      vector<ll> winning_states = {14, 7, 224, 112, 3584, 1792, 57344, 28672, 4368, 273, 8736, 546, 17472, 1092, 34944, 2184, 1057, 33824, 4672, 584, 292, 9344, 2114, 16912};
      
      void print_state(ll x){
        ll p1 = (x & ((1 << 16) - 1)), p2 = (x >> 16);
        for(int i = 0; i < 4; i++){
          for(int j = 0; j < 4; j++){
            if(p1 & (1 << (4 * i + j))){
              cout << 1;
            }
            else if(p2 & (1 << (4 * i + j))){
              cout << 2;
            }
            else{
              cout << 0;
            }
          }
          cout << endl;
        }
        cout << endl;
      }
      
      
      ll state_win(ll player1, ll player2){
        for(ll state: winning_states){
          if((player1 & state) == state){
            return 100;
          }
          if((player2 & state) == state){
            return -100;
          }
        }
        return 0;
      }
      
      int main(){
        freopen("best_move.txt", "r", stdin);
        ll x, y;
        while(cin >> x && cin >> y){
          best_move[x] = y;
        }
        fclose(stdin);
        freopen("/dev/tty", "r", stdin);
        cin.clear();              
        for(auto state: winning_states){
          print_state(state);
        }
        cout << (int)best_move.size() << endl;
        ll state = 0, player1 = 0, player2 = 0;
        for(int i = 0; i < 16; i++){
          if(i % 2){
            state = best_move[state];
          }
          else{
            int u; cin >> u;
            state = state | (1 << (u));
          }
          print_state(state);
        }
      }
      else{
        cout << 0;
      }
    }
    cout << endl;
  }
  cout << endl;
}


ll state_win(ll player1, ll player2){
  for(ll state: winning_states){
    if((player1 & state) == state){
      return 100;
    }
    if((player2 & state) == state){
      return -100;
    }
  }
  return 0;
}

int main(){
  freopen("best_move.txt", "r", stdin);
  ll x, y;
  while(cin >> x && cin >> y){
    best_move[x] = y;
  }
  fclose(stdin);
  freopen("/dev/tty", "r", stdin);
  cin.clear();              
  for(auto state: winning_states){
    print_state(state);
  }
  cout << (int)best_move.size() << endl;
  ll state = 0, player1 = 0, player2 = 0;
  for(int i = 0; i < 16; i++){
    if(i % 2){
      state = best_move[state];
    }
    else{
      int u; cin >> u;
      state = state | (1 << (u));
    }
    print_state(state);
  }
}