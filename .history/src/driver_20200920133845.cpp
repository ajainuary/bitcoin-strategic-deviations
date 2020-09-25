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
  vector<Node> nodes(n);
  Randomness_matrix R(n, r, argv[4]);
  vector<NodeEvent> events;
  double p = 0.01;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < n; j++) {
      if (R[i][j] < p) {
        events.push_back(NodeEvent(j, i));
      }
    }
  }
  return 0;
}