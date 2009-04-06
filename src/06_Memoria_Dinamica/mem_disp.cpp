
#include <iostream>
using namespace std;

const int MB = 1024 * 1024; // 1 MegaByte

int main() {
  char *p;
  int tam = 1;
  p = new char[MB];
  while (p) {
    tam++;
    p = new char[MB];
  }
  cout << "Tamany total " << tam << "MBs" << endl;

}
