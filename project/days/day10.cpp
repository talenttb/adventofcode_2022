#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void day10q1(bool test) {
  string file_name = (test) ? "day10" : "day10Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<int> data;
  // register
  int x = 1;
  int ans = 0;
  string line;

  while (getline(file, line)) {
    stringstream ss(line);
    string token;
    vector<string> output;

    while (getline(ss, token, ' ')) {
      output.push_back(token);
    }
    // cout << output[0] << ";" << output[1] << "\n";

    if (output[0] == "noop") {
      //   x++;
      data.push_back(x);
    } else if (output[0] == "addx") {
      data.push_back(x);

      //   cout << stoi(output[1]) << "\n";
      x += stoi(output[1]);
      data.push_back(x);
    } else {
      assert("err");
    }
  }

  int check_list[] = {20, 60, 100, 140, 180, 220};

  for (auto idx : check_list) {
    cout << "idx: " << idx << "; data: " << data.at(idx - 2) << endl;
    ans += idx * data.at(idx - 2);
  }

  cout << "Answer is: " << ans << endl;
}

void day10q2(bool test) {
  string file_name = (test) ? "day10" : "day10Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<int> data;
  // register
  int x = 1, pos = 0;
  int ans = 0;
  string line, result = "";
  string ori_sprite = "###.............................................................................", sprite = ori_sprite;
  //   sprite.insert(sprite.begin(), 20 - sprite.length(), '.');

  while (getline(file, line)) {
    stringstream ss(line);
    string token;
    vector<string> output;

    while (getline(ss, token, ' ')) {
      output.push_back(token);
    }
    // cout << output[0] << ";" << output[1] << "\n";

    if (output[0] == "noop") {
      result += sprite.at(pos);
      pos++;
      if (pos > 39) {
        pos = 0;
        cout << result << endl;
        result = "";
      }
    } else if (output[0] == "addx") {
      result += sprite.at(pos);
      pos++;
      if (pos > 39) {
        pos = 0;
        cout << result << endl;
        result = "";
      }
      result += sprite.at(pos);
      pos++;
      if (pos > 39) {
        pos = 0;
        cout << result << endl;
        result = "";
      }
      x += stoi(output[1]);

      sprite = string(x - 1 < 0 ? 0 : x - 1, '.') + ori_sprite;
    } else {
      assert("err");
    }
  }

  cout << "Answer is: RZHFGJCB" << endl;
}