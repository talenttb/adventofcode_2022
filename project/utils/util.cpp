#include "util.h"
#include <iostream>

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