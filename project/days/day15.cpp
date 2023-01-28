#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Pos {
  int x, y;
  char value;
};

struct PosHash {
  std::size_t operator()(const Pos &coord) const {
    // hash the x and y values of the Pos struct
    return std::hash<int>()(coord.x) ^ std::hash<int>()(coord.y);
  }
};

bool operator==(const Pos &l, const Pos &r) {
  // compare the x and y values of the Pos structs
  return l.x == r.x && l.y == r.y && l.value == r.value;
}

unordered_map<Pos, Pos, PosHash> result;
int left_x = 0, right_x = 0, up_y = 0, down_y = 0;

int get_distance(Pos s) {
  int dis = -1;
  if (result.find(s) != result.end()) {
    auto b = result[s];
    dis = abs(s.x - b.x) + abs(s.y - b.y);
  }
  return dis;
}

void draw_en_q1(Pos s, int y) {
  int dis = get_distance(s);
  //   for (int y = s.y - dis; y <= s.y + dis; y++) {
  for (int x = s.x - dis; x <= s.x + dis; x++) {
    //   cout << "(" << x << "," << y << ")" << endl;
    //   cout << "(" << x << "," << y << ")\t";
    int check = abs(s.x - x) + abs(s.y - y);
    if (check > dis) {
      continue;
    }

    Pos s = Pos{x, y, 'S'};
    Pos b = Pos{x, y, 'B'};
    Pos en = Pos{x, y, '#'};
    if (result.count(s) <= 0 || result.count(b) <= 0 || result.count(en) <= 0) {
      right_x = x > right_x ? x : right_x;
      left_x = x < left_x ? x : left_x;
      up_y = y > up_y ? y : up_y;
      down_y = y < down_y ? y : down_y;
      // cout << "DRAW: (" << x << "," << y << ")" << endl;
      result[en] = s;
    }
  }
  //
}

bool draw_en_q2(Pos s) {
  int dis = get_distance(s);
  //   if ((s.x - dis) < 0 || (s.y + dis) > 4000000) {
  //     return false;
  //   } else {
  //     return true;
  //   }
  int xx = (s.x - dis) < 0 ? 0 : s.x - dis;
  int yy = (s.y + dis) > 4000000 ? 4000000 : s.y + dis;
  for (int y = s.y - dis; y <= yy; y++) {
    for (int x = xx; x <= s.x + dis; x++) {
      int check = abs(s.x - x) + abs(s.y - y);
      if (check > dis) {
        continue;
      }

      Pos s = Pos{x, y, 'S'};
      Pos b = Pos{x, y, 'B'};
      Pos en = Pos{x, y, '#'};
      if (result.count(s) <= 0 || result.count(b) <= 0 || result.count(en) <= 0) {
        //   lower than 0 and no larger than 4000000.
        // if (x < 0 || y > 4000000) {
        //   return false;
        //   break;
        // }
        right_x = x > right_x ? x : right_x;
        left_x = x < left_x ? x : left_x;
        up_y = y > up_y ? y : up_y;
        down_y = y < down_y ? y : down_y;
        // cout << "DRAW: (" << x << "," << y << ")" << endl;
        result[en] = s;
      }
    }
  }
  return true;
}

void print_map() {
  for (int y = down_y; y <= up_y; y++) {
    for (int x = left_x; x <= right_x; x++) {
      Pos s = Pos{x, y, 'S'};
      Pos b = Pos{x, y, 'B'};
      Pos en = Pos{x, y, '#'};
      if (x == 0 && y == 0) {
        std::cout << "0";
      } else if (result.count(s) > 0) {
        std::cout << "S";
      } else if (result.count(b) > 0) {
        std::cout << "B";
      } else if (result.count(en) > 0) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    cout << endl;
  }
}

void print_map_2() {
  int yy = up_y > 4000000 ? 4000000 : up_y;
  for (int y = down_y; y <= yy; y++) {
    for (int x = 0; x <= right_x; x++) {
      Pos s = Pos{x, y, 'S'};
      Pos b = Pos{x, y, 'B'};
      Pos en = Pos{x, y, '#'};
      if (x == 0 && y == 0) {
        std::cout << "0";
      } else if (result.count(s) > 0) {
        std::cout << "S";
      } else if (result.count(b) > 0) {
        std::cout << "B";
      } else if (result.count(en) > 0) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    cout << endl;
  }
}

void day15q1(bool test) {
  string file_name = (test) ? "day15" : "day15Test";
  int target_y = (test) ? 2000000 : 10;
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  int ans = 0;
  vector<Pos> need_draws = {};
  string line;
  const regex r("Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)");
  smatch sm;

  while (getline(file, line)) {
    // cout << line << ":\n";
    if (regex_search(line, sm, r)) {
      int sx = stoi(sm[1]), sy = stoi(sm[2]), bx = stoi(sm[3]), by = stoi(sm[4]);
      //   cout << "\t"
      //        << "Sensor: (" << sx << "," << sy << ") ";
      //   cout << "\t"
      //        << "Beacon: (" << bx << "," << by << ") ";
      //   cout << endl;
      //   result.push_back(Pos{sx, sy, 'S'});
      //   result.push_back(Pos{bx, by, 'B'});

      Pos s = Pos{sx, sy, 'S'};
      Pos b = Pos{bx, by, 'B'};
      result[s] = b;
      need_draws.push_back(s);
      result[b] = b;

      if (sx > right_x || bx > right_x) {
        right_x = sx > bx ? sx : bx;
      }
      if (sx < left_x || bx < left_x) {
        left_x = sx < bx ? sx : bx;
      }
      if (sy > up_y || by > up_y) {
        up_y = sy > by ? sy : by;
      }
      if (sy < down_y || by < down_y) {
        down_y = sy < by ? sy : by;
      }
    }
  }

  for (auto &&i : need_draws) {
    draw_en_q1(i, target_y);
    // if (i.x == 8 && i.y == 7) {
    //   //   cout << "(" << i.x << "," << i.y << ")->" << get_distance(i) << endl;
    //   draw_en_q1(i);
    // }
  }

  for (int x = left_x; x <= right_x; x++) {
    Pos en = Pos{x, target_y, '#'};
    if (result.count(en) > 0) {
      ans++;
    }
  }
  ans--;
  print_map();

  cout << "Answer is: " << ans << endl;
}

void day15q2(bool test) {
  string file_name = (test) ? "day15" : "day15Test";
  int target_y = (test) ? 2000000 : 10;
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  int ans = 0;
  vector<Pos> need_draws = {};
  string line;
  const regex r("Sensor at x=(-?\\d+), y=(-?\\d+): closest beacon is at x=(-?\\d+), y=(-?\\d+)");
  smatch sm;

  while (getline(file, line)) {
    // cout << line << ":\n";
    if (regex_search(line, sm, r)) {
      int sx = stoi(sm[1]), sy = stoi(sm[2]), bx = stoi(sm[3]), by = stoi(sm[4]);
      //   cout << "\t"
      //        << "Sensor: (" << sx << "," << sy << ") ";
      //   cout << "\t"
      //        << "Beacon: (" << bx << "," << by << ") ";
      //   cout << endl;
      //   result.push_back(Pos{sx, sy, 'S'});
      //   result.push_back(Pos{bx, by, 'B'});

      Pos s = Pos{sx, sy, 'S'};
      Pos b = Pos{bx, by, 'B'};
      result[s] = b;
      need_draws.push_back(s);
      result[b] = b;

      if (sx > right_x || bx > right_x) {
        right_x = sx > bx ? sx : bx;
      }
      if (sx < left_x || bx < left_x) {
        left_x = sx < bx ? sx : bx;
      }
      if (sy > up_y || by > up_y) {
        up_y = sy > by ? sy : by;
      }
      if (sy < down_y || by < down_y) {
        down_y = sy < by ? sy : by;
      }
    }
  }

  for (auto &&i : need_draws) {
    bool f = draw_en_q2(i);
    cout << "Found: " << f << " (" << i.x << "," << i.y << ")" << endl;
    // cout << "Found: " << f << " (" << i.x << "," << i.y << ")->" << get_distance(i) << endl;
  }

  //   for (int x = left_x; x <= right_x; x++) {
  //     Pos en = Pos{x, target_y, '#'};
  //     if (result.count(en) > 0) {
  //       ans++;
  //     }
  //   }
  //   ans--;

  print_map_2();
  //   print_map();

  cout << "Answer is: " << ans << endl;
}