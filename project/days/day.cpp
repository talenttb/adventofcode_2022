#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void dayXq1(bool test) {
  string file_name = (test) ? "dayX" : "dayXTest";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<int> result;
  string line;

  while (getline(file, line)) {
    // cout << line << "\n";
    if (line.empty()) {
      continue;
    }
  }

  int ans = 0;
  cout << "Answer is: " << ans << endl;
}

void dayXq2(bool test) {
  string file_name = (test) ? "dayX" : "dayXTest";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  string line;

  while (getline(file, line)) {
    // cout << line << "\n";
    if (line.empty()) {
      continue;
    }
  }

  int ans = 0;
  cout << "Answer is: " << ans << endl;
}