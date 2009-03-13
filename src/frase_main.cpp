
#include <iostream>
using namespace std;

#include "frase.h"

int main() {
  Frase f;
  f.afegeix_paraula("Ser");
  f.afegeix_paraula("o");
  f.afegeix_paraula("no");
  f.afegeix_paraula("ser");
  f.mostra(cout); cout << endl;
  cout << "La frase té " << f.num_paraules() << " paraules" <<  endl;
  
  string nom;
  cout << "El teu nom? ";
  cin >> nom;
  
  f.esborra();
  f.afegeix_paraula("Hola,");
  f.afegeix_paraula(nom);
  f.mostra(cout); 
  cout << endl;
}
