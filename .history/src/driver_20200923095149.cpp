#include <bits/stdc++.h>
using namespace std;
#include "distance_matrix.hpp"
#include "node.hpp"
#include "randomness_matrix.hpp"
int Block::nextID = 0;
int Block::max_height = 0;
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
  D.print();
  array<double, 4> strategy_space = {1, 0.75, 0.5, 0.25};
  Randomness_matrix R(n, r, argv[4]);
  list<Block> mined;
  mined.push_back(Block());
  double p = 0.01;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < n; j++) {
      if (R[i][j] < p) {
        for (auto it = mined.begin();
             it->creator == -1 || it->round < i - D[it->creator][j]; ++it) {
          mined.push_back(Block(i, j, 1, it));
        }
      }
    }
  }
  cout << "Total Blocks Mined: " << mined.size() << endl;
  auto min_it = mined.end();
  double min_var = double(INT_MAX);
  for (auto it = mined.begin(); it != mined.end(); it++) {
    if (it->height == Block::max_height) {
      double mean = it->total_chain_reward() / double(it->height);
      double variance = it->total_variance(mean);
      list<Block> proposed_chain;
      it->chain(proposed_chain);
      for (auto it2 = proposed_chain.begin(); it2 != proposed_chain.end();
           it2++) {
        cerr << it2->reward << ',';
      }
      for (auto it2 = proposed_chain.begin(); it2 != proposed_chain.end();
           it2++) {
        cerr << it2->leftover << ',';
      }
      cerr << endl;
      double var = variance / mean;
      if (var < min_var) {
        min_it = it;
        min_var = var;
      }
    }
  }
  list<Block> fair_chain;
  min_it->chain(fair_chain);
  cout << "Fair Chain: " << endl;
  for (auto it = fair_chain.begin(); it != fair_chain.end(); ++it) {
    cout << "Miner : " << it->creator << " Reward: " << setprecision(5)
         << it->reward << " Leftover: " << it->leftover
         << " Strategy: " << it->strategy << endl;
  }
  return 0;
}