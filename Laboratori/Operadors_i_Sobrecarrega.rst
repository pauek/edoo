
.. tema:: lab.ops

========================
Operadors i sobrecarrega
========================

Objectius
=========

- Declaració, implementació i ús d'operadors aritmètics. 

- Declaració, implementació i ús d'operadors de lectura i escriptura.


Classe Racional
===============

En aquesta sessió de laboratori practicarem la declaració i
implementació d'operadors. Per a fer-ho crearem una nova classe,
``Racional``, afegint-hi funcionalitat de forma gradual. Un nombre
racional és aquell que pot expressar-se com la divisió de dos nombres
enters. Per exemple, 1/2 o 3/4 són nombres racionals.

Com ja hem vist, es habitual crear dos fitxers per a cada classe. En
un es posa la declaració de la classe i en l'altre la implementació
dels mètodes d'aquesta. Donat que també voldrem tenir un programa
principal que faci servir la classe ``Racional``, necessitarem tres
fitxers: ``main.cpp``, ``Racional.h`` i ``Racional.cpp``.

Penseu que a ``Racional.cpp`` s'implementen els mètodes de la classe
``Racional`` i com a tal necessita coneixer la declaració de
``Racional``. Per a que la tingui disponible caldrà que
``Racional.cpp`` inclogui el fitxer ``Racional.h`` amb la directiva
``include`` de la manera següent::

  #include "Racional.h"
  
El mateix passa amb ``main.cpp`` que haurà de fer ús de la classe
``Racional`` i, per tant, també necessita incloure ``Racional.h``.

De moment, com a declaració del TAD Racional farem servir el codi
següent::

  struct Racional {
    int num, den;  // numerador y denominador
  };
  
Si us hi fixeu, s'ha estat parlant tota la estona de la classe
``Racional``, però s'ha definit com a ``struct``. Això ho canviarem més
endavant.

Com que el TAD ``Racional`` no té mètodes, no cal implementar res a
``Racional.cpp`` (encara que no estaria malament afegir ja el
``include`` de ``Racional.h``). De tota manera, si que necessitem una
funció ``main`` o el programa no compilarà. El codi de la funció
``main`` serà, de moment, el següent::

  #include <iostream>
  #include "Racional.h"
  
  using namespace std;
  
  int main() 
  {
    Racional r1, r2;
    r1.num = 1;
    r1.den = 4;

    cout << "Introdueix un racional" << endl;
    cout << "Primer el numerador: " << endl;
    cin >> r2.num;
    cout << "Ara el denominador: " << endl;
    cin >> r2.den;
    
    cout << "Racional 1: " << r1.num << "/" << r1.den << endl;
    cout << "Racional 2: " << r2.num << "/" << r2.den << endl;
  }
  
El programa anterior inicialitza el racional ``r1`` a 1/4 i després
demana a l'usuari el numerador i el denominador de un segon racional
``r2``. Finalment, el programa escriu per la sortida estàndar els dos
racionals ``r1`` i ``r2``.

.. exercici::

   Crea un projecte i afegeix tot el codi que hem vist
   anteriorment. Compila i prova el programa.
   

Constructors
============

En el programa anterior s'inicilitzava el racional ``r1`` accedint
directament als atributs ``num`` i ``den``. Hi ha una
manera millor de fer-ho i es fent servir un constructor. El que
voldrem és poder eliminar les dues línies::

  r1.num = 1;
  r1.den = 4;

i en el seu lloc subsituir la línia::

  Racional r1, r2;
  
per la línia::

  Racional r1(1, 4), r2;
  
que crida a un constructor que ja s'encarrega d'inicialitzar els
atributs. Caldrà, però, declarar aquest constructor a ``Racional.h`` i
implementar-lo a ``Racional.cpp``.

.. exercici::

   Afegeix la declaració del constructor a ``Racional.h``. El
   constructor haurà de tenir dos paràmetres que li serviran per
   inicialitzar els atributs ``num`` i ``den`` de
   l'objecte que està construint.
   
.. exercici::

   Afegeix la implementació del constructor a ``Racional.cpp``. 
   

Operador de lectura
===================

Ara mateix la lectura del racional ``r2`` es fa a la funció ``main``,
però hem vist a teoria que podem declarar operadors de lectura i
escriptura per a qualsevol TAD que definim. El que farem es agafar el
codi que fa la lectura d'un ``Racional``::

    cout << "Introdueix un racional" << endl;
    cout << "Primer el numerador: " << endl;
    cin >> r2.num;
    cout << "Ara el denominador: " << endl;
    cin >> r2.den;
  
i ficar-lo al TAD ``Racional`` com a un operador de lectura
(``operator>>``). D'aquesta manera es podrà substituir tot el codi
anterior per una simple crida a l'operador de lectura de
``Racional``::

  cin >> r1;

Recordeu que el operador de lectura té la capçalera següent::

  istream &operator>>(istream &is, NomDeLaClasse &obj);

i que com mai és un mètode de la classe en qüestió (és una funció
operador a part) es declara fora de la declaració del TAD que
llegeix. Tingueu en compte que ``NomDeLaClasse`` es correspon amb el
nom de la classe que volem que es llegeixi (en el cas d'aquesta sessió
és ``Racional``).

.. exercici::

   Afegeix l'operador de lectura de ``Racional`` i implementa'l. Pensa
   que ha de fer el mateix que el codi al que substituirà.
   
.. exercici::

   Fes servir l'operador de lectura que has definit per a llegir el
   racional ``r1``.
   
   
Operador d'escriptura
=====================

Anàlogament, podem definir l'operador d'escriptura per al TAD ``Racional``::

  ostream &operator<<(ostream &os, const NomDeLaClasse &obj);

per a substituir les escriptures dels dos racionals ``r1`` i ``r2``::

  cout << "Racional 1: " << r1.num << "/" << r1.den << endl;
  cout << "Racional 2: " << r2.num << "/" << r2.den << endl;
  
pel codi molt més curt::

  cout << r1;
  cout << r2;

.. exercici::

   Afegeix l'operador d'escriptura de ``Racional`` i
   implementa'l. Pensa que ha de fer el mateix que el codi al que
   substituirà.
   
.. exercici::

   Fes servir l'operador d'escriptura que has definit per a escriure
   els racionals ``r1`` i ``r2``.
   

Pas a classe
============

Un cop fets tots el canvis anteriors, podreu veure que ja no accediu
als atributs ``num`` i ``den`` des de la funció
``main``. Totes les operacions es realitzen mitjançant mètodes, ja
sigui el constructor que heu afegit o amb els operadors de lectura i
escriptura. Això significa que ara podem tancar el TAD ``Racional``
fent privats alguns dels seus components i deixant com a públics
aquells que fan falta des de fora.

.. exercici::

   Canvia ``Racional`` per a que sigui una classe i no una tupla.
   Fes servir les paraules clau ``public:`` i/o ``private:`` per a fer
   els canvis necessaris d'accessibilitat dels atributs i mètodes de
   la classe ``Racional``.
   
   
Operadors aritmètics
====================

Operador de producte
--------------------

Ara podem inicialitzar, llegir i escriure racionals, però no podem
operar amb ells.

Per a començar introduirem el producte de racionals. A teoria vam
veure que els operadors aritmetics es podien fer de dues maneres: o bé
com a funcions (operador extern), o bé com a mètodes (operador
intern). Aquí farem servir la segona manera.

La capçalera del mètode de producte de racionals seria::

  Racional operator*(const Racional& r) const;
  
Com que és un mètode i no una funció, caldrà afegir aquesta declaració
dintre de la declaració de la classe ``Racional`` a
``Racional.h``. També la haurem de implementar a ``Racional.cpp`` com
un mètode més.

.. exercici::

   Afegeix l'operador de producte a la classe ``Racional``.
   
Un cop implementat, s'ha de provar que realment funciona. Per a fer-ho
podeu afegir després del codi que dóna valor als dos racionals ``r1``
i ``r2`` el codi següent::

  cout << (r1 * r2);

Això calcula el producte de ``r1`` i ``r2`` i escriu el resultat.

.. exercici::

   Afegiu la línia anterior per a fer servir el producte de racionals
   i comproveu que funciona correctament.
   
   
Operadors de suma i resta
-------------------------

De manera similar es poden declarar, implementar i fer servir els
operadors de suma i resta. Cal tenir en compte, però, com funciona la
suma de racionals (la resta és anàloga). Farem servir el mètode més
simple per a no complicar el codi.

Si teniu dos nombres racionals ``a/b`` i ``c/d``, per a poder fer la
seva suma, primer cal que tinguin el mateix denominador. Normalment es
treuria el mínim comú múltiple dels dos denominadors (``b`` i
``d``). Es pot fer més fàcilment multiplicant tots dos racionals per
un racional equivalent a 1 i que resulti en dos nombres racionals amb
el mateix denominador. És a dir, fent ``(a/b)·(d/d)`` i
``(c/d)·(b/b)`` tenim ``ad/bd`` i ``cb/bd`` que són equivalents als
racionals que voliem sumar (``a/b`` i ``c/d``). Ara ja podem fer la
suma i el resultat serà ``(ad+cb)/bd``.

.. exercici::

   Aplicant el que s'ha exposat afegeix els operadors de suma i resta.
   
.. exercici::

   De la mateixa manera que has fet a l'apartat anterior, fes servir
   els operadors nous i comprova el resultat.
   
