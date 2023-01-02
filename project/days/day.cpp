#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int dayXq1(bool test) {
  string path = "";
  if (test) {
    path = "../project/inputs/dayX";
  } else {
    path = "../project/inputs/dayX";
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

int dayXq2(bool test) {
  string path = "";
  if (test) {
    path = "../project/inputs/dayX";
  } else {
    path = "../project/inputs/dayX";
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