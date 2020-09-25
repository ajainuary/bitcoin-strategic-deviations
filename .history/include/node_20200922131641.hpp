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