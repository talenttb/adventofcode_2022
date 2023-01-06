#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int day4q1(bool test) {
  string file_name = (test) ? "day4" : "day4Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<int> result;
  string line;

  const regex r("(\\d*)-(\\d*),(\\d*)-(\\d*)");
  smatch sm;
  int ans = 0;

  while (getline(file, line)) {
    if (regex_search(line, sm, r)) {
      //   for (int i = 1; i < sm.size(); i++) {
      //     cout << sm[i] << endl;
      //   }
      //   cout << "A-Start: " << sm[1] << ". A-End: " << sm[2] << ". B-Start: " << sm[3] << ". B-End: " << sm[4] << endl;
      int as = stoi(sm[1]), ae = stoi(sm[2]), bs = stoi(sm[3]), be = stoi(sm[4]);

      if (as <= bs && ae >= be) {
        ans++;
      } else if (as >= bs && ae <= be) {
        ans++;
      }
    }
  }

  cout << "Answer is: " << ans << endl;
  return ans;
}

int day4q2(bool test) {
  string file_name = (test) ? "day4" : "day4Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<int> result;
  string line;

  const regex r("(\\d*)-(\\d*),(\\d*)-(\\d*)");
  smatch sm;
  int ans = 0;

  while (getline(file, line)) {
    if (regex_search(line, sm, r)) {
      //   cout << atoi << sm[1] << endl;
      int as = stoi(sm[1]), ae = stoi(sm[2]), bs = stoi(sm[3]), be = stoi(sm[4]);

      if (ae < bs || as > be) {
        continue;
      }

      ans++;
    }
  }

  cout << "Answer is: " << ans << endl;
  return ans;
}