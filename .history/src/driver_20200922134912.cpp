#include <bits/stdc++.h>
using namespace std;
#include "distance_matrix.hpp"
#include "node.hpp"
#include "randomness_matrix.hpp"

int main(int argc, char *argv[]) {
  if (argc != 5) {
    cerr << "Incorrect Usage!" << endl;
    cerr << "Correct Usage: ./simulator <number_of_nodes> "
            "<distance_matrix_csv> <number_of_rounds> <randomness_file>"
         << endl;
    return 1;
  }
  int n = stoi(argv[1]), r = stoi(argv[3]);
  Distance_matrix D(n, argv[2]);
  //   D.print();
  array<double, 4> strategy_space = {1.0, 0.75, 0.5, 0.25};
  Randomness_matrix R(n, r, argv[4]);
  list<Block> mined;
  double p = 0.01;
  for (int i = 0; i < r; i++) {
    list<Block> transit;
    for (int j = 0; j < n; j++) {
      if (R[i][j] < p) {
        for (auto it = mined.begin(); it != mined.end(); it++) {
          for (int k = 0; k < 4; k++) {
            transit.push_back(Block(i, strategy_space[k] * (it->offer(i)), it))
          }
        }
      }
    }
  }
  return 0;
}