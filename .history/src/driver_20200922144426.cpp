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
    auto last_round_begin = prev_round_begin;
    for (int j = 0; j < n; j++) {
      if (R[i][j] < p) {
        for (auto it = last_round_begin; it->round != i;
             ++it, ++last_round_begin) {
          for (int k = 0; k < 4; k++) {
            cerr << "Block with leftover " << strategy_space[k] * (it->offer(i))
                 << " produced by " << j << endl;
            mined.push_back(Block(i, strategy_space[k] * (it->offer(i)), it));
            ++next_round_begin;
          }
        }
      }
      prev_round_begin = next_round_begin;
    }
  }
  cout << mined.size() << endl;
  return 0;
}