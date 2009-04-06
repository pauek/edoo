
#include <iostream>
#include <fstream>
using namespace std;

#include "imatge.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    cout << "Utilització: img_invert <fitxer_entrada> <fitxer_sortida>" << endl;
    return 1;
  }
  
  Imatge I;
  {
    ifstream fin(argv[1]);
    fin >> I;
  }

  I.inverteix();

  {
    ofstream fout(argv[2]);
    fout << I;
  }
}
