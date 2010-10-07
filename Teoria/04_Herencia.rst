
.. tema:: he


=============
Herència
=============

.. rubric:: Objectius

- Identificar la declaració d'una classe derivada.

- Determinar si és possible l'accés a membres d'una classe i de les
  seves bases.

- Implementar noves classes que hereden d'una classe base donada.

- Utilitzar llibreries en C++ heredant de les classes existents.


Comencem amb un exemple
=======================

Imaginem que volem fer un programa que treballi amb les dades dels
soldats d'un exèrcit. Podem començar amb la classe ``Soldat``::

  class Soldat {
    string DNI, nom, cognoms;
    Data   data_incorporacio;
    int    seccio;
  public:
    // ...
  }

Alhora, volem que el programa pugui tractar amb els tinents, que són
responsables dels soldats de la seva secció (i en el programa volem
saber de quins). Si féssim la classe ``Tinent`` desde zero, seria així::

  class Tinent {
    string   DNI, nom, cognoms;
    Data     data_incorporacio;
    int      seccio;
    string   DNI_subordinats[50];
  public:
    // ...
  }

Els tinents tenen una llista dels soldats al seu càrrec
(``DNI_subordinats``), però com que també són soldats, tenen les dades
típiques dels soldats. El problema amb aquesta implementació, de fet,
és la *repetició*. Per fer la classe ``Tinent`` seria interessant poder
aprofitar la classe ``Soldat`` i estalviar-nos haver de tornar a
escriure els 4 camps de les dades del soldat.

Per fer això, fem que ``Soldat`` sigui la classe base, i
``Tinent`` la classe derivada i fem així::

  class Tinent : public Soldat {
    string dni_subordinats[50];
  public:
    // ...
  }

Pel sol fet d'afegir "``: public Soldat``" després de "``class
Tinent``", estem dient que *un ``Tinent`` és un ``Soldat``* i
per tant tots els camps de ``Soldat`` han d'estar a ``Tinent``.

.. exercici::

   Donada la classe ``Animal`` amb els atributs següents::

     class Animal {
       int color;
       float pes, velocitat_maxima;
       bool pelut;
     public:
       //...
     };

   Declara una classe ``Girafa`` que derivi d'``Animal``, i que tingui
   un atribut ``llargada_coll`` de tipus real. No cal que declaris cap
   mètode, és un exemple totalment acadèmic.


Terminologia
============

Classe base
  La classe que representa un concepte general, que emmagatzema les
  parts comunes d'un conjunt d'objectes.

Classe derivada
  Una classe que representa una ampliació de la classe
  base, un cas particular del concepte. La classe derivada hereda tots
  els membres de la classe base.

Heredar
  Obtenir automàticament els membres d'una classe base en una
  derivada. A la declaració d'una classe derivada només s'han
  d'especificar els membres que *afegim*, que han de representar les
  diferències entre el concepte general i el particular.


Classes derivades: els detalls
==============================

Les classes derivades acumulen els atributs i mètodes de totes les bases
------------------------------------------------------------------------

Si tenim un 3 classes com [1]_::

  struct A {
    int x;
  };

  struct B : public A {
    char y;
  };
  
  struct C : public B {
    float z;  
  };

Un objecte de la classe ``A`` té un atribut (``x``), un objecte de
classe ``B`` té 2 atributs (``x`` i ``y``) i un objecte de classe
``C`` té 3 atributs (``x``, ``y`` i ``z``). Si tenim les següent
declaracions::

   A a;
   B b;
   C c;

el dibuix següent mostra l'estructura interna de cada objecte.

.. image:: img/herencia_ABC.*
   :align: center

Com és natural, intentar accedir a atributs que no són de la classe és
un error::

   a.y = 'Q';  // error, la classe A no té atribut 'y'
   c.x = 1024; // correcte
   b.z = 2.55; // error, la classe B no té atribut 'z'

.. exercici::

   Donades les següents declaracions::

     struct X {
       char a;
       int b;
     };
     
     struct Y : public X {
       string s;  
     };
   
     struct W : public X {
       float x;
     };

     struct V : public W {
       bool p, q;
     };
 
     struct Z : public Y {
       double c, d;
     };

   i els objectes següents::
  
     X x;
     Y y;
     W w;
     V v;
     Z z;

   digues quins dels següents accessos a atributs són erronis. Indica
   també aquells en que l'error està en el tipus::

     w.x = 'e';
     y.s = "qwerty";
     v.q = 3;
     w.p = true;
     v.b = 81;
     z.d = 5.01;
     v.x = 55.34;
     y.x = 0.7;
     x.a = 'A';
     z.a = '$';
     x.b = 1;
     y.b = 3;




Classes: crida al constructor base
----------------------------------





Accés a membres base a la classe derivada: ``protected``
--------------------------------------------------------



Cassos d'utilització de l'herència
==================================

Per expressar petites diferències en un mateix programa
-------------------------------------------------------


Per fer servir llibreries
-------------------------

.. [1] Recordem que un ``struct`` és com una classe amb tots els
       membres ``public``.
