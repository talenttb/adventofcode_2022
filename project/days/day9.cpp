#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const int N = 400;
struct Coord {
  int x;
  int y;
  Coord(int x = N / 2, int y = N / 2) : x(x), y(y) {}
};

class Step {
 public:
  char dir;
  int steps;
  Step(char ch, int s) : dir(ch), steps(s) {}
};

string printCoord(Coord item) {
  ostringstream oss;
  oss << "(x,y)=(" << item.x << "," << item.y << ")";
  return oss.str();
}

int sign(int x) { return x > 0 ? 1 : -1; }

// bool is_h_t_around(Coord head, Coord tail, int (*board)[N]) {
//   for (int i = 0; i < N; i++) {
//     for (int j = 0; j < N; j++) {
//       cout << i << j << ": " << board[i][j] << " ";
//     }
//     cout << endl;
//   }
// }
bool is_h_t_around(Coord head, Coord tail) {
  // left top
  if ((tail.x - 1 == head.x) && (tail.y + 1 == head.y)) {
    return true;
  }
  // top
  if ((tail.x == head.x) && (tail.y + 1 == head.y)) {
    return true;
  }
  // right top
  if ((tail.x + 1 == head.x) && (tail.y + 1 == head.y)) {
    return true;
  }

  // left mid
  if ((tail.x - 1 == head.x) && (tail.y == head.y)) {
    return true;
  }
  // mid
  if ((tail.x == head.x) && (tail.y == head.y)) {
    return true;
  }
  // right mid
  if ((tail.x + 1 == head.x) && (tail.y == head.y)) {
    return true;
  }

  // left bot
  if ((tail.x - 1 == head.x) && (tail.y - 1 == head.y)) {
    return true;
  }
  // bot
  if ((tail.x == head.x) && (tail.y - 1 == head.y)) {
    return true;
  }
  // right bot
  if ((tail.x + 1 == head.x) && (tail.y - 1 == head.y)) {
    return true;
  }
  return false;
}

void day9q1(bool test) {
  string file_name = (test) ? "day9" : "day9Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<Step> steps;
  struct Coord head, tail;
  string line;
  string token;
  int ans = 0;
  int board[N][N] = {};

  while (getline(file, line)) {
    cout << line << ": " << endl;
    // if (line.empty()) {
    //   continue;
    // }
    stringstream ss(line);
    vector<string> output;

    while (getline(ss, token, ' ')) {
      output.push_back(token);
    }

    auto s = Step(output[0].data()[0], stoi(output[1]));
    steps.push_back(s);

    int move_x, move_y;

    switch (s.dir) {
      case 'U': {
        move_x = 0;
        move_y = 1;
        break;
      }
      case 'D': {
        move_x = 0;
        move_y = -1;
        break;
      }
      case 'L': {
        move_x = -1;
        move_y = 0;
        break;
      }
      case 'R': {
        move_x = 1;
        move_y = 0;
        break;
      }
    }

    int move = s.steps;
    while (move-- > 0) {
      head.x += move_x;
      head.y += move_y;
      int tail_x, tail_y;
      if (!is_h_t_around(head, tail)) {
        switch (s.dir) {
          case 'U': {
            tail_x = head.x;
            tail_y = head.y - 1;
            break;
          }
          case 'D': {
            tail_x = head.x;
            tail_y = head.y + 1;
            break;
          }
          case 'L': {
            tail_x = head.x + 1;
            tail_y = head.y;
            break;
          }
          case 'R': {
            tail_x = head.x - 1;
            tail_y = head.y;
            break;
          }
        }
        tail.x = tail_x;
        tail.y = tail_y;
        if (board[tail_x][tail_y] == 0) {
          ans += 1;
        }
        board[tail_x][tail_y] = 1;
      }
    }
    cout << "head: " << printCoord(head) << "tail: " << printCoord(tail) << endl;
    // for (int i = head.x; i < N; i++) {
    //   for (int j = head.y; j < N; j++) {
    //   }
    // }
    // cout << endl;
  }

  //   for (auto i : steps) {
  //     cout << i.dir << "\t" << i.steps << endl;
  //   }

  //   int* array = new int[N * N];
  //   for (int i = 0; i < N; i++) {
  //     for (int j = 0; j < N; j++) {
  //       *(array + (i * N) + j) = i + j;
  //     }
  //   }

  //   for (int i = 0; i < N; i++) {
  //     for (int j = 0; j < N; j++) {
  //       cout << *(array + (i * N) + j) << "\t";
  //     }
  //     cout << endl;
  //   }
  //   delete[] array;

  //   int xyArray[N][N] = {};

  //   // 掃過二維陣列中的每一個位置
  //   for (int i = 0; i < N; i++) {
  //     for (int j = 0; j < N; j++) {
  //       // 如果在第一象限中，就將它設為1
  //       //   if (i >= 0 && j >= 0) {
  //       //     xyArray[i][j] = 1;
  //       //   }
  //     }
  //   }

  // print board in human way
  //   for (int j = N - 1; j >= 0; j--) {
  //     for (int i = 0; i < N; i++) {
  //       cout << board[i][j] << " ";
  //     }
  //     cout << endl;
  //   }

  //   for (int i = 0; i < N; i++) {
  //     for (int j = 0; j < N; j++) {
  //       ans += board[i][j];
  //     }
  //   }
  // tail start point.
  if (board[N / 2][N / 2] == 0) {
    ans += 1;
  }

  cout << "Answer is: " << ans << endl;
}

void day9q2(bool test) {
  string file_name = (test) ? "day9" : "day9Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  string line;
  string token;
  int ans = 0;
  //   Coord[10] bodies;
  Coord bodies[10];
  int board[N][N] = {};

  while (getline(file, line)) {
    cout << line << ": " << endl;
    stringstream ss(line);
    vector<string> output;

    while (getline(ss, token, ' ')) {
      output.push_back(token);
    }

    auto s = Step(output[0].data()[0], stoi(output[1]));

    int move_x, move_y;

    switch (s.dir) {
      case 'U': {
        move_x = 0;
        move_y = 1;
        break;
      }
      case 'D': {
        move_x = 0;
        move_y = -1;
        break;
      }
      case 'L': {
        move_x = -1;
        move_y = 0;
        break;
      }
      case 'R': {
        move_x = 1;
        move_y = 0;
        break;
      }
    }

    int move = s.steps;
    int idx, tail_x, tail_y;

    // auto head = &bodies[idx];
    // head->x = 10;
    // head->y = 100;
    // idx++;
    // head = &bodies[idx];
    // head->x = 11;
    // head->y = 101;
    while (move-- > 0) {
      idx = 0;
      auto head = &bodies[idx];
      head->x += move_x;
      head->y += move_y;
      //   head.x += move_x;
      //   head.y += move_y;
      idx++;
      auto tail = &bodies[idx];
      while (!is_h_t_around(*head, *tail) && (idx < 10)) {
        int delta_x = abs(head->x - tail->x);
        int delta_y = abs(head->y - tail->y);

        if (delta_x == 0) {
          // vertical
          tail_x = head->x;
          tail_y = head->y - sign(head->y - tail->y);
        } else if (delta_y == 0) {
          // horizontal
          tail_x = head->x - sign(head->x - tail->x);
          tail_y = head->y;
        } else {
          // diagonal
          tail_x = (tail->x) + sign(head->x - tail->x);
          tail_y = (tail->y) + sign(head->y - tail->y);
        }
        tail->x = tail_x;
        tail->y = tail_y;

        if (idx == 9) {
          if (board[tail_x][tail_y] == 0) {
            ans += 1;
          }
          board[tail_x][tail_y] = 1;
        }

        head = tail;
        idx++;
        tail = &bodies[idx];
      }
    }
    for (size_t i = 0; i < 10; i++) {
      cout << "body(" << i << ")->" << printCoord(bodies[i]) << endl;
    }
    cout << "Move done." << endl;
  }

  // print board in human way
  //   for (int j = N - 1; j >= 0; j--) {
  //     for (int i = 0; i < N; i++) {
  //       cout << board[i][j] << " ";
  //     }
  //     cout << endl;
  //   }
  // tail start point.
  if (board[N / 2][N / 2] == 0) {
    ans += 1;
  }

  cout << "Answer is: " << ans << endl;
}