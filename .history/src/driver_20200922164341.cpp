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
  mined.push_back(Block());
  double p = 0.01;
  auto last_round_begin = mined.begin();
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < n; j++) {
      if (R[i][j] < p) {
        for (auto it = last_round_begin; it->round != i;
             ++it, ++last_round_begin) {
          for (int k = 0; k < 4; k++) {
            mined.push_back(Block(i, j, strategy_space[k], it));
          }
        }
      }
    }
  }
  cout << "Total Blocks Mined: " << mined.size() << endl;
  auto min_it = mined.end();
  double min_var = double(INT_MAX);
  for (auto it = mined.begin(); it != mined.end(); it++) {
    if (it->height == Block::max_height) {
      double var =
          it->total_variance(it->total_chain_reward() / double(it->height));
      if (var < min_var) {
        min_it = it;
        min_var =
      }
    }
  }
  return 0;
}