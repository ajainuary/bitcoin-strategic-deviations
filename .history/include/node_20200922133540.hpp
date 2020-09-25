#ifndef NODE_CLASS
#define NODE_CLASS

// class Node {
//   int strategy;
// };

// class NodeEvent {
//  public:
//   NodeEvent(int i, int j) {
//     node_id = i;
//     round = j;
//   }
//   int node_id;
//   int round;
//   int strategy;
// };

class Block {
 public:
  Block(int round_no, double leftover_input, Block *prev_input = NULL)
      : round(round_no), prev(prev_input), leftover(leftover_input) {}
  int round;
  Block *prev;
  double leftover;
  /**
   * Compares the blocks according to the block reward
   */
  bool operator<(Block &left, Block &right) {
    return (left.leftover - double(left.round)) <
           (right.leftover - double(right.round));
  }
}
#endif