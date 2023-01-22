#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void day8q1(bool test) {
  string file_name = (test) ? "day8" : "day8Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<string> data;
  string line;

  while (getline(file, line)) {
    // cout << line << "\n";
    data.push_back(line);
  }

  const int N = data[0].length();
  int* array = new int[N * N];

  for (int i = 0; i < N; i++) {
    auto ch = data[i].data();
    for (int j = 0; j < N; j++) {
      *(array + (i * N) + j) = ch[j] - '0';
    }
  }
  int tmp, check;
  bool visible = true;
  //   int ans = 0;
  int ans = N * 4 - 4;
  for (int i = 1; i < N - 1; i++) {
    for (int j = 1; j < N - 1; j++) {
      auto curr = *(array + (i * N) + j);
      //   cout << *(array + (i * N) + j) << " ";
      // left
      visible = true;
      tmp = j - 1;
      while (tmp >= 0) {
        check = *(array + (i * N) + tmp);
        if (curr <= check) {
          visible = false;
          break;
        }
        tmp--;
      }
      if (visible) {
        ans++;
        continue;
      }

      // up
      visible = true;
      tmp = i - 1;
      while (tmp >= 0) {
        check = *(array + (tmp * N) + j);
        if (curr <= check) {
          visible = false;
          break;
        }
        tmp--;
      }
      if (visible) {
        ans++;
        continue;
      }

      // down
      visible = true;
      tmp = i + 1;
      while (tmp < N) {
        check = *(array + (tmp * N) + j);
        if (curr <= check) {
          visible = false;
          break;
        }
        tmp++;
      }
      if (visible) {
        ans++;
        continue;
      }

      // right
      visible = true;
      tmp = j + 1;
      while (tmp < N) {
        check = *(array + (i * N) + tmp);
        if (curr <= check) {
          visible = false;
          break;
        }
        tmp++;
      }
      if (visible) {
        ans++;
        continue;
      }
    }
  }
  //   cout << (N * 4 - 4) << endl;
  //   for (int i = 0; i < N; i++) {
  //     for (int j = 0; j < N; j++) {
  //       cout << *(array + (i * N) + j) << " ";
  //     }
  //     cout << endl;
  //   }
  //   delete[] array;

  cout << "Answer is: " << ans << endl;
}

void day8q2(bool test) {
  string file_name = (test) ? "day8" : "day8Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  vector<string> data;
  string line;

  while (getline(file, line)) {
    data.push_back(line);
  }

  const int N = data[0].length();
  int* array = new int[N * N];

  for (int i = 0; i < N; i++) {
    auto ch = data[i].data();
    for (int j = 0; j < N; j++) {
      *(array + (i * N) + j) = ch[j] - '0';
    }
  }
  int tmp, check, up, down, left, right;
  int ans = 0;
  for (int i = 1; i < N - 1; i++) {
    for (int j = 1; j < N - 1; j++) {
      auto curr = *(array + (i * N) + j);
      //   cout << *(array + (i * N) + j) << " ";
      // left
      tmp = j - 1;
      left = 0;
      while (tmp >= 0) {
        left++;
        check = *(array + (i * N) + tmp);
        if (curr <= check) {
          break;
        }
        tmp--;
      }

      // up
      tmp = i - 1;
      up = 0;
      while (tmp >= 0) {
        up++;
        check = *(array + (tmp * N) + j);
        if (curr <= check) {
          break;
        }
        tmp--;
      }

      // down
      tmp = i + 1;
      down = 0;
      while (tmp < N) {
        down++;
        check = *(array + (tmp * N) + j);
        if (curr <= check) {
          break;
        }
        tmp++;
      }

      // right
      tmp = j + 1;
      right = 0;
      while (tmp < N) {
        right++;
        check = *(array + (i * N) + tmp);
        if (curr <= check) {
          break;
        }
        tmp++;
      }

      if (up * down * left * right > ans) {
        ans = up * down * left * right;
      }
    }
  }

  cout << "Answer is: " << ans << endl;
}