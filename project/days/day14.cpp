#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// const int WIDTH = 200, HEIGHT = 20, SHRINK_X = 0;
const int WIDTH = 1000, HEIGHT = 230, SHRINK_X = 0;
char maze[HEIGHT][WIDTH];

struct Pos {
  int x, y;
  bool init = false;
};

void print_map() {
  cout << "===== MAP =====" << endl;
  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      cout << maze[y][x];
    }
    cout << endl;
  }
  cout << "===== MAP END =====" << endl;
}

void day14q1(bool test) {
  string file_name = (test) ? "day14" : "day14Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);

  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      maze[y][x] = '.';
    }
  }

  //   vector<int> data;
  int ans = 0, GOAL_FLOOR = 1;
  string line;

  while (getline(file, line)) {
    // cout << line << "\n";
    vector<string> parts;
    boost::split(parts, line, boost::is_any_of("->"));
    string xx, yy, delimiter = ",";
    int x, y;
    Pos curr, next;
    for (const auto& s : parts) {
      if (s == "") {
        continue;
      }

      size_t pos = s.find(delimiter);
      xx = s.substr(0, pos);
      boost::trim(xx);
      x = stoi(xx) - SHRINK_X;
      yy = s.substr(pos + delimiter.length());
      boost::trim(yy);
      y = stoi(yy);

      if (y > GOAL_FLOOR) {
        GOAL_FLOOR = y;
      }

      if (!curr.init) {
        curr = {x, y, true};
        continue;
      } else {
        next = {x, y, true};

        if (curr.x == next.x) {
          int start, end;
          if (curr.y > next.y) {
            // up
            start = next.y;
            end = curr.y;
          } else {
            // down
            start = curr.y;
            end = next.y;
          }
          for (int y = start; y <= end; y++) {
            maze[y][curr.x] = '#';
          }
        } else if (curr.y == next.y) {
          int start, end;
          if (curr.x > next.x) {
            // left
            start = next.x;
            end = curr.x;
          } else {
            // right
            start = curr.x;
            end = next.x;
          }

          for (int x = start; x <= end; x++) {
            maze[curr.y][x] = '#';
          }
        }
        curr = next;
      }
      //   std::cout << s << "-> (" << x << "," << y << ")"
      // << "\t";
    }
  }

  cout << "GOAL_FLOOR: " << GOAL_FLOOR << endl;

  // init
  Pos init = {500 - SHRINK_X, 0};

  // pouring
  for (size_t i = 0; i < 30000; i++) {
    // go down
    auto curr = init;

  pouring:
    while (maze[curr.y + 1][curr.x] == '.') {
      //   maze[curr.y][curr.x] = 'o';
      curr.y = curr.y + 1;
      goto pouring;
      //   cout << "Pos: (" << curr.x << "," << curr.y << ")" << endl;
      //   print_map();
    }

    // go down and left
    while (maze[curr.y + 1][curr.x - 1] == '.') {
      curr.x = curr.x - 1;
      curr.y = curr.y + 1;
      goto pouring;
    }

    // // go down and right
    while (maze[curr.y + 1][curr.x + 1] == '.') {
      curr.x = curr.x + 1;
      curr.y = curr.y + 1;
      goto pouring;
    }

    // cout << "Pos: (" << curr.x << "," << curr.y << ")" << endl;
    maze[curr.y][curr.x] = 'o';
    if (curr.y > GOAL_FLOOR) {
      ans = i;
      cout << "Out of maze. with heigh: " << curr.y << ". Step: " << i << endl;
      break;
    }
  }
  maze[init.y][init.x] = '+';
  print_map();

  cout << "Answer is: " << ans << endl;
}

void day14q2(bool test) {
  string file_name = (test) ? "day14" : "day14Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);

  for (size_t y = 0; y < HEIGHT; y++) {
    for (size_t x = 0; x < WIDTH; x++) {
      maze[y][x] = '.';
    }
  }

  //   vector<int> data;
  int ans = 0, GOAL_FLOOR = 1;
  string line;

  while (getline(file, line)) {
    // cout << line << "\n";
    vector<string> parts;
    boost::split(parts, line, boost::is_any_of("->"));
    string xx, yy, delimiter = ",";
    int x, y;
    Pos curr, next;
    for (const auto& s : parts) {
      if (s == "") {
        continue;
      }

      size_t pos = s.find(delimiter);
      xx = s.substr(0, pos);
      boost::trim(xx);
      x = stoi(xx) - SHRINK_X;
      yy = s.substr(pos + delimiter.length());
      boost::trim(yy);
      y = stoi(yy);

      if (y > GOAL_FLOOR) {
        GOAL_FLOOR = y;
      }

      if (!curr.init) {
        curr = {x, y, true};
        continue;
      } else {
        next = {x, y, true};

        if (curr.x == next.x) {
          int start, end;
          if (curr.y > next.y) {
            // up
            start = next.y;
            end = curr.y;
          } else {
            // down
            start = curr.y;
            end = next.y;
          }
          for (int y = start; y <= end; y++) {
            maze[y][curr.x] = '#';
          }
        } else if (curr.y == next.y) {
          int start, end;
          if (curr.x > next.x) {
            // left
            start = next.x;
            end = curr.x;
          } else {
            // right
            start = curr.x;
            end = next.x;
          }

          for (int x = start; x <= end; x++) {
            maze[curr.y][x] = '#';
          }
        }
        curr = next;
      }
      //   std::cout << s << "-> (" << x << "," << y << ")"
      // << "\t";
    }
  }

  cout << "GOAL_FLOOR: " << GOAL_FLOOR << endl;
  for (int x = 0; x < WIDTH; x++) {
    maze[GOAL_FLOOR + 2][x] = '#';
  }

  // init
  Pos init = {500 - SHRINK_X, 0};

  // pouring
  for (size_t i = 0; i < 30000; i++) {
    // go down
    auto curr = init;

  pouring:
    while (maze[curr.y + 1][curr.x] == '.') {
      //   maze[curr.y][curr.x] = 'o';
      curr.y = curr.y + 1;
      goto pouring;
      //   cout << "Pos: (" << curr.x << "," << curr.y << ")" << endl;
      //   print_map();
    }

    // go down and left
    while (maze[curr.y + 1][curr.x - 1] == '.') {
      curr.x = curr.x - 1;
      curr.y = curr.y + 1;
      goto pouring;
    }

    // // go down and right
    while (maze[curr.y + 1][curr.x + 1] == '.') {
      curr.x = curr.x + 1;
      curr.y = curr.y + 1;
      goto pouring;
    }

    // cout << "Pos: (" << curr.x << "," << curr.y << ")" << endl;
    maze[curr.y][curr.x] = 'o';
    ans++;
    if (curr.x == init.x && curr.y == init.y) {
      cout << "FULLLLLLL" << endl;
      break;
    }

    // if (curr.y > GOAL_FLOOR) {
    //   ans = i;
    //   cout << "Out of maze. with heigh: " << curr.y << ". Step: " << i << endl;
    //   break;
    // }
  }
  maze[init.y][init.x] = '+';
  print_map();

  cout << "Answer is: " << ans << endl;
}