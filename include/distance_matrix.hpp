#ifndef DISTANCE_MATRIX
#define DISTANCE_MATRIX

class Distance_matrix {
  vector<vector<int>> matrix;

 public:
  /**
   * Number of nodes in the matrix, the size of matrix will be nxn
   */
  int n;
  /**
   * Initialize a Distance Matrix from a CSV file
   * @param n   Size of the distance matrix
   * @param file    The filename to load
   */
  Distance_matrix(int, string);
  /**
   * Dump the matrix contents
   */
  void print();
  const vector<int>& operator[](int i) const { return matrix[i]; }
};
#endif