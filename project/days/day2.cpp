#include "day2.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "../utils/util.h"
using namespace std;

int day2q1(bool test) {
  string file_name = (test) ? "day2" : "day2Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  string line;
  int result = 0;
  //   vector<int> group;
  map<string, int> rps_map = {{"LOST", 0}, {"DRAW", 3}, {"WON", 6}, {"X", 1}, {"Y", 2}, {"Z", 3}};
  while (getline(file, line)) {
    // cout << line << "\n";
    vector<string> v = splitString(line, " ");
    // cout << v[0] << " ~~~ " << v[1] << endl;
    // 0 if you lost, 3 if the score was a draw, and 6 if you won
    // 1 for Rock, 2 for Paper, and 3 for Scissors
    // A for Rock, B for Paper, and C for Scissors
    // X for Rock, Y for Paper, and Z for Scissors
    auto game = v[0] + v[1];
    int score = 0;
    // cout << game << endl;
    score += rps_map[v[1]];
    if (game == "AX") {
      score += rps_map["DRAW"];
    } else if (game == "AY") {
      score += rps_map["WON"];
    } else if (game == "AZ") {
      score += rps_map["LOST"];
    } else if (game == "BX") {
      score += rps_map["LOST"];
    } else if (game == "BY") {
      score += rps_map["DRAW"];
    } else if (game == "BZ") {
      score += rps_map["WON"];
    } else if (game == "CX") {
      score += rps_map["WON"];
    } else if (game == "CY") {
      score += rps_map["LOST"];
    } else if (game == "CZ") {
      score += rps_map["DRAW"];
    } else {
    }

    cout << "Round: " << game << ". Score: " << score << endl;
    result += score;
  }
  file.close();
  cout << "Answer: " << result << endl;
  cout << "Done" << endl;
  return result;
}

int day2q2(bool test) {
  string file_name = (test) ? "day2" : "day2Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  string line;
  int result = 0;
  map<string, int> rps_map = {{"X", 0}, {"Y", 3}, {"Z", 6}};
  while (getline(file, line)) {
    vector<string> v = splitString(line, " ");
    // 0 if you lost, 3 if the score was a draw, and 6 if you won
    // 1 for Rock, 2 for Paper, and 3 for Scissors
    // A for Rock, B for Paper, and C for Scissors
    // X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win
    auto game = v[0] + v[1];
    int score = 0;
    // cout << game << endl;
    score += rps_map[v[1]];
    if (game == "AX") {
      score += 3;
    } else if (game == "AY") {
      score += 1;
    } else if (game == "AZ") {
      score += 2;
    } else if (game == "BX") {
      score += 1;
    } else if (game == "BY") {
      score += 2;
    } else if (game == "BZ") {
      score += 3;
    } else if (game == "CX") {
      score += 2;
    } else if (game == "CY") {
      score += 3;
    } else if (game == "CZ") {
      score += 1;
    } else {
    }

    cout << "Round: " << game << ". Score: " << score << endl;
    result += score;
  }
  file.close();
  cout << "Answer: " << result << endl;
  cout << "Done" << endl;
  return result;
}