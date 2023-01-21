#include <algorithm>
#include <boost/multiprecision/cpp_int.hpp>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
namespace bmp = boost::multiprecision;

class Monkey {
 public:
  vector<bmp::cpp_int> items;
  vector<string> operation;
  int divide, trueIdx, falseIdx;

  void setDivide(int v) { divide = v; }
  void setTrueIdx(int v) { trueIdx = v; }
  void setFalseIdx(int v) { falseIdx = v; }
  void appendItem(bmp::cpp_int i) { items.push_back(i); }
  void setOperation(string o) {
    stringstream ss(o);
    string s;
    while (getline(ss, s, ' ')) {
      operation.push_back(s);
    }
  }
  void clearItems() { items.clear(); }

  int getOperateResult(int x) {
    int v = 0;
    int y = operation[2] == "old" ? x : stoi(operation[2]);
    if (operation[1] == "+") {
      v = x + y;
    } else if (operation[1] == "*") {
      v = x * y;
    } else {
      assert("operate error");
    }

    return floor(v / 3);
  }

  bmp::cpp_int getOperateResultQ2(bmp::cpp_int x) {
    bmp::cpp_int v = 0;
    bmp::cpp_int y = operation[2] == "old" ? x : bmp::cpp_int(stoi(operation[2]));
    if (operation[1] == "+") {
      v = x + y;
    } else if (operation[1] == "*") {
      //   auto [result, overflow] = std::mul_overflow(x, y);
      //   if (overflow) {
      //     std::cout << "Overflow detected!" << std::endl;
      //   } else {
      //     std::cout << "Result: " << result << std::endl;
      //   }
      //   if (x > INT64_MAX / y) {
      //     std::cout << "Overflow detected! " << x << "," << y << std::endl;
      //     assert(false);
      //   }
      v = x * y;
    } else {
      std::cout << "Operatie error." << endl;
      assert(false);
    }

    // cout << v << endl;

    return v;
  }
};

void day11q1(bool test) {
  string file_name = (test) ? "day11" : "day11Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<Monkey> data;
  vector<int> ans;
  int row = 0, idx = 0;
  string line;
  stringstream ss;

  while (getline(file, line)) {
    ss.str("");
    ss.clear();

    ss << line;
    switch (row) {
      case 0: {
        // ss >> lhs >> op >> rhs;
        std::cout << "new object: " << idx << "\t";
        data.push_back(Monkey());
        ans.push_back(0);
        row++;
        break;
      }
      case 1: {
        string s1, s2;
        ss >> s1;
        ss >> s1;
        while (getline(ss, s2, ',')) {
          std::cout << "item: " << stoi(s2) << "\t";
          data.at(idx).appendItem(stoi(s2));
        }
        row++;
        break;
      }
      case 2: {
        string f = line.substr(line.find('=') + 2, line.length());
        std::cout << "Operation: " << f << "\t";
        data.at(idx).setOperation(f);
        row++;
        break;
      }
      case 3: {
        string s;
        // int check;
        while (getline(ss, s, ' ')) {
          // get the last token
          if (ss.eof()) {
            // stringstream(s) >> check;
            std::cout << "Divisible: " << stoi(s) << "\t";
            // std::cout << "Divisible: " << check << "\t";
            data.at(idx).setDivide(stoi(s));
          }
        }
        row++;
        break;
      }
      case 4: {
        string s;
        while (getline(ss, s, ' ')) {
          if (ss.eof()) {
            std::cout << "true goto: " << stoi(s) << "\t";
            data.at(idx).setTrueIdx(stoi(s));
          }
        }
        row++;
        break;
      }
      case 5: {
        string s;
        while (getline(ss, s, ' ')) {
          if (ss.eof()) {
            std::cout << "false goto: " << stoi(s) << "\t";
            data.at(idx).setFalseIdx(stoi(s));
          }
        }
        row++;
        break;
      }
      default: {
        std::cout << endl;
        row = 0;
        idx++;
        break;
      }
    }
  }
  std::cout << endl;

  for (size_t round = 0; round < 20; round++) {
    for (int i = 0; i < data.size(); i++) {
      auto monkey = data[i];
      for (auto item : monkey.items) {
        ans.at(i) += 1;
        auto v = monkey.getOperateResult((int)item);
        if (v % monkey.divide == 0) {
          data.at(monkey.trueIdx).appendItem(v);
        } else {
          data.at(monkey.falseIdx).appendItem(v);
        }
      }
      data[i].items.clear();
      //   data[i].clearItems();
    }
  }

  std::sort(ans.begin(), ans.end(), std::greater<int>());

  for (auto i : ans) {
    cout << i << endl;
  }

  cout << endl << "Answer is: " << (ans[0] * ans[1]) << endl;
}

void day11q2(bool test) {
  string file_name = (test) ? "day11" : "day11Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<Monkey> data;
  vector<int> ans;
  int row = 0, idx = 0;
  string line;
  stringstream ss;

  while (getline(file, line)) {
    ss.str("");
    ss.clear();

    ss << line;
    switch (row) {
      case 0: {
        data.push_back(Monkey());
        ans.push_back(0);
        row++;
        break;
      }
      case 1: {
        string s1, s2;
        ss >> s1;
        ss >> s1;
        while (getline(ss, s2, ',')) {
          data.at(idx).appendItem(stoi(s2));
        }
        row++;
        break;
      }
      case 2: {
        string f = line.substr(line.find('=') + 2, line.length());
        data.at(idx).setOperation(f);
        row++;
        break;
      }
      case 3: {
        string s;
        while (getline(ss, s, ' ')) {
          // get the last token
          if (ss.eof()) {
            data.at(idx).setDivide(stoi(s));
          }
        }
        row++;
        break;
      }
      case 4: {
        string s;
        while (getline(ss, s, ' ')) {
          if (ss.eof()) {
            data.at(idx).setTrueIdx(stoi(s));
          }
        }
        row++;
        break;
      }
      case 5: {
        string s;
        while (getline(ss, s, ' ')) {
          if (ss.eof()) {
            data.at(idx).setFalseIdx(stoi(s));
          }
        }
        row++;
        break;
      }
      default: {
        row = 0;
        idx++;
        break;
      }
    }
  }
  std::cout << endl;

  int gcd = 1;
  for (auto &&i : data) {
    gcd *= i.divide;
  }

  for (size_t round = 0; round < 10000; round++) {
    // cout << "Go round: " << round << endl;
    for (int i = 0; i < data.size(); i++) {
      auto monkey = data[i];
      for (auto item : monkey.items) {
        ans.at(i) += 1;
        auto v = monkey.getOperateResultQ2(item);
        v = v % gcd;
        if (v % monkey.divide == 0) {
          data.at(monkey.trueIdx).appendItem(v);
        } else {
          data.at(monkey.falseIdx).appendItem(v);
        }
      }
      data[i].items.clear();
      //   data[i].clearItems();
    }
  }

  cout << "Ori:\n==========" << endl;
  for (auto i : ans) {
    cout << i << endl;
  }
  cout << "==========" << endl;
  //   cout << "Sorted" << endl;
  std::sort(ans.begin(), ans.end(), std::greater<int>());
  //   for (auto i : ans) {
  //     cout << i << endl;
  //   }

  //   std::cout << "INT_MAX: " << INT_MAX << std::endl;
  //   if ((ans[0] * ans[1]) > INT_MAX) {
  //     assert("BOMB!");
  //   }
  //   cout << ((bmp::cpp_int)50218 * (bmp::cpp_int)52523) << endl;

  cout << endl << "Answer is: " << ((bmp::cpp_int)ans[0] * (bmp::cpp_int)ans[1]) << endl;
}