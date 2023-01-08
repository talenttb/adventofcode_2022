#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void printVector(const T& t) {
  std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
  cout << endl;
}

template <typename T>
void printVectorInVector(const T& t) {
  std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

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