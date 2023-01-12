#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../utils/util.h"
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

struct Node {
  bool is_dir;
  int size;
  string name;
  Node* parent;
  vector<Node*> children;
};

void day7q1(bool test) {
  string file_name = (test) ? "day7" : "day7Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<int> result;
  string line;
  Node* pwd;
  Node* root = new Node{true, 0, "/", nullptr, {}};

  while (getline(file, line)) {
    // cout << line << "\n";
    char* cmd = line.data();

    if (cmd[0] == '$') {
      cout << "run command: " << line << endl;
      if (line.find("$ cd /") == 0) {
        // cout << "root" << endl;
        pwd = root;
      } else if (line.find("$ ls") == 0) {
        continue;
      } else if (line.find("$ cd ..") == 0) {
        pwd = pwd->parent;
      } else if (line.find("$ cd") == 0) {
        vector<string> v = splitString(line, " ");
        string dir = v.back();
        cout << "go into: " << v.back() << endl;
        // printVector(v);
        for (auto n : pwd->children) {
          if (n->name == dir) {
            pwd = n;
            break;
          }
        }
      } else {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
      }
    } else {
      if (line.find("dir") == 0) {
        vector<string> v = splitString(line, " ");
        Node* n = new Node{true, 0, v[1], pwd, {}};
        pwd->children.push_back(n);
      } else {
        vector<string> v = splitString(line, " ");
        cout << "list data: " << v[1] << " size: " << v[0] << endl;
        Node* tmp = pwd;
        while (tmp != nullptr) {
          tmp->size += stoi(v[0]);
          tmp = tmp->parent;
        }
      }
    }
  }

  int target = 100000, ans = 0;
  //   cout << "Answer is: " << ans << endl;
  std::stack<Node*> stack;
  stack.push(root);
  while (!stack.empty()) {
    Node* current = stack.top();
    stack.pop();
    //     // process current node
    //     std::cout << current->value << " ";
    if (current->size <= target) {
      ans += current->size;
    };
    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
      stack.push(*it);
    }
  }
  cout << "Answer is: " << ans << endl;
}

void day7q2(bool test) {
  string file_name = (test) ? "day7" : "day7Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  cout << path << endl;

  ifstream file(path);
  //   vector<int> result;
  string line;
  Node* pwd;
  Node* root = new Node{true, 0, "/", nullptr, {}};

  while (getline(file, line)) {
    char* cmd = line.data();

    if (cmd[0] == '$') {
      cout << "run command: " << line << endl;
      if (line.find("$ cd /") == 0) {
        pwd = root;
      } else if (line.find("$ ls") == 0) {
        continue;
      } else if (line.find("$ cd ..") == 0) {
        pwd = pwd->parent;
      } else if (line.find("$ cd") == 0) {
        vector<string> v = splitString(line, " ");
        string dir = v.back();
        for (auto n : pwd->children) {
          if (n->name == dir) {
            pwd = n;
            break;
          }
        }
      } else {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
      }
    } else {
      if (line.find("dir") == 0) {
        vector<string> v = splitString(line, " ");
        Node* n = new Node{true, 0, v[1], pwd, {}};
        pwd->children.push_back(n);
      } else {
        vector<string> v = splitString(line, " ");
        cout << "list data: " << v[1] << " size: " << v[0] << endl;
        Node* tmp = pwd;
        while (tmp != nullptr) {
          tmp->size += stoi(v[0]);
          tmp = tmp->parent;
        }
      }
    }
  }

  int total = 70000000, need = 30000000;
  int current_free_disk = total - root->size;
  int ans = root->size;
  std::stack<Node*> stack;
  stack.push(root);
  while (!stack.empty()) {
    Node* current = stack.top();
    stack.pop();
    if (current_free_disk + current->size > need) {
      if (current->size < ans) {
        ans = current->size;
      }
    };
    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
      stack.push(*it);
    }
  }
  cout << "Answer is: " << ans << endl;
}