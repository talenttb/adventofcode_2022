
template <typename T>
void printVector(const T& t) {
  std::copy(t.cbegin(), t.cend(), std::ostream_iterator<typename T::value_type>(std::cout, " "));
  cout << endl;
}

template <typename T>
void printVectorInVector(const T& t) {
  std::for_each(t.cbegin(), t.cend(), printVector<typename T::value_type>);
}

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

void test() {
  string line = "";
  stringstream ss(line);
  string token;
  vector<string> output;

  while (getline(ss, token, ' ')) {
    output.push_back(token);
  }
}