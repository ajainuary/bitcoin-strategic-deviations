#ifndef NODE_CLASS
#define NODE_CLASS

class Node {
  int strategy;
};

class NodeEvent {
  int node_id;
  int round;

 public:
  NodeEvent(int i, int j) {
    node_id = i;
    round = j;
  }
};
#endif