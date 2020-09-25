#ifndef RANDOMNESS_MATRIX
#define RANDOMNESS_MATRIX

class Randomness_matrix {
  vector<vector<double>> matrix;

 public:
  /**
   * Number of nodes in the matrix and the number of rounds, the size of matrix
   * will be nxr
   */
  int n, r;
  /**
   * Initialize a Randomness Matrix from a CSV file
   * @param n   Size of the distance matrix
   * @param file    The filename to load
   */
  Randomness_matrix(int, int, string);
  /**
   * Dump the matrix contents
   */
  void print();
  const vector<double>& operator[](int i) const { return matrix[i]; }
};
#endif