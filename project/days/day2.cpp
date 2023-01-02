#include "day2.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int day2q1(bool test) {
  string path = "";
  if (test) {
    path = "../project/inputs/day2";
  } else {
    path = "../project/inputs/day2Test";
  }

  cout << path << endl;

  ifstream file(path);
  string line;
  vector<int> result;
  vector<int> group;

  while (getline(file, line)) {
    cout << line << "\n";
    // if (line.empty()) {
    //   // calculate
    //   //   auto result = reduce(group.begin(), group.end());
    //   auto sum = 0;
    //   for (auto& n : group) {
    //     sum += n;
    //   }
    //   group.clear();
    //   result.push_back(sum);
    //   continue;
    // }
    // group.push_back(stoi(line, 0, 10));
  }

  //   auto sum = 0;
  //   for (auto& n : group) {
  //     sum += n;
  //   }
  //   group.clear();
  //   result.push_back(sum);

  //   cout << result.size() << endl;
  //   copy(result.begin(), result.end(), ostream_iterator<int>(cout, "; "));
  //   cout << endl;

  //   int ans = *max_element(result.begin(), result.end());
  //   cout << "Answer is: " << ans << endl;
  //   return ans;
  return 0;
}

int day2q2(bool test) {
  cout << "day2q2:" << test << endl;
  string path = "";
  if (test) {
    path = "../project/inputs/day2";
  } else {
    path = "../project/inputs/day2Test";
  }

  cout << path << endl;

  ifstream file(path);
  string line;
  vector<int> result;
  vector<int> group;

  while (getline(file, line)) {
    // cout << line << "\n";
    if (line.empty()) {
      // calculate
      //   auto result = reduce(group.begin(), group.end());
      auto sum = 0;
      for (auto& n : group) {
        sum += n;
      }
      group.clear();
      result.push_back(sum);
      continue;
    }
    group.push_back(stoi(line, 0, 10));
  }

  auto sum = 0;
  for (auto& n : group) {
    sum += n;
  }
  group.clear();
  result.push_back(sum);

  sort(result.begin(), result.end(), [](int a, int b) {
    return a > b;  // 升序排列
  });

  //   cout << result.size() << endl;
  //   copy(result.begin(), result.end(), ostream_iterator<int>(cout, "; "));
  //   cout << endl;

  int ans = result[0] + result[1] + result[2];
  cout << "Answer is: " << ans << endl;
  return ans;
}