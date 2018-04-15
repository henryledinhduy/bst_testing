#ifndef BSTree_
#define BSTree_

#include <vector>
/**
  @Author: Duy Le-Dinh
  @Version: 0.1
  @Description:
    A Binary Search Tree Library.
*/
const int DEPTH_OF_ROOT = 0;
const int ONE_INCREMENT = 1;

struct Node {
  int record;
  int depth;
  Node *left;
  Node *right;

  Node(int record);
};

class BSTree {
 public:
  BSTree();
  ~BSTree();

  void insert(const int number);
  void print() const;
  int getIPL() const;
  int getAPL() const;
  void deleteS(const int value);
  void deleteA(const int value);
  void updateInfo();
  int getRandomNode();

 private:
  Node *root_;
  int n_counter_;  // Node Counter
  int ipl_;        // Internal Path Length
  bool direction_;
  std::vector<int> node_;

  void insert_p(const int number, Node* root_node);
  void print_p(Node* root_node) const;
  Node* rightDelete(Node* root_node, const int value);
  Node* leftDelete(Node* root_node, const int value);
  void updateInfo_p(Node* root_node, int depth);
  void getAllNodeRecord_p(Node* root_node);

};

#endif
