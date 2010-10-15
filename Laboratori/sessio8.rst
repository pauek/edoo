
=================
STL: Piles i cues
=================

Objectius
=========

- Utilitzar estructures de pila.

- Aprendre a fer servir estructures de tipus cua.

- Recordar les operacions característiques.


Piles
=====

En STL una pila es declara fent servir la paraula clau **stack**. Si, per exemple, volguèssim declarar un stack de cadenes de caràcters faríem el següent::

  stack<string> pila;

Cal recordar, però, que per a fer servir les piles de STL i els strings hem de fer les inclusions pertinents::

  #include <iostream>
  #include <stack>
  
  using namespace std;

Les operacions principals de les piles són:

- Afegir un element a la pila (push).

- Treure un element de la pila (pop).

- Consultar l'últim element afegit a la pila (top).

.. exercici::

   Feu un programa que llegeixi paraules de teclat fins que llegeixi la paraula punt (".") i que, després, escrigui les paraules en ordre invers. És a dir, per una seqüència d'entrada com: {"What", "is", "the", "matrix", "."}, donaria com a resultat: {"matrix", "the", "is", "What"}. Feu servir una pila de strings.


Cues
====

Per una altra banda, les cues es declaren utilitzant la paraula clau **queue**. Si tenim una classe Cotxe::

  class Cotxe
  {
    string matricula, tipus;

  public:
    void setMatricula(string &novaMatricula);
    string getMatricula();
    void setTipus(string &nouTipus);
    string getTipus();
  };

podem declarar una cua de objectes de la classe Cotxe::

  queue<Cotxe> cua;

De la mateixa manera que amb les piles cal fer certes inclusions::

  #include <queue>
  
  using namespace std;

Cal recordar que les operacions principals de les cues són:

- Afegir un element al final de la cua (push).

- Treure un element del principi de la cua (pop).

- Consultar l'element que es troba al principi de la cua (front).

.. exercici::

   Feu un programa que simuli el pas de cotxes per un pas de peatge. El programa ha de permetre tres operacions: afegir un cotxe al punt de peatge, fer passar un cotxe pel punt de peatge i sortir del programa. Utilitzeu la classe Cotxe (caldrà que implementeu els mètodes) i una cua de STL per simular el peatge.


