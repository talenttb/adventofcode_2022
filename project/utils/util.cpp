#include "util.h"
#include <iostream>
#include <vector>

using namespace std;

vector<string> splitString(string str, string delimiter) {
  vector<string> result;
  int start = 0;
  int end = str.find(delimiter);
  while (end != -1) {
    auto r = str.substr(start, end - start);
    start = end + delimiter.size();
    end = str.find(delimiter, start);
    result.push_back(r);
  }
  result.push_back(str.substr(start, end - start));
  return result;
}

template <typename T>
void outVec(const T& t) {
  std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, ", "));
  cout << endl;
}