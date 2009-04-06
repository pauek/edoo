
#include <iostream>
using namespace std;

int main() {
  bool *pT = new bool[2000000];
  bool *p = pT;
  for (int k = 0; k < 2000000; k++) {
    *p = (k % 2 == 0);
    p++;
  }
}
