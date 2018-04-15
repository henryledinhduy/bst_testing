#include <iostream>
#include "BSTree.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


/*********************** CONSTRUCTOR - DESTRUCTOR ****************************/

Node::Node(int record) : record(record) {
  left = NULL;
  right = NULL;
}

BSTree::BSTree() {
  root_ = NULL;
  n_counter_ = 0;
  ipl_ = 0;
  direction_ = false;
}

BSTree::~BSTree() {
  // There is no need for a destructor in this case. 
}


/**************************** PUBLIC FUNCTIONS *******************************/

/**
  void BSTree::insert(const int number)

  @DESCRIPTION:
    Function insert the a number to the Binary Search Tree.
    The detail implementation is hidden behind insert_p(...) method.
  @PARAMETERS:
    number: an integer number.
  @RETURN: void.
*/
void BSTree::insert(const int number) {
  if (root_ == NULL) {
    root_ = new Node(number);
  } else {
    insert_p(number, root_);
  }
}

/**
  void BSTree::print()

  @DESCRIPTION:
    Function prints the Binary Search Tree to the screen.
    The detail implementation is hidden behind print_p(...) method.
  @PARAMETERS: none
  @RETURN: void.
  @IMPORTANT: updateInfo() need to be called to get the newest status.
*/
void BSTree::print() const {
  std::cout << "Number of Node: " << n_counter_ << '\n';
  print_p(root_);
}

/**
  int BSTree::getIPL()

  @DESCRIPTION:
    Function returns the Internal Path Length of the Tree
  @PARAMETERS: none
  @RETURN: integer number.
  @IMPORTANT: updateInfo() need to be called to get the newest status.
*/
int BSTree::getIPL() const {
  return ipl_;
}

/**
  int BSTree::getAPL()

  @DESCRIPTION:
    Function returns the Average Path Length of the Tree
    APL = ipl/Number of Nodes in the tree
  @PARAMETERS: none
  @RETURN: integer number.
  @IMPORTANT: updateInfo() need to be called to get the newest status.
*/
int BSTree::getAPL() const {
  return ipl_/n_counter_;
}

/**
  void BSTree::deleteS()

  @DESCRIPTION:
    Function with Symmetric Deletion Algorithm,
    Symmetric Deletion Algorithm: Replaces the root root either by the smallest
    root of the root's right branch or the biggest root of the root's left branch.
  @PARAMETERS: an integer number
  @RETURN: none
*/
void BSTree::deleteS(const int value) {
  if (direction_) {
    root_ = leftDelete(root_, value);
    direction_ = !direction_;
  } else {
    root_ = rightDelete(root_, value);
    direction_ = !direction_;
  }
}

/**
  void BSTree::deleteA()

  @DESCRIPTION:
    Public function with Asymmetric Deletion Algorithm,
    Asymmetric Deletion Algorithm: Replace the root root by the smallest root of
    the root's right branch.
  @PARAMETERS: an integer number that need to be deleted
  @RETURN: none
*/
void BSTree::deleteA(const int value) {
  root_ = rightDelete(root_, value);
}

/**
  void BSTree::updateInfo()

  @DESCRIPTION:
    Function updates the root counter, re-calculate the internal path length
    and the depth of each root.
    Need to be called after change occurs and before print(), getIPL(), getAPL()
  @PARAMETERS: none
  @RETURN: none
*/
void BSTree::updateInfo() {
  n_counter_ = 0;
  ipl_ = 0;
  updateInfo_p(root_, 0);
}

/**
  void BSTree::getRandomNode()

  @DESCRIPTION:
    Function return a random node's record.
  @PARAMETERS: none
  @RETURN: integer number
*/
int BSTree::getRandomNode() {
  getAllNodeRecord_p(root_);
  srand(time(0));
  return node_[rand() % node_.size() - 1];
}

/***************************** PRIVATE FUNCTIONS *****************************/


/**
  void BSTree::insert_p(const int number, Node* root)

  @DESCRIPTION:
    Private function that is called in BSTree::insert(), this function insert
    a number to the correct position of a Binary Search Tree.
  @PARAMETERS:
    number: an integer number.
    root: a Node pointer
  @RETURN: none.
*/
void BSTree::insert_p(const int number, Node* root) {
  if (root->record > number) {
    if (root->left == NULL) {
      root->left = new Node(number);
    } else insert_p(number, root->left);
  } else {
      if (root->right == NULL) {
        root->right = new Node(number);
    } else insert_p(number, root->right);
  }
}

/**
  void BSTree::print_p(Node *root)

  @DESCRIPTION:
    Private function that is called in BSTree::print(),
    this function prints the Binary Search Tree to the screen in order.
  @PARAMETERS:
    root: the root_ pointer.
  @RETURN: none.
*/
void BSTree::print_p(Node *root) const {
  if (root != NULL) {
    print_p(root->left);
    std::cout << root->record << '\n';
    print_p(root->right);
  }
}

/**
  void BSTree::updateInfo_p(Node* root, int depth)

  @DESCRIPTION:
    Use for public function updateInfo()
  @PARAMETERS:
    root: the root_ pointer
    depth: 0
  @RETURN: integer number.
*/
void BSTree::updateInfo_p(Node* root, int depth) {
  if (root != NULL) {
    root_->depth = depth;
    ipl_ += depth;
    n_counter_++;
    updateInfo_p(root->left, depth + ONE_INCREMENT);
    updateInfo_p(root->right, depth + ONE_INCREMENT);
  }
}


/**
  void BSTree::rightDelete()

  @DESCRIPTION:
    Replace the deleted node by node in the right subtree.
  @PARAMETERS:
    root: a Node pointer;
    value: the record to be deleted.
  @RETURN: none.
*/

Node* BSTree::rightDelete(Node* root, const int value) {
  if (root == NULL) {
      return root;
  } else if (value < root->record) {
      root->left = rightDelete(root->left, value);
  } else if (value > root->record) {
      root->right = rightDelete(root->right, value);
  } else {
      /* Case 1: No successor */
      if (root->right == NULL) {
          Node *temp = root;
          root = root->left;
          delete temp;
          return root;
      /* Case 2: Successor is the right child */
      } else if (root->right->left == NULL) {
          Node *temp = root;
          root->right->left = root->left;
          root = root->right;
          delete temp;
          return root;
      /* Case 3: Successor is the leftmost child in the right subtree */
      } else {
          Node *temp = root;
          Node *succPtr = root->right;
          // Traverse to the leftmost child of the right subtree
          while (succPtr->left->left != NULL) {
            succPtr = succPtr->left;
          }
          Node *successor = succPtr->left;
          succPtr->left = successor->right;
          successor->left = root->left;
          successor->right = root->right;
          root = successor;
          delete temp;
          return root;
      }
  }
}

/**
  void BSTree::leftDelete()

  @DESCRIPTION:
    Replace the deleted node by it's left side
  @PARAMETERS:
    root: A Node pointer
    value: the record to be deleted
  @RETURN: none.
*/
Node* BSTree::leftDelete(Node* root, const int value) {
  if (root == NULL) {
      return root;
  } else if (value < root->record) {
      root->left = rightDelete(root->left, value);
  } else if (value > root->record) {
      root->right = rightDelete(root->right, value);
  } else {
      /* Case 1: No successor */
      if (root->left == NULL) {
          Node *temp = root;
          root = root->right;
          delete temp;
          return root;
      /* Case 2: Predecessor is the right child */
      } else if (root->left->right == NULL) {
          Node *temp = root;
          root->left->right = root->right;
          root = root->left;
          delete temp;
          return root;
      /* Case 3: Predecessor is the rightmost child in the right subtree */
      } else {
          Node *temp = root;
          Node *succPtr = root->left;
          // Traverse to the right child of the left subtree
          while (succPtr->right->right != NULL) {
            succPtr = succPtr->right;
          }
          Node *successor = succPtr->right;
          succPtr->right = successor->left;
          successor->right = root->right;
          successor->left = root->left;
          root = successor;
          delete temp;
          return root;
      }
  }
}

/**
  void BSTree::getAllNodeRecord_p(Node* root)

  @DESCRIPTION:
    This is for getRandomNode() function. It pushes all node in to a vector so
    that the getRandomNode() can get one.
    I am not happy with this but it does the trick well.
  @PARAMETERS:
    root: A Node pointer
  @RETURN: none.
*/
void BSTree::getAllNodeRecord_p(Node* root) {
  if (root!= NULL) {
    getAllNodeRecord_p(root->left);
    node_.push_back(root->record);
    getAllNodeRecord_p(root->right);
  }
}
