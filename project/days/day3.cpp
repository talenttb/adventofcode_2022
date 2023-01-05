#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int day3q1(bool test) {
  string file_name = (test) ? "day3" : "day3Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  int ans = 0;
  string line;

  while (getline(file, line)) {
    cout << "Parse: " << line << "\n";
    const int length = line.length();
    char* char_arr = line.data();
    int mid = length / 2;
    // cout << "Length:" << length << " Mid:" << mid << endl;
    char found;

    for (int i = 0; i < mid; i++) {
      //   cout << char_arr[i];
      for (int j = mid; j < length; j++) {
        // cout << char_arr[j];
        if (char_arr[i] == char_arr[j]) {
          found = char_arr[i];
          break;
        }
      }
    }

    int ascii = (int)found;

    if (ascii >= 97 && ascii <= 122) {
      ascii -= 96;
    } else if (ascii >= 65 && ascii <= 90) {
      ascii -= 38;
    }

    cout << "Found char: " << found << ". Value is: " << ascii << endl;
    cout << "End Parse" << endl;
    ans += ascii;
  }

  cout << "Answer is: " << ans << endl;
  return ans;
}

int day3q2(bool test) {
  string file_name = (test) ? "day3" : "day3Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  int ans = 0;
  int group = 0;
  string line;
  string groupStr;
  vector<int> groupIdx;

  while (getline(file, line)) {
    // cout << "Parse: " << line << "\n";
    // cout << "Group: " << group << " => " << group % 3 << endl;
    groupStr.append(line);
    groupIdx.push_back(line.length());
    group++;

    if (group % 3 == 0) {
      map<char, int> charMap = {};
      char* char_arr = groupStr.data();
      //   cout << "Parsing group: " << group << ". " << groupStr << endl;
      //   cout << "parsing..." << endl;
      //   for (auto i : groupIdx) {
      //     cout << i << endl;
      //   }

      bool p1 = false, p2 = false;
      char found = 0;

      for (int i = 0; i < groupIdx[0]; i++) {
        char ch = char_arr[i];
        for (int j = groupIdx[0]; j < groupIdx[0] + groupIdx[1]; j++) {
          if (ch == char_arr[j]) {
            p1 = true;
            break;
          }
        }

        for (int j = groupIdx[0] + groupIdx[1]; j < groupStr.length(); j++) {
          if (ch == char_arr[j]) {
            p2 = true;
            break;
          }
        }

        if (p1 && p2) {
          found = ch;
          break;
        }

        p1 = false;
        p2 = false;
      }
      int ascii = (int)found;

      if (ascii >= 97 && ascii <= 122) {
        ascii -= 96;
      } else if (ascii >= 65 && ascii <= 90) {
        ascii -= 38;
      }

      cout << "Found char: " << found << ". Value is: " << ascii << endl;
      ans += ascii;
      //   cout << "End Parse" << endl;
      //   cout << "value:" << ascii << endl;
      cout << endl << "done" << endl;
      groupStr = "";
      groupIdx.clear();
    }

    // char* char_arr = line.data();
    // char found;

    // for (int i = 0; i < mid; i++) {
    //   //   cout << char_arr[i];
    //   for (int j = mid; j < length; j++) {
    //     // cout << char_arr[j];
    //     if (char_arr[i] == char_arr[j]) {
    //       found = char_arr[i];
    //       break;
    //     }
    //   }
    // }

    // int ascii = (int)found;

    // if (ascii >= 97 && ascii <= 122) {
    //   ascii -= 96;
    // } else if (ascii >= 65 && ascii <= 90) {
    //   ascii -= 38;
    // }

    // cout << "Found char: " << found << ". Value is: " << ascii << endl;
    // cout << "End Parse" << endl;
    // ans += ascii;
  }

  cout << "Answer is: " << ans << endl;
  return ans;
}