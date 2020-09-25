#include <bits/stdc++.h>
using namespace std;
#include "distance_matrix.hpp"
#include "node.hpp"
#include "randomness_matrix.hpp"
int Block::nextID = 0;
int Block::max_height = 0;
int no_blocks[100] = {0};

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
  // D.print();
  array<double, 4> strategy_space = {1, 0.75, 0.5, 0.25};
  Randomness_matrix R(n, r, argv[4]);
  list<Block> mined;
  mined.push_back(Block());
  double p = 0.02;
  for (int i = 0; i < r; i++) {
    cout << "Round " << i << ": " << endl;
    for (int j = 0; j < n; j++) {
      if (R[i][j] < p) {
        cout << "Miner " << j << endl;
        int longest_chain_length = 0;
        for (auto it = mined.begin(); it != mined.end(); ++it) {
          if (it->creator == -1 || it->round <= i - D[it->creator][j])
            longest_chain_length = max(it->height, longest_chain_length);
        }
        for (auto it = mined.begin(); it != mined.end(); ++it) {
          if (it->height == longest_chain_length) {
            mined.push_back(
                Block(i, (it->creator == -1) ? i : (i - D[it->creator][j] + 1),
                      j, it));
          }
        }
      }
    }
  }
  cout << "Total Blocks Mined: " << mined.size() << endl;
  auto min_it = mined.end(), first_it = mined.end();
  double min_var = double(INT_MAX);
  vector<double> rewards(100, 0);
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
        cerr << it2->creator << ',';
        rewards[it2->creator] += it2->reward;
        no_blocks[it2->creator]++;
      }
      cerr << endl;
      //     double var = variance / mean;
      //     if (var < min_var) {
      //       min_it = it;
      //       min_var = var;
      //     }
      if (first_it == mined.end()) {
        first_it = it;
      }
    }
  }
  // for (int i = 0; i < 99; i++) {
  //   cerr << rewards[i] << ',';
  // }
  // cerr << rewards[100] << endl;
  // for (int i = 0; i < 99; i++) {
  //   cerr << no_blocks[i] << ',';
  // }
  // cerr << no_blocks[100] << endl;
  // list<Block> fair_chain;
  // min_it->chain(fair_chain);
  // cout << "Fair Chain: " << endl;
  // for (auto it = fair_chain.begin(); it != fair_chain.end(); ++it) {
  //   cout << "Miner : " << it->creator << " Reward: " << setprecision(5)
  //        << it->reward << " Leftover: " << it->leftover
  //        << " Strategy: " << it->strategy << endl;
  // }
  list<Block> first_chain;
  first_it->chain(first_chain);
  cout << "First Chain: " << endl;
  for (auto it = first_chain.begin(); it != first_chain.end(); ++it) {
    cout << "Miner : " << it->creator << " Reward: " << setprecision(5)
         << it->reward << " Leftover: " << it->leftover
         << " Strategy: " << it->strategy << endl;
  }
  // cout << "Slow: " << slow << " Fast: " << fast << endl;
  return 0;
}