#include <iostream>
#include <fstream>
#include "BSTree.h"
#include <random>
#include <string>

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
  // Test setting
  const int RECORD_POPULATION = 500;
  const int TEST_RUN = 10000;
  const string file_name = "result.txt";
  const bool random = true;
  const bool symmetric = true;
  const int SEED = 1;

  ofstream output;
  output.open(file_name);

  BSTree bst;
  default_random_engine generator;
  generator.seed(SEED);
  uniform_int_distribution<int> distribution(1,10000);

  int random_number_1;
  int random_number_2;

  // Establishing the tree
  for (int i = 0; i < RECORD_POPULATION; i++) {
    random_number_1 = distribution(generator);
    bst.insert(random_number_1);
  }

  // Performing insert and delete
  for (int i = 0; i < TEST_RUN; i++) {
    random_number_1 = random ? distribution(generator): i;
    random_number_2 = bst.getRandomNode();
    bst.insert(random_number_1);

    if (symmetric) bst.deleteS(random_number_2);
    else bst.deleteA(random_number_2);

    bst.updateInfo();
    output << bst.getAPL() << "\n";
  }

  output.close();
  return 0;
}
