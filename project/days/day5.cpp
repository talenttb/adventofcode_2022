#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

struct step {
  int move;
  int from;
  int to;
};

int day5q1(bool test) {
  string file_name = (test) ? "day5" : "day5Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<vector<int>> steps;
  vector<step> steps;
  vector<vector<char>> crates;
  string line;
  int section = 1;
  const regex r("move (\\d*) from (\\d*) to (\\d*)");
  smatch sm;

  while (getline(file, line)) {
    // cout << line << "\n";

    // init crates
    if (crates.empty()) {
      for (int i = 0; i <= (line.length() / 4); i++) {
        crates.push_back({});
      }
    }

    if (line.empty()) {
      section = 2;
      continue;
    }

    char* char_arr = line.data();
    switch (section) {
      case 1: {
        // stop sign
        if (char_arr[1] == '1') {
          break;
        }

        for (int i = 1, j = 0; i < line.length(); i += 4, j++) {
          if (char_arr[i] != ' ') {
            crates.at(j).push_back(char_arr[i]);
          }
        }
      } break;
      case 2: {
        if (regex_search(line, sm, r)) {
          //   steps.push_back({stoi(sm[1]), stoi(sm[2]), stoi(sm[3])});
          steps.push_back(step{stoi(sm[1]), stoi(sm[2]) - 1, stoi(sm[3]) - 1});
        }
      } break;
    }
  }
  // reverse
  for (size_t i = 0; i < crates.size(); i++) {
    reverse(crates[i].begin(), crates[i].end());
  }

  for (auto s : steps) {
    for (int i = s.move; i > 0; i--) {
      //   auto cccc = crates.at(s.from);
      //   auto el = cccc.pop_back();
      //   auto el = crates[s.from].pop_back();
      char el = crates.at(s.from).back();
      crates.at(s.from).pop_back();
      crates.at(s.to).push_back(el);
      //   cout << "pop: " << el << endl;
    }
  }

  string ans = "";

  for (size_t i = 0; i < crates.size(); i++) {
    cout << "Group: " << i << " -> " << crates[i].back() << endl;
    ans += crates[i].back();
    // cout << "Group: " << crates[i].back() << " : ";

    // cout << "Group: " << i << " : ";
    // for (auto c : crates[i]) {
    //   cout << c << " ";
    //   reverse(c.begin(), c.end());
    // }
    // cout << "Group end" << endl;
  }

  //   for (size_t i = 0; i < steps.size(); i++) {
  //     cout << "Step: " << i << endl;
  //     cout << steps[i].move << steps[i].from << steps[i].to << endl;
  //     cout << "Step end" << endl;
  //   }

  cout << "Answer is: " << ans << endl;
  return 0;
}

int day5q2(bool test) {
  string file_name = (test) ? "day5" : "day5Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<vector<int>> steps;
  vector<step> steps;
  vector<vector<char>> crates;
  string line;
  int section = 1;
  const regex r("move (\\d*) from (\\d*) to (\\d*)");
  smatch sm;

  while (getline(file, line)) {
    // cout << line << "\n";

    // init crates
    if (crates.empty()) {
      for (int i = 0; i <= (line.length() / 4); i++) {
        crates.push_back({});
      }
    }

    if (line.empty()) {
      section = 2;
      continue;
    }

    char* char_arr = line.data();
    switch (section) {
      case 1: {
        // stop sign
        if (char_arr[1] == '1') {
          break;
        }

        for (int i = 1, j = 0; i < line.length(); i += 4, j++) {
          if (char_arr[i] != ' ') {
            crates.at(j).push_back(char_arr[i]);
          }
        }
      } break;
      case 2: {
        if (regex_search(line, sm, r)) {
          steps.push_back(step{stoi(sm[1]), stoi(sm[2]) - 1, stoi(sm[3]) - 1});
        }
      } break;
    }
  }
  // reverse
  for (size_t i = 0; i < crates.size(); i++) {
    reverse(crates[i].begin(), crates[i].end());
  }

  for (auto s : steps) {
    vector<char> tmp;
    for (int i = s.move; i > 0; i--) {
      char el = crates.at(s.from).back();
      crates.at(s.from).pop_back();
      tmp.push_back(el);
    }

    while (!tmp.empty()) {
      crates.at(s.to).push_back(tmp.back());
      tmp.pop_back();
    }
  }

  string ans = "";

  for (size_t i = 0; i < crates.size(); i++) {
    cout << "Group: " << i << " -> " << crates[i].back() << endl;
    ans += crates[i].back();
  }

  cout << "Answer is: " << ans << endl;
  return 0;
}