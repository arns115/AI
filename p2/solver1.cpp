#include <bits/stdc++.h>
using namespace std;

typedef long long ll;


void rotateFaceClockwise(vector<int>& cube, const vector<int>& faceIndices) {
  // Save the facelets in a temporary array
  vector<int> temp(9);
  for (int i = 0; i < 9; ++i) {
      temp[i] = cube[faceIndices[i]];
  }

  // Perform the clockwise rotation
  cube[faceIndices[0]] = temp[6];
  cube[faceIndices[1]] = temp[3];
  cube[faceIndices[2]] = temp[0];
  cube[faceIndices[3]] = temp[7];
  cube[faceIndices[5]] = temp[1];
  cube[faceIndices[6]] = temp[8];
  cube[faceIndices[7]] = temp[5];
  cube[faceIndices[8]] = temp[2];
}

void rotateFaceCounterClockwise(vector<int>& cube, const vector<int>& faceIndices) {
  // Save the facelets in a temporary array
  vector<int> temp(9);
  for (int i = 0; i < 9; ++i) {
      temp[i] = cube[faceIndices[i]];
  }

  // Perform the counterclockwise rotation
  cube[faceIndices[0]] = temp[2];
  cube[faceIndices[1]] = temp[5];
  cube[faceIndices[2]] = temp[8];
  cube[faceIndices[3]] = temp[1];
  cube[faceIndices[5]] = temp[7];
  cube[faceIndices[6]] = temp[0];
  cube[faceIndices[7]] = temp[3];
  cube[faceIndices[8]] = temp[6];
}

// Define the indices for each face
const vector<int> FRONT_FACE = {0, 1, 2, 3, 4, 5, 6, 7, 8};
const vector<int> BACK_FACE = {9, 10, 11, 12, 13, 14, 15, 16, 17};
const vector<int> RIGHT_FACE = {18, 19, 20, 21, 22, 23, 24, 25, 26};
const vector<int> LEFT_FACE = {27, 28, 29, 30, 31, 32, 33, 34, 35};
const vector<int> UP_FACE = {36, 37, 38, 39, 40, 41, 42, 43, 44};
const vector<int> DOWN_FACE = {45, 46, 47, 48, 49, 50, 51, 52, 53};

// Rotate the front face clockwise and update adjacent faces
void rotateFrontClockwise(vector<int> &cube) {
  rotateFaceClockwise(cube, FRONT_FACE);

  // Save the adjacent facelets
  int temp1 = cube[36], temp2 = cube[37], temp3 = cube[38]; // Up face
  int temp4 = cube[18], temp5 = cube[21], temp6 = cube[24]; // Right face
  int temp7 = cube[45], temp8 = cube[46], temp9 = cube[47]; // Down face
  int temp10 = cube[35], temp11 = cube[32], temp12 = cube[29]; // Left face

  // Update adjacent faces
  cube[36] = temp10; cube[37] = temp11; cube[38] = temp12; // Up face
  cube[18] = temp1; cube[21] = temp2; cube[24] = temp3; // Right face
  cube[45] = temp4; cube[46] = temp5; cube[47] = temp6; // Down face
  cube[35] = temp7; cube[32] = temp8; cube[29] = temp9; // Left face

}

// Rotate the front face counterclockwise and update adjacent faces
void rotateFrontCounterClockwise(vector<int> &cube) {
  rotateFaceCounterClockwise(cube, FRONT_FACE);

  // Save the adjacent facelets
  int temp1 = cube[36], temp2 = cube[37], temp3 = cube[38]; // Up face
  int temp4 = cube[18], temp5 = cube[21], temp6 = cube[24]; // Right face
  int temp7 = cube[45], temp8 = cube[46], temp9 = cube[47]; // Down face
  int temp10 = cube[35], temp11 = cube[32], temp12 = cube[29]; // Left face

  // Update adjacent faces
  cube[36] = temp4; cube[37] = temp5; cube[38] = temp6; // Up face
  cube[18] = temp7; cube[21] = temp8; cube[24] = temp9; // Right face
  cube[45] = temp10; cube[46] = temp11; cube[47] = temp12; // Down face
  cube[35] = temp1; cube[32] = temp2; cube[29] = temp3; // Left face

}

// Rotate the back face clockwise and update adjacent faces
void rotateBackClockwise(vector<int> &cube) {
  rotateFaceClockwise(cube, BACK_FACE);

  // Save the adjacent facelets
  int temp1 = cube[42], temp2 = cube[43], temp3 = cube[44]; // Up face
  int temp4 = cube[26], temp5 = cube[23], temp6 = cube[20]; // Right face
  int temp7 = cube[51], temp8 = cube[52], temp9 = cube[53]; // Down face
  int temp10 = cube[27], temp11 = cube[30], temp12 = cube[33]; // Left face

  // Update adjacent faces
  cube[42] = temp4; cube[43] = temp5; cube[44] = temp6; // Up face
  cube[26] = temp7; cube[23] = temp8; cube[20] = temp9; // Right face
  cube[51] = temp10; cube[52] = temp11; cube[53] = temp12; // Down face
  cube[27] = temp1; cube[30] = temp2; cube[33] = temp3; // Left face

}

// Rotate the back face counterclockwise and update adjacent faces
void rotateBackCounterClockwise(vector<int> &cube) {
  rotateFaceCounterClockwise(cube, BACK_FACE);

  // Save the adjacent facelets
  int temp1 = cube[42], temp2 = cube[43], temp3 = cube[44]; // Up face
  int temp4 = cube[26], temp5 = cube[23], temp6 = cube[20]; // Right face
  int temp7 = cube[51], temp8 = cube[52], temp9 = cube[53]; // Down face
  int temp10 = cube[27], temp11 = cube[30], temp12 = cube[33]; // Left face

  // Update adjacent faces
  cube[42] = temp10; cube[43] = temp11; cube[44] = temp12; // Up face
  cube[26] = temp1; cube[23] = temp2; cube[20] = temp3; // Right face
  cube[51] = temp4; cube[52] = temp5; cube[53] = temp6; // Down face
  cube[27] = temp7; cube[30] = temp8; cube[33] = temp9; // Left face
}

// Rotate the right face clockwise and update adjacent faces
void rotateRightClockwise(vector<int> &cube) {
  rotateFaceClockwise(cube, RIGHT_FACE);

  // Save the adjacent facelets
  int temp1 = cube[38], temp2 = cube[41], temp3 = cube[44]; // Up face
  int temp4 = cube[9], temp5 = cube[12], temp6 = cube[15]; // Back face
  int temp7 = cube[47], temp8 = cube[50], temp9 = cube[53]; // Down face
  int temp10 = cube[2], temp11 = cube[5], temp12 = cube[8]; // Front face

  // Update adjacent faces
  cube[38] = temp10; cube[41] = temp11; cube[44] = temp12; // Up face
  cube[9] = temp1; cube[12] = temp2; cube[15] = temp3; // Back face
  cube[47] = temp4; cube[50] = temp5; cube[53] = temp6; // Down face
  cube[2] = temp7; cube[5] = temp8; cube[8] = temp9; // Front face

}

// Rotate the right face counterclockwise and update adjacent faces
void rotateRightCounterClockwise(vector<int> &cube) {
  rotateFaceCounterClockwise(cube, RIGHT_FACE);

  // Save the adjacent facelets
  int temp1 = cube[38], temp2 = cube[41], temp3 = cube[44]; // Up face
  int temp4 = cube[9], temp5 = cube[12], temp6 = cube[15]; // Back face
  int temp7 = cube[47], temp8 = cube[50], temp9 = cube[53]; // Down face
  int temp10 = cube[2], temp11 = cube[5], temp12 = cube[8]; // Front face

  // Update adjacent faces
  cube[38] = temp4; cube[41] = temp5; cube[44] = temp6; // Up face
  cube[9] = temp7; cube[12] = temp8; cube[15] = temp9; // Back face
  cube[47] = temp10; cube[50] = temp11; cube[53] = temp12; // Down face
  cube[2] = temp1; cube[5] = temp2; cube[8] = temp3; // Front face

}

// Rotate the left face clockwise and update adjacent faces
void rotateLeftClockwise(vector<int> &cube) {
  rotateFaceClockwise(cube, LEFT_FACE);

  // Save the adjacent facelets
  int temp1 = cube[36], temp2 = cube[39], temp3 = cube[42]; // Up face
  int temp4 = cube[0], temp5 = cube[3], temp6 = cube[6]; // Front face
  int temp7 = cube[45], temp8 = cube[48], temp9 = cube[51]; // Down face
  int temp10 = cube[11], temp11 = cube[14], temp12 = cube[17]; // Back face

  // Update adjacent faces
  cube[36] = temp10; cube[39] = temp11; cube[42] = temp12; // Up face
  cube[0] = temp1; cube[3] = temp2; cube[6] = temp3; // Front face
  cube[45] = temp4; cube[48] = temp5; cube[51] = temp6; // Down face
  cube[11] = temp7; cube[14] = temp8; cube[17] = temp9; // Back face

}

// Rotate the left face counterclockwise and update adjacent faces
void rotateLeftCounterClockwise(vector<int> &cube) {
  rotateFaceCounterClockwise(cube, LEFT_FACE);

  // Save the adjacent facelets
  int temp1 = cube[36], temp2 = cube[39], temp3 = cube[42]; // Up face
  int temp4 = cube[0], temp5 = cube[3], temp6 = cube[6]; // Front face
  int temp7 = cube[45], temp8 = cube[48], temp9 = cube[51]; // Down face
  int temp10 = cube[11], temp11 = cube[14], temp12 = cube[17]; // Back face

  // Update adjacent faces
  cube[36] = temp4; cube[39] = temp5; cube[42] = temp6; // Up face
  cube[0] = temp7; cube[3] = temp8; cube[6] = temp9; // Front face
  cube[45] = temp10; cube[48] = temp11; cube[51] = temp12; // Down face
  cube[11] = temp1; cube[14] = temp2; cube[17] = temp3; // Back face

}

// Rotate the up face clockwise and update adjacent faces
void rotateUpClockwise(vector<int> &cube) {
  rotateFaceClockwise(cube, UP_FACE);

  // Save the adjacent facelets
  int temp1 = cube[0], temp2 = cube[1], temp3 = cube[2]; // Front face
  int temp4 = cube[18], temp5 = cube[19], temp6 = cube[20]; // Right face
  int temp7 = cube[9], temp8 = cube[10], temp9 = cube[11]; // Back face
  int temp10 = cube[27], temp11 = cube[28], temp12 = cube[29]; // Left face

  // Update adjacent faces
  cube[0] = temp10; cube[1] = temp11; cube[2] = temp12; // Front face
  cube[18] = temp1; cube[19] = temp2; cube[20] = temp3; // Right face
  cube[9] = temp4; cube[10] = temp5; cube[11] = temp6; // Back face
  cube[27] = temp7; cube[28] = temp8; cube[29] = temp9; // Left face

}

// Rotate the up face counterclockwise and update adjacent faces
void rotateUpCounterClockwise(vector<int> &cube) {
  rotateFaceCounterClockwise(cube, UP_FACE);

  // Save the adjacent facelets
  int temp1 = cube[0], temp2 = cube[1], temp3 = cube[2]; // Front face
  int temp4 = cube[18], temp5 = cube[19], temp6 = cube[20]; // Right face
  int temp7 = cube[9], temp8 = cube[10], temp9 = cube[11]; // Back face
  int temp10 = cube[27], temp11 = cube[28], temp12 = cube[29]; // Left face

  // Update adjacent faces
  cube[0] = temp4; cube[1] = temp5; cube[2] = temp6; // Front face
  cube[18] = temp7; cube[19] = temp8; cube[20] = temp9; // Right face
  cube[9] = temp10; cube[10] = temp11; cube[11] = temp12; // Back face
  cube[27] = temp1; cube[28] = temp2; cube[29] = temp3; // Left face

}

// Rotate the down face clockwise and update adjacent faces
void rotateDownClockwise(vector<int> &cube) {
  rotateFaceClockwise(cube, DOWN_FACE);

  // Save the adjacent facelets
  int temp1 = cube[6], temp2 = cube[7], temp3 = cube[8]; // Front face
  int temp4 = cube[24], temp5 = cube[25], temp6 = cube[26]; // Right face
  int temp7 = cube[15], temp8 = cube[16], temp9 = cube[17]; // Back face
  int temp10 = cube[33], temp11 = cube[34], temp12 = cube[35]; // Left face

  // Update adjacent faces
  cube[6] = temp10; cube[7] = temp11; cube[8] = temp12; // Front face
  cube[24] = temp1; cube[25] = temp2; cube[26] = temp3; // Right face
  cube[15] = temp4; cube[16] = temp5; cube[17] = temp6; // Back face
  cube[33] = temp7; cube[34] = temp8; cube[35] = temp9; // Left face

}

// Rotate the down face counterclockwise and update adjacent faces
void rotateDownCounterClockwise(vector<int> &cube) {
  rotateFaceCounterClockwise(cube, DOWN_FACE);

  // Save the adjacent facelets
  int temp1 = cube[6], temp2 = cube[7], temp3 = cube[8]; // Front face
  int temp4 = cube[24], temp5 = cube[25], temp6 = cube[26]; // Right face
  int temp7 = cube[15], temp8 = cube[16], temp9 = cube[17]; // Back face
  int temp10 = cube[33], temp11 = cube[34], temp12 = cube[35]; // Left face

  // Update adjacent faces
  cube[6] = temp4; cube[7] = temp5; cube[8] = temp6; // Front face
  cube[24] = temp7; cube[25] = temp8; cube[26] = temp9; // Right face
  cube[15] = temp10; cube[16] = temp11; cube[17] = temp12; // Back face
  cube[33] = temp1; cube[34] = temp2; cube[35] = temp3; // Left face

}

vector<pair<vector<int>, string>> moves(vector<int> & cur){
  vector<pair<vector<int>, string>> possible_moves;
  rotateFrontClockwise(cur);
  possible_moves.push_back({cur, "F"});
  rotateFrontCounterClockwise(cur);
  rotateFrontCounterClockwise(cur);
  possible_moves.push_back({cur, "F'"});
  rotateFrontClockwise(cur);
  rotateBackClockwise(cur);
  possible_moves.push_back({cur, "B"});
  rotateBackCounterClockwise(cur);
  rotateBackCounterClockwise(cur);
  possible_moves.push_back({cur, "B'"});
  rotateBackClockwise(cur);
  rotateRightClockwise(cur);
  possible_moves.push_back({cur, "R"});
  rotateRightCounterClockwise(cur);
  rotateRightCounterClockwise(cur);
  possible_moves.push_back({cur, "R'"});
  rotateRightClockwise(cur);
  rotateLeftClockwise(cur);
  possible_moves.push_back({cur, "L"});
  rotateLeftCounterClockwise(cur);
  rotateLeftCounterClockwise(cur);
  possible_moves.push_back({cur, "L'"});
  rotateLeftClockwise(cur);
  rotateUpClockwise(cur);
  possible_moves.push_back({cur, "U"});
  rotateUpCounterClockwise(cur);
  rotateUpCounterClockwise(cur);
  possible_moves.push_back({cur, "U'"});
  rotateUpClockwise(cur);
  rotateDownClockwise(cur);
  possible_moves.push_back({cur, "D"});
  rotateDownCounterClockwise(cur);
  rotateDownCounterClockwise(cur);
  possible_moves.push_back({cur, "D'"});
  rotateDownClockwise(cur);
  return possible_moves;
}


bool end(const vector<int> &cur, const vector<int> &initial_cube){
  return (cur == initial_cube);
}

// manhattan distance
int heuristic(const vector<int> &cur, const vector<int> &initial_cube) {
  int res = 0;
  return 0;
  for (int i = 0; i < (int)cur.size(); i++) {
    if (cur[i] != initial_cube[i]) {
      for (int j = 0; j < (int)initial_cube.size(); j++) {
        if (initial_cube[j] == cur[i]) {
          res += abs(i - j);
          break;
        }
      }
    }
  }
  return res;
}

vector<string> split(const string& str, char delimiter) {
  vector<string> result;
  stringstream ss(str);
  string tmp;


  // cout << "split: " << cin>>
  while (getline(ss, tmp, delimiter)) result.push_back(tmp);

  return result;
}

int main() {
  vector<int> initial_state(54);
  for (int i = 0; i < 9; ++i) initial_state[i] = 0;    // Front face
  for (int i = 9; i < 18; ++i) initial_state[i] = 1;  // Back face
  for (int i = 18; i < 27; ++i) initial_state[i] = 2;   // Right face
  for (int i = 27; i < 36; ++i) initial_state[i] = 3;  // Left face
  for (int i = 36; i < 45; ++i) initial_state[i] = 4;    // Up face
  for (int i = 45; i < 54; ++i) initial_state[i] = 5; // Down face
  vector<int> scrambled = initial_state;

  // freopen("input.txt", "r", stdin);

  ifstream input("input.txt");
  string n; 
  std::getline(input, n);
	//freopen("output.txt", "w", stdout);
  vector<string> s = split(n, ' ');

  for(int i = 0; i < (int)s.size(); i++){
    if(s[i] == "R"){
      rotateRightClockwise(scrambled);
    }
    if(s[i] == "R'"){
      rotateRightCounterClockwise(scrambled);
    }
    if(s[i] == "L"){
      rotateLeftClockwise(scrambled);
    }
    if(s[i] == "L'"){
      rotateLeftCounterClockwise(scrambled);
    }
    if(s[i] == "U"){
      rotateUpClockwise(scrambled);
    }
    if(s[i] == "U'"){
      rotateUpCounterClockwise(scrambled);
    }
    if(s[i] == "D"){
      rotateDownClockwise(scrambled);
    }
    if(s[i] == "D'"){
      rotateDownCounterClockwise(scrambled);
    }
    if(s[i] == "F"){
      rotateFrontClockwise(scrambled);
    }
    if(s[i] == "F'"){
      rotateFrontCounterClockwise(scrambled);
    }
    if(s[i] == "B"){
      rotateBackClockwise(scrambled);
    }
    if(s[i] == "B'"){
      rotateBackCounterClockwise(scrambled);
    }
  }
  map<vector<int>, pair<vector<int>, string>> pre;
  /*
  set<vector<int>> visited;
  visited.insert(scrambled);
  priority_queue<tuple<int, vector<int>>> pq;
  //pq.push({-heuristic(scrambled, initial_state), scrambled});
  while((int)pq.size()){
    auto [dist, cur] = pq.top();
    if(end(cur, initial_state)) break;
    pq.pop();
    dist = -dist;
    dist -= heuristic(cur, initial_state);
    auto possible_moves = moves(cur);
    for(auto [move, rotation]: possible_moves){
      int heuristic_cost = heuristic(move, initial_state);
      pre[move] = {cur, rotation};
      pq.push({-(heuristic_cost + dist + 1), move});
    }
  }
    */
  queue<vector<int>> q;
  q.push(scrambled);
  while((int)q.size()){
    auto cur = q.front();
    q.pop();
    auto possible_moves = moves(cur);
    bool finished = end(cur, initial_state);
    for(auto [move, rotation]: possible_moves){
      if(pre.count(move)){
        continue;
      }
      q.push(move);
      pre[move] = {cur, rotation};
      if(end(move, initial_state)){
        finished = 1;
        break;
      }
    }
    if(finished) break;
  }
  cout << "FOUND" << endl;
  vector<int> cur = initial_state;
  vector<string> sol;
  while(cur != scrambled){
    sol.push_back(pre[cur].second);
    cur = pre[cur].first;
  }
  reverse(sol.begin(), sol.end());
  cout << (int)sol.size() << endl;
  for (string rotation:sol) cout << rotation << ' ';
  cout << endl;
}