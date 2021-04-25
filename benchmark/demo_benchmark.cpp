#include <fstream>      // ifstream
#include <iostream>     // cout
#include <string>       // string, stoi
#include <string_view>  // string_view
#include <chrono>       // high_resolution_clock, duration_cast, nanoseconds

// подключаем вашу структуру данных
#include "data_structure.hpp"

using namespace std;
using namespace itis;

// абсолютный путь до набора данных и папки проекта
static constexpr auto kDatasetPath = string_view{PROJECT_DATASET_DIR};

int main() {
  const auto path = string(kDatasetPath);
  cout << "Path to the 'dataset/' folder: " << path << endl;

  int trials = 1;
  string files[1] = {"01"};
  SplayTree sTree;
  for(string elem : files) {
    for (int i = 0; i < trials; i++) {
      string line = "1";

      // тут вместо "insert" указываете метод, который будете тестировать
      auto input_file = ifstream(path + "/insert/data(100).txt");
      // вместо "data(100).txt" указываете файл с нужным набором тестовых данных

      if (input_file) {
        while (!line.empty()) {
          getline(input_file, line);
          if (line.empty()) {
            break;
          }
          sTree.insert(stoi(line));
        }
      }
      const auto time_point_before = chrono::steady_clock::now();

      // тут вместо "insert" вызываете метод, который тестируете
      sTree.insert(34524);

      const auto time_point_after = chrono::steady_clock::now();
      Node *curr = sTree.root;
      sTree.Clear(curr);
      input_file.close();
      const auto time_diff = time_point_after - time_point_before;

      const long time_elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(time_diff).count();

      cout << time_elapsed_ns << endl;
    }
  }
  return 0;
}