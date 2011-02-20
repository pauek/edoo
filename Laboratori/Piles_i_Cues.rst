
=================
STL: Piles i cues
=================

.. tema:: lab.pq

Objectius
=========

- Utilitzar estructures de pila.

- Aprendre a fer servir estructures de tipus cua.

- Recordar les operacions característiques.


Piles
=====

La STL implementa la classe ``stack``, que serveix per emmagatzemar
una pila d'elements. Si volguéssim declarar una pila de
cadenes de caràcters, per exemple, faríem el següent [#f1]_ ::

  stack<string> pila;

Les operacions principals de les piles són:

- Afegir un element a la pila (``push``).

- Treure un element de la pila (``pop``).

- Consultar l'últim element afegit a la pila (``top``).

.. exercici::

   Fes un programa que llegeixi una sequència de missatges com els
   següents en una pila::

      12:36 MeteorWayne Zv: NO.
      12:38 Funkopolis Made-up results will be available immediately
      12:38 ugordan lol
      12:39 mammoth We heard about pH and marsparagus almost immediately
      12:39 djellison Any more questions?
      12:40 mammoth QUESTION: has the MECA team talked about their next sample?
      12:41 Funkopolis Like the back seat of a volkswagen?
      12:41 Zvezdichko QUESTION: Do they plan to look for Cl- again?

   Aquesta seqüència prové d'un *chat* i com es pot veure té una hora,
   un usuari i un text (el text que hi ha després de l'usuari arriba
   fins al final de línia, pots fer servir ``getline`` per obtenir-la).

   Un cop llegida, el programa ha de mostrar els últims 10 missatges:
   primer l'últim, després el penúltim, fins al desè.

Cues
====

A part del ``stack``, la STL també implementa la classe ``queue``, que
serveix per emmagatzemar una cua d'elements. Si tenim una classe
``Cotxep`` com al següent::

  class Cotxe {
    string matricula, tipus;

  public:
    void   setMatricula(const string& matricula);
    string getMatricula() const;
    void   setTipus(const string& tipus);
    string getTipus() const;
  };

podem declarar una cua d'objectes de la classe ``Cotxe`` [#f2]_ ::

  queue<Cotxe> cua_cotxes;

Cal recordar que les operacions principals de les cues són:

- Afegir un element al final de la cua (``push``).

- Treure un element del principi de la cua (``pop``).

- Consultar l'element que es troba al principi de la cua (``front``).

.. exercici::

   Fes un programa que simuli el pas de cotxes per un pas de
   peatge. El programa ha de permetre tres operacions: afegir un cotxe
   al punt de peatge, fer passar un cotxe pel punt de peatge i sortir
   del programa. Utilitzeu la classe ``Cotxe`` (caldrà que implementeu els
   mètodes) i una cua de STL per simular el peatge.


.. [#f1] Recorda que per a fer servir la classe ``stack`` has de fer
   ``#include <stack>`` i posar ``using namespace std`` si no hi és.

.. [#f2] Un altre cop, cal fer ``#include <queue>`` i posar ``using
   namespace std`` si no hi és.

