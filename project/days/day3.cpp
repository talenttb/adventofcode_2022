#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int day3q1(bool test) {
  string path = "";
  if (test) {
    path = "../project/inputs/day3";
  } else {
    path = "../project/inputs/day3";
  }

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
  return ans;
}

int day3q2(bool test) {
  string path = "";
  if (test) {
    path = "../project/inputs/day3";
  } else {
    path = "../project/inputs/day3";
  }

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
  return ans;
}