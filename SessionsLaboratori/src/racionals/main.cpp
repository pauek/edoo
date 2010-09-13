  #include <iostream>
  #include "Racional.h"
  
  using namespace std;
  
  int main()
  {
    Racional r1, r2;
    
    r1.numerador = 1;
    r1.denominador = 4;
    cout << "Introdueix un racional" << endl;
    cout << "Primer el numerador: " << endl;
    cin >> r2.numerador;
    cout << "Ara el denominador: " << endl;
    cin >> r2.denominador;
    
    cout << "Racional 1: " << r1.numerador << "/" << r1.denominador << endl;
    cout << "Racional 2: " << r2.numerador << "/" << r2.denominador << endl;
    
    return 0;
  }

