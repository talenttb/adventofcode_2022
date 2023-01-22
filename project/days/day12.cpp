#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct Pos {
  int x, y;
  string path;
  //   vector<Pos> visited;
  //   Pos* prev;
};

bool operator==(const Pos& a, const Pos& b) { return a.x == b.x && a.y == b.y; }

bool isVisited(int x, int y, Pos& curr) {
  return false;
  //   return curr.prev->x == x && curr.prev->y == y;
  //   bool result = false;
  //   for (auto&& i : curr.visited) {
  //     if (i.x == x && i.y == y) {
  //       result = true;
  //       break;
  //     }
  //   }
  //   return result;

  //   auto it = find(begin(curr.visited), end(curr.visited), Pos{x, y, ""});
  //   if (it == end(curr.visited)) {
  //     cout << "Inner3 not exists in the inners vector." << endl;
  //   } else {
  //     cout << "Inner3 already exists in the inners vector." << endl;
  //   }
  //   return it == end(curr.visited);
}

bool isValidMove(int x, int y, char c, vector<vector<char>>& v) {
  //   cout << map.at(3).at(2) << endl;
  if (x < 0 || x >= v.at(0).size()) {
    return false;
  }
  if (y < 0 || y >= v.size()) {
    return false;
  }

  char next = v.at(y).at(x);

  if (next <= c + 1) {
    return true;
  }

  return false;
}

bool isValidMoveReverse(int x, int y, char c, vector<vector<char>>& v) {
  //   cout << map.at(3).at(2) << endl;
  if (x < 0 || x >= v.at(0).size()) {
    return false;
  }
  if (y < 0 || y >= v.size()) {
    return false;
  }

  char next = v.at(y).at(x);

  if (next >= c - 1) {
    return true;
  }

  return false;
}

void day12q1(bool test) {
  string file_name = (test) ? "day12" : "day12Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<vector<char>> map;
  vector<vector<bool>> visited;
  int ans = 0, x = 0, y = 0, next_x, next_y;
  string line;
  Pos start, goal;
  queue<Pos> q;

  while (getline(file, line)) {
    vector<char> r;
    vector<bool> rr;
    x = 0;
    for (auto&& c : line) {
      if (c == 'S') {
        c = '`';
        start.x = x;
        start.y = y;
        q.push(start);
      }
      if (c == 'E') {
        c = '{';
        goal.x = x;
        goal.y = y;
      }

      r.push_back(c);
      rr.push_back(false);
      x++;
    }
    map.push_back(r);
    visited.push_back(rr);
    y++;
  }

  visited[start.y][start.x] = true;

  while (!q.empty()) {
    Pos curr = q.front();
    q.pop();

    if (curr.x == goal.x && curr.y == goal.y) {
      cout << "Solution found: " << curr.path << endl;
      cout << "Size is: " << curr.path.size() << endl;
      continue;
    }

    // Move in all four directions (up, down, left, right)
    next_x = curr.x - 1;
    next_y = curr.y;
    if (isValidMove(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "L"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
    next_x = curr.x + 1;
    next_y = curr.y;
    if (isValidMove(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "R"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
    next_x = curr.x;
    next_y = curr.y - 1;
    if (isValidMove(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "U"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
    next_x = curr.x;
    next_y = curr.y + 1;
    if (isValidMove(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "D"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
  }
  cout << "Done." << endl;
  cout << "Answer is: " << ans << endl;
}

void day12q2(bool test) {
  string file_name = (test) ? "day12" : "day12Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<vector<char>> map;
  vector<vector<bool>> visited;
  int ans = 0, x = 0, y = 0, next_x, next_y;
  string line;
  Pos start, goal;
  queue<Pos> q;

  while (getline(file, line)) {
    vector<char> r;
    vector<bool> rr;
    x = 0;
    for (auto&& c : line) {
      if (c == 'S') {
        c = '`';
        start.x = x;
        start.y = y;
      }
      if (c == 'E') {
        c = '{';
        goal.x = x;
        goal.y = y;
        q.push(goal);
      }

      r.push_back(c);
      rr.push_back(false);
      x++;
    }
    map.push_back(r);
    visited.push_back(rr);
    y++;
  }

  visited[goal.y][goal.x] = true;

  while (!q.empty()) {
    Pos curr = q.front();
    q.pop();

    if (map[curr.y][curr.x] == 'a') {
      cout << "Solution found: " << curr.path << endl;
      cout << "Size is: " << curr.path.size() << endl;
      continue;
    }

    // Move in all four directions (up, down, left, right)
    next_x = curr.x - 1;
    next_y = curr.y;
    if (isValidMoveReverse(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "L"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
    next_x = curr.x + 1;
    next_y = curr.y;
    if (isValidMoveReverse(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "R"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
    next_x = curr.x;
    next_y = curr.y - 1;
    if (isValidMoveReverse(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "U"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
    next_x = curr.x;
    next_y = curr.y + 1;
    if (isValidMoveReverse(next_x, next_y, map[curr.y][curr.x], map) && !visited[next_y][next_x]) {
      Pos next = {next_x, next_y, curr.path + "D"};
      q.push(next);
      visited[next_y][next_x] = true;
    }
  }
  cout << "Done." << endl;
  cout << "Answer is: " << ans << endl;
}