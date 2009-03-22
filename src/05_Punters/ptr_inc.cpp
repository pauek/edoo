
#include <iostream>
using namespace std;

int main() {
  int x = 0;
  int *px = &x;
  cout << px << endl;
  px += 1;
  cout << px << endl;
}
