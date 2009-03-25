
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "Has de posar un nom en el primer argument!" << endl;
  }
  else {
    cout << "Hola, " << argv[1] << ", què tal estàs?" << endl;
  }
}

