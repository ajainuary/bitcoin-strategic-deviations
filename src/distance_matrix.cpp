#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include "distance_matrix.hpp"
Distance_matrix::Distance_matrix(int size, string filename) {
  n = size;
  matrix = vector<vector<int>>(n, vector<int>(n));
  ifstream inputFile(filename);
  int l = 0;

  while (inputFile) {
    l++;
    string s;
    if (!getline(inputFile, s)) break;
    if (s[0] != '#') {
      istringstream ss(s);
      vector<int> record;
      int i = 0;
      while (ss) {
        i++;
        string line;
        if (!getline(ss, line, ',')) break;
        try {
          matrix[l - 1][i - 1] = stoi(line);
        } catch (const std::invalid_argument &e) {
          cout << "NaN found in file " << filename << " line " << l
               << " position " << i << endl;
          e.what();
        }
      }
    }
  }

  if (!inputFile.eof()) {
    cerr << "Could not read file " << filename << "\n";
    __throw_invalid_argument("File not found.");
  }
}

void Distance_matrix::print() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << setw(3) << matrix[i][j] << ' ';
    }
    cout << '\n';
  }
}