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
  static int nextID;
  static int max_height;
  int ID;
  int round;
  int height;
  list<Block>::iterator prev;
  double leftover;
  double reward;
  int creator;
  double strategy;
  Block(int round_no, int creator_node, double strategy_input,
        list<Block>::iterator pointer)
      : round(round_no),
        prev(pointer),
        creator(creator_node),
        strategy(strategy_input) {
    reward = min(BLOCK_SIZE, (pointer->leftover + (round_no - pointer->round)) *
                                 strategy_input);
    leftover = (pointer->leftover + (round_no - pointer->round)) - reward;
    height = pointer->height + 1;
    max_height = max(max_height, height);
    ID = nextID++;
  }
  /**
   * Genesis Block
   */
  Block() : round(-1), leftover(0), creator(-1), reward(0), height(0) {
    ID = nextID++;
  }
  double total_chain_reward() {
    if (round == -1) {
      return 0;
    }
    return reward + prev->total_chain_reward();
  }
  double total_variance(double mean) {
    if (round == -1) {
      return 0;
    }
    return ((reward - mean) * (reward - mean)) + prev->total_variance(mean);
  }
  void chain(list<Block> &output) {
    if (round == -1) {
      return;
    }
    prev->chain(output);
    output.push_back(*this);
    return;
  }
};
#endif