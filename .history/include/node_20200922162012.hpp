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
 protected:
  static int nextID;

 public:
  int Block::nextID = 0;
  Block(int round_no, int creator_node, double strategy,
        list<Block>::iterator pointer)
      : round(round_no), prev(pointer), creator(creator_node) {
    reward = min(BLOCK_SIZE,
                 (pointer->leftover + (round_no - pointer->round)) * strategy);
    leftover = (pointer->leftover + (round_no - pointer->round)) - reward;
    ID = nextID++;
  }
  /**
   * Genesis Block
   */
  Block() : round(-1), leftover(0), creator(-1), reward(0) { ID = nextID++; }
  int ID;
  int round;
  int height;
  list<Block>::iterator prev;
  double leftover;
  double reward;
  double creator;
};
#endif