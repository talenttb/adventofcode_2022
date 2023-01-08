#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
// #include "../utils/util.h"
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

void day6q1(bool test) {
  string file_name = (test) ? "day6" : "day6Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  string line;
  int target_length = 4;

  while (getline(file, line)) {
    cout << line << "\n";
    map<char, int> char_map = {};
    char* char_arr = line.data();
    int conti_start = 0;
    for (int i = 0; i < line.length(); i++) {
      // found
      if (char_map.size() == target_length) {
        cout << "Answer is: " << i << endl;
        break;
      }

      // clean
      char curr_ch = char_arr[i];
      if (char_map.contains(curr_ch)) {
        int should_erase = char_map[curr_ch];
        for (; conti_start <= should_erase; conti_start++) {
          char_map.erase(char_arr[conti_start]);
        }
      }
      char_map.insert({curr_ch, i});
    }
  }

  int ans = 0;
  cout << "Answer is: " << ans << endl;
}

void day6q2(bool test) {
  string file_name = (test) ? "day6" : "day6Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  string line;
  int target_length = 14;

  while (getline(file, line)) {
    cout << line << "\n";
    map<char, int> char_map = {};
    char* char_arr = line.data();
    int conti_start = 0;
    for (int i = 0; i < line.length(); i++) {
      // found
      if (char_map.size() == target_length) {
        cout << "Answer is: " << i << endl;
        break;
      }

      // clean
      char curr_ch = char_arr[i];
      if (char_map.contains(curr_ch)) {
        int should_erase = char_map[curr_ch];
        for (; conti_start <= should_erase; conti_start++) {
          char_map.erase(char_arr[conti_start]);
        }
      }
      char_map.insert({curr_ch, i});
    }
  }
}