#ifndef _ALUMNE_INCLUDE
#define _ALUMNE_INCLUDE

#include <iostream>

using namespace std;

class Alumne
{

  string nom, dni;
  int nota;
  
public:
  Alumne();
  Alumne(string &nom, string &dni, int nota);
  
  void setNom(string &nom);
  void setDNI(string &dni);
  void setNota(int nota);
  
  string getNom();
  string getDNI();
  int getNota();
  
};

#endif

