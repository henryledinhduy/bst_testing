#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BSTree.h"
#include <ctime>
#include <random>

using namespace std;

/**
  @Author: Duy Le-Dinh
  @Version: 0.1
  @Description:
    A Binary Search Tree Testing program to determine whether the Symmetric
    deletion algorithm or Asymmetric deletion algorithm is more efficient to
    the Average Path Length (APL = IPL / number of record).
*/

int main(int argc, char const *argv[]) {
  ofstream output;
  output.open("results.txt");

  BSTree bst;
  default_random_engine generator;
  uniform_int_distribution<int> distribution(1,2000);

  int random_number_1;
  int random_number_2;

  const int RECORD_POPULATION = 500;
  const int TEST_RUN = 100000;

  // Establishing the tree
  for (int i = 0; i < RECORD_POPULATION; i++) {
    random_number_1 = distribution(generator);
    bst.insert(random_number_1);
  }

  for (int i = 0; i < TEST_RUN; i++) {
    random_number_1 = distribution(generator);
    random_number_2 = bst.getRandomNode();
    bst.insert(random_number_1);

    // Change the Deletion Algorithm here to deleteA to use Asymmetric Deletion.
    bst.deleteS(random_number_2);
    bst.updateInfo();
    output << bst.getAPL() << "\n";
  }

  output.close();
  return 0;
}
