#include <iostream>
#include <fstream>
#include <cstdlib>
#include "BSTree.h"
using namespace std;

/**
  @Author: Duy Le-Dinh
  @Version: 1.0
  @Description:
    A Binary Search Tree Testing program to determine whether the Symmetric
    deletion algorithm or Asymmetric deletion algorithm is more efficient to
    the Average Path Length (APL = IPL / number of record).
*/

int main(int argc, char const *argv[]) {
  ofstream output;
  output.open("resutls");

  BSTree bst;
  int random_number;
  srand(1);
  for (int i = 0; i < 500; i++) {
    random_number = rand() % 5000;
    bst.insert(random_number);
    bst.updateInfo();

    output << "Inserted: " << random_number <<"\t\tAPL: " << bst.getAPL() << "\n";

  }

  output.close();
  return 0;
}
