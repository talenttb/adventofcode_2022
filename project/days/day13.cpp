#include <any>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum KIND { VALUE, ARRAY };

// class Doc {
//  public:
//   KIND kind;
//   void* value;
//   Doc();
//   //   Doc(KIND k) : kind(k){};
//   Doc(KIND k) : kind(k) {
//     if (KIND::ARRAY == k) {
//       vector<Doc>* empty{};
//       this->value = empty;
//     }
//   };
//   Doc(KIND k, void* value) : kind(k), value(value){};
//   //   ~Doc() { cout << "!!!!!!" << endl; }
// };

class Doc2 {
 public:
  KIND kind;
  std::any value;
  bool closed;
  //   Doc2();
  Doc2(KIND k) : kind(k) {
    if (KIND::ARRAY == k) {
      vector<Doc2> empty{};
      this->value = empty;
    }
  };
  Doc2(KIND k, any value) : kind(k), value(value){};
  Doc2(KIND k, any value, bool closed) : kind(k), value(value), closed(closed){};
  void hoist() {
    this->kind = KIND::ARRAY;
    int v = any_cast<int>(this->value);
    Doc2 x = Doc2{KIND::VALUE, v};
    vector<Doc2> update{x};
    this->value = update;
  }
};

void deep_print(vector<Doc2> res, int repeat) {
  string s = "\t";
  stringstream rt;
  for (int i = 0; i < repeat; i++) {
    rt << s;
  }
  repeat++;
  for (size_t i = 0; i < res.size(); i++) {
    switch (res[i].kind) {
      case KIND::VALUE: {
        cout << rt.str() << "value: " << any_cast<int>(res[i].value) << endl;
        break;
      }
      case KIND::ARRAY: {
        auto v = any_cast<vector<Doc2>>(res[i].value);
        cout << rt.str() << "vector with size: " << v.size() << endl;
        deep_print(v, repeat);
        // cout << "value: " << any_cast<int>(res[i].value) << endl;
        break;
      }
    }
  }
}

// vector<Doc2> parser(string s) {
//   vector<Doc2> res = {};
//   //   vector<Doc2> res = {Doc2{KIND::ARRAY}};
//   //   , my_stack = {};
//   vector<bool> merge = {};
//   string buffer = "";
//   for (int i = 1; i < s.length(); i++) {
//     switch (s[i]) {
//       case ',': {
//         if (buffer != "") {
//           int t = stoi(buffer);
//           auto doc = Doc2{KIND::VALUE, t};
//           if (res.size() > 0) {
//             Doc2 item = res.back();
//             res.pop_back();
//             vector<Doc2> vec_ptr = any_cast<vector<Doc2>>(item.value);
//             vec_ptr.push_back(doc);
//             item.value = vec_ptr;
//             res.push_back(item);
//           } else {
//             res.push_back(doc);
//           }

//           // res.push_back(item);
//           //   Doc2 item = my_stack.back();
//           //   my_stack.pop_back();
//           //   vector<Doc2> vec_ptr = any_cast<vector<Doc2>>(item.value);
//           //   vec_ptr.push_back(doc);
//           //   item.value = vec_ptr;
//           //   res.push_back(item);
//         } else {
//           // res.push_back(my_stack.back());
//           // my_stack.pop_back();
//           if (merge.size() > 0) {
//             merge.pop_back();
//             Doc2 last = res.back();
//             res.pop_back();
//             Doc2 tail = res.back();
//             res.pop_back();
//             vector<Doc2> vec_ptr = any_cast<vector<Doc2>>(tail.value);
//             vec_ptr.push_back(last);
//             tail.value = vec_ptr;
//             res.push_back(tail);
//           }
//           //   res.push_back(Doc2{KIND::ARRAY});
//         }

//         // merge = false;
//         buffer = "";
//         break;
//       }
//       case ']': {
//         // merge = true;
//         merge.push_back(false);
//         if (buffer != "") {
//           int t = stoi(buffer);
//           auto doc = Doc2{KIND::VALUE, t};
//           Doc2 item = res.back();
//           res.pop_back();
//           if (item.kind == KIND::ARRAY) {
//             vector<Doc2> vec_ptr = any_cast<vector<Doc2>>(item.value);
//             vec_ptr.push_back(doc);
//             item.value = vec_ptr;
//             res.push_back(item);
//           } else {
//             res.push_back(doc);
//           }
//         } else {
//           res.push_back(Doc2{KIND::ARRAY});
//         }
//         buffer = "";
//         break;
//       }
//       case '[': {
//         res.push_back(Doc2{KIND::ARRAY});
//         break;
//       }
//       default: {
//         buffer += s[i];
//         break;
//       }
//     }
//   }
//   return res;
// }

vector<Doc2> parser2(string s) {
  vector<Doc2> res = {};
  string buffer = "";
  int closed = 0;
  for (int i = 1; i < s.length() - 1; i++) {
    switch (s[i]) {
      case ',': {
        if (buffer != "") {
          int t = stoi(buffer);
          auto doc = Doc2{KIND::VALUE, t};
          res.push_back(doc);
        }
        buffer = "";
        break;
      }
      case ']': {
        if (buffer != "") {
          int t = stoi(buffer);
          auto doc = Doc2{KIND::VALUE, t};
          res.push_back(doc);
        }

        // if (res[res.size() - 1].kind == KIND::VALUE) {
        for (int j = res.size() - 1; j >= 0; j--) {
          //   if (res[j].kind == KIND::ARRAY) {
          //     found++;
          //   }

          if (res[j].kind == KIND::ARRAY && !res[j].closed) {
            auto tmp = res[j];
            vector<Doc2> tail = any_cast<vector<Doc2>>(tmp.value);
            for (size_t k = j + 1; k < res.size(); k++) {
              tail.push_back(res[k]);
            }
            auto doc = Doc2{KIND::ARRAY, tail, true};
            res.erase(res.begin() + j, res.end());
            res.push_back(doc);
            break;
          }
        }
        closed--;

        buffer = "";
        break;
      }
      case '[': {
        closed++;
        res.push_back(Doc2{KIND::ARRAY});
        break;
      }
      default: {
        buffer += s[i];
        break;
      }
    }
  }
  if (buffer != "") {
    int t = stoi(buffer);
    auto doc = Doc2{KIND::VALUE, t};
    res.push_back(doc);
  }
  return res;
}

// bool compare(vector<Doc2> left, vector<Doc2> right) {
//   if (right.size() == 0) {
//     return false;
//   }

//   for (size_t i = 0; i < left.size(); i++) {
//     if (i > right.size() - 1) {
//       return false;
//     }
//     if (left[i].kind == KIND::VALUE && right[i].kind == KIND::VALUE) {
//       int left_v = any_cast<int>(left[i].value);
//       int right_v = any_cast<int>(right[i].value);
//       if (left_v > right_v) {
//         return false;
//       }
//       //   if ((left.size() != right.size()) && (i >= right.size() - 1)) {
//       //     return false;
//       //   }
//     } else if (left[i].kind == KIND::ARRAY && right[i].kind == KIND::ARRAY) {
//       auto left_v = any_cast<vector<Doc2>>(left[i].value);
//       auto right_v = any_cast<vector<Doc2>>(right[i].value);
//       if (!compare(left_v, right_v)) {
//         return false;
//       }
//       if ((left.size() != right.size()) && (i >= right.size() - 1)) {
//         return false;
//       }
//     } else if (left[i].kind == KIND::VALUE && right[i].kind == KIND::ARRAY) {
//       auto tmp = left[i];
//       tmp.hoist();
//       left.at(i) = tmp;
//       i--;
//       continue;
//     } else if (left[i].kind == KIND::ARRAY && right[i].kind == KIND::VALUE) {
//       auto tmp = right[i];
//       tmp.hoist();
//       right.at(i) = tmp;
//       i--;
//       continue;
//     } else {
//       assert(false && "unknown");
//     }

//     // switch (res[i].kind) {
//     //   case KIND::VALUE: {
//     //     cout << rt.str() << "value: " << any_cast<int>(res[i].value) << endl;
//     //     break;
//     //   }
//     //   case KIND::ARRAY: {
//     //     auto v = any_cast<vector<Doc2>>(res[i].value);
//     //     cout << rt.str() << "vector with size: " << v.size() << endl;
//     //     deep_print(v, repeat);
//     //     // cout << "value: " << any_cast<int>(res[i].value) << endl;
//     //     break;
//     //   }
//     // }
//   }
//   return true;
// }

int compare2(vector<Doc2> left, vector<Doc2> right) {
  while (left.size() > 0 && right.size() > 0) {
    auto right_item = right[0];
    auto left_item = left[0];
    if (left_item.kind == KIND::VALUE && right_item.kind == KIND::VALUE) {
      int left_v = any_cast<int>(left_item.value);
      int right_v = any_cast<int>(right_item.value);
      if (right_v > left_v) {
        return 1;
      } else if (left_v > right_v) {
        return -1;
      }
    } else if (left_item.kind == KIND::ARRAY && right_item.kind == KIND::ARRAY) {
      auto left_v = any_cast<vector<Doc2>>(left_item.value);
      auto right_v = any_cast<vector<Doc2>>(right_item.value);
      int com = compare2(left_v, right_v);
      if (com != 0) {
        return com;
      }
    } else if (left_item.kind == KIND::VALUE && right_item.kind == KIND::ARRAY) {
      auto tmp = left_item;
      tmp.hoist();
      left.at(0) = tmp;
      continue;
    } else if (left_item.kind == KIND::ARRAY && right_item.kind == KIND::VALUE) {
      auto tmp = right_item;
      tmp.hoist();
      right.at(0) = tmp;
      continue;
    } else {
      assert(false && "unknown");
    }
    left.erase(left.begin());
    right.erase(right.begin());
    // left.pop_front();
    // right.pop_front();
  }

  if (left.size() < right.size()) {
    return 1;
  } else if (left.size() > right.size()) {
    return -1;
  } else {
    return 0;
  }
}

void day13q1(bool test) {
  string file_name = (test) ? "day13" : "day13Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  std::cout << path << endl;

  ifstream file(path);
  //   vector<int> data;
  int ans = 0, row = 0, pair = 1;
  vector<Doc2> line1, line2;
  string line;

  //   void* ptr = new std::vector<int>{1, 2, 3};
  //   std::vector<int>* vec_ptr = static_cast<std::vector<int>*>(ptr);
  //   cout << (*vec_ptr)[0] << (*vec_ptr)[1] << (*vec_ptr)[2] << endl;

  //   void* ptr2 = new int{42};
  //   int* int_ptr = static_cast<int*>(ptr2);
  //   cout << *int_ptr << endl;

  //   int t = 123;
  //   auto doc = Doc2{KIND::VALUE, t};
  //   Doc2 test1(KIND::ARRAY);
  //   auto vec_ptr = any_cast<vector<Doc2>>(test1.value);
  //   vec_ptr.push_back(doc);
  //   test1.value = vec_ptr;

  //   vec_ptr = any_cast<vector<Doc2>>(test1.value);
  //   cout << "test 1 v2 loop start " << vec_ptr[0].kind << ", " << any_cast<int>(vec_ptr[0].value) << endl;
  //   for (auto&& i : vec_ptr) {
  //     cout << i.kind << ", " << any_cast<int>(i.value) << endl;
  //   }
  //   cout << "test 1 v2 loop end " << endl;

  //   Doc2 test2(KIND::ARRAY);
  //   vec_ptr = any_cast<vector<Doc2>>(test2.value);
  //   vec_ptr.push_back(doc);
  //   test2.value = vec_ptr;

  //   vec_ptr = any_cast<vector<Doc2>>(test2.value);
  //   vec_ptr.push_back(doc);
  //   int t2 = 333;
  //   auto doc2 = Doc2{KIND::VALUE, t2};
  //   vec_ptr.push_back(doc2);
  //   test2.value = vec_ptr;

  //   vec_ptr = any_cast<vector<Doc2>>(test2.value);
  //   for (auto&& i : vec_ptr) {
  //     cout << i.kind << ", " << any_cast<int>(i.value) << endl;
  //   }

  //   cout << "test 2 v2 loop end " << endl;

  //   string s = "[[1],[2,3,4]]";
  vector<Doc2> res, res1;
  //   auto res = parser(s);
  //   deep_print(res, 0);

  //   cout << "======" << endl;
  //   res = parser2("[[[]]]");
  //   deep_print(res, 0);
  //   cout << "======" << endl;
  //   res = parser2("[[]]");
  //   deep_print(res, 0);

  //   cout << "======" << endl;
  //   res = parser2("[1,2,3,4]");
  //   deep_print(res, 0);

  //   cout << "======" << endl;
  //   res = parser2("[1,[2],3,4]");
  //   deep_print(res, 0);

  //   cout << "======" << endl;
  //   res = parser2("[1,[2,[3]],4]");
  //   deep_print(res, 0);

  // cout << "======" << endl;
  // res = parser2("[1,[2,[3,[4,[5,6,7]]]],8,9]");
  // deep_print(res, 0);

  //   cout << "======" << endl;
  //   res = parser2("[[1,2],[],[]");
  //   deep_p rint(res, 0);
  //   cout << "======" << endl;
  //   res = parser2("[[1,4,7,4,8],[],[8,0,7,[],[]]]");
  //   deep_print(res, 0);
  //   cout << "======" << endl;
  //   res1 = parser2("[[10,[5,[0,2,5,3,3],[9,7,9],6],7,9,[2,9,[],4,0]],[8]]");
  //   deep_print(res1, 0);
  //   cout << compare2(res, res1) << endl;

  //   cout << "======" << endl;
  //   res = parser2("[[1,4,7,4,8]]");
  //   deep_print(res, 0);
  //   cout << "======" << endl;
  //   res1 = parser2("[[10,[5,[0,2,5,3,3],[9,7,9],6],7,9,[2,9,[],4,0]]]");
  //   deep_print(res1, 0);
  //   cout << compare2(res, res1) << endl;

  //   cout << "======" << endl;
  //   res1 = parser2("[3,[4],[5]]");
  //   res1 = parser2("[[3,[4],[5]]]");
  //   res1 = parser2("[[2,[3,[4],[5]]]]");
  //   res1 = parser2("[[1],[2,[3,[4],[5]]],[[[6],7]]]");
  //   res1 = parser2("[[1],[2,[3,[4],[5]]],[[[6],7],8,9,10]]");
  //   res1 = parser2("[[1],[2,[3,[4],[5]]],[[[6],7],8,9,10,[5,[5,10,9,9],7,0,[2,3]]],[[[1,5],[0],0],3,[[]]]]");
  //   deep_print(res1, 0);

  //   cout << "======" << endl;
  //   res = parser2("[[[9,10,[1,0,6],[1,2]],[[],[9,5,3],[7,3,10,1],0,0],5,10,[]],[]]");
  //   deep_print(res, 0);
  //   cout << "======" << endl;
  //   res1 = parser2("[[5,6,1,6],[8,6,5,[7,0,5,[0,4,3,6,6],[8,7,8,5]]],[[[1,2],9,1],10,4,3,[5,[5,10,9,9],7,0,[2,3]]],[[[1,5],[0],0],3,[[]]]]");
  //   deep_print(res1, 0);
  //   cout << compare2(res, res1) << endl;

  while (getline(file, line)) {
    // cout << line << "\n";
    if (line.empty()) {
      row = 0;
      cout << "Pair: " << pair << endl;
      cout << "Left:" << endl;
      deep_print(line1, 0);
      cout << "Right:" << endl;
      deep_print(line2, 0);
      int r = compare2(line1, line2);
      if (r == 1) {
        ans += pair;
        cout << pair << " -> OK(" << r << ")" << endl;
      } else {
        cout << pair << " -> FAIL(" << r << ")" << endl;
      }
      pair++;
      continue;
    }

    if (row == 0) {
      line1 = parser2(line);
    } else {
      line2 = parser2(line);
    }
    row++;
  }

  int r = compare2(line1, line2);
  if (r == 1) {
    ans += pair;
    cout << pair << " -> OK(" << r << ")" << endl;
  } else {
    cout << pair << " -> FAIL(" << r << ")" << endl;
  }

  std::cout << "Answer is: " << ans << endl;
}

void day13q2(bool test) {
  string file_name = (test) ? "day13" : "day13Test";
  string path = "/Users/liyu/talenttb/adventofcode_2022/project/inputs/" + file_name;

  std::cout << path << endl;

  ifstream file(path);
  int ans = 1;
  vector<vector<Doc2>> data;
  vector<Doc2> parsed_data;
  string line;

  while (getline(file, line)) {
    // cout << line << "\n";
    if (line.empty()) {
      continue;
    }

    parsed_data = parser2(line);

    if (data.size() == 0) {
      data.push_back(parsed_data);
      continue;
    }

    for (int i = 0; i < data.size(); i++) {
      int r = compare2(parsed_data, data[i]);
      if (i == data.size() - 1 && r == -1) {
        data.push_back(parsed_data);
        break;
      } else if (r == 1) {
        data.insert(data.begin() + i, parsed_data);
        break;
      } else if (i == 0 && r == 1) {
        data.insert(data.begin(), parsed_data);
        break;
      }
    }
  }

  auto insert_2 = parser2("[[2]]");
  for (int i = 0; i < data.size(); i++) {
    int r = compare2(insert_2, data[i]);
    if (r == 1) {
      cout << "insert [[2]] at: " << i << endl;
      ans *= i + 1;
      data.insert(data.begin() + i, insert_2);
      break;
    }
  }
  auto insert_6 = parser2("[[6]]");
  for (int i = 0; i < data.size(); i++) {
    int r = compare2(insert_6, data[i]);
    if (i == data.size() - 1 && r == -1) {
      data.push_back(insert_6);
      break;
    } else if (r == 1) {
      cout << "insert [[6]] at: " << i << endl;
      ans *= i + 1;
      data.insert(data.begin() + i, insert_6);
      break;
    } else if (i == 0 && r == 1) {
      data.insert(data.begin(), insert_6);
      break;
    }
  }

  for (int i = 0; i < data.size(); i++) {
    cout << endl << "====== INDEX: " << i << " ========" << endl;
    deep_print(data[i], 0);
    cout << "=========================" << endl;
  }

  std::cout << "Answer is: " << ans << endl;
}