#include "Alumne.h"


Alumne::Alumne()
{
}

Alumne::Alumne(string &nom, string &dni, int nota)
{
  this->nom = nom;
  this->dni = dni;
  this->nota = nota;
}

  
void Alumne::setNom(string &nom)
{
  this->nom = nom;
}

void Alumne::setDNI(string &dni)
{
  this->dni = dni;
}

void Alumne::setNota(int nota)
{
  this->nota = nota;
}

  
string Alumne::getNom()
{
  return nom;
}

string Alumne::getDNI()
{
  return dni;
}

int Alumne::getNota()
{
  return nota;
}


