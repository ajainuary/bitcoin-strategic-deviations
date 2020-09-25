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
const double BLOCK_SIZE = 4;

class Block {
 public:
  Block(int round_no, double strategy, list<Block>::iterator pointer)
      : round(round_no), prev(pointer), leftover(leftover_input) {}
  /**
   * Genesis Block
   */
  Block() : round(-1), leftover(0) {}
  int round;
  list<Block>::iterator prev;
  double leftover;
  double reward;
  double creator;
  double offer(int round_no) { return double(round_no - round) + leftover; }
};
#endif