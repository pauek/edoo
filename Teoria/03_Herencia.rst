
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
-----------------------

Imaginem que volem fer un programa que treballi amb les dades els
empleats d'una empresa. Podem començar amb la classe ``Empleat``::

  class Empleat {
    string DNI;
    string nom, cognoms;
    Data   data_contractacio;
    int    departament;
  public:
    // ...
  }

Alhora, volem que el programa pugui tractar amb els "jefes" [1]_, que
són responsables d'altres empleats (i en el programa volem saber de
quins). Si féssim la classe ``Jefe`` de nou, seria així::

  const int MAX_PERSONES = 25;

  class Jefe {
    string   DNI;
    string   nom, cognoms;
    Data     data_contractacio;
    int      departament;
    string   dni_subordinats[MAX_PERSONES];
  public:
    // ...
  }

Els jefes tenen una llista de les persones al seu càrrec (els
DNIs), però com que són també empleats, tenen les dades típiques dels
empleats. El problema amb aquesta implementació, de fet, és la
*repetició*. Per fer la classe ``Jefe`` seria interessant poder
aprofitar la classe ``Empleat`` i estalviar-nos haver de tornar a
escriure els 4 camps de les dades d'empleat (encara que només sigui
perquè si les hem de canviar, ho haurem de fer 2 cops). 

Per fer això, fem que ``Empleat`` sigui la classe base, i
``Jefe`` la classe derivada i fem així::

  const int MAX_PERSONES = 25;

  class Jefe : public Empleat {
    string dni_subordinats[MAX_PERSONES];
  public:
    // ...
  }

Pel sol fet d'afegir "``: public Empleat``" després de "``class
Jefe``", estem dient que *un ``Jefe`` és un ``Empleat``* i
per tant tots els camps d'``Empleat`` han d'estar a ``Jefe``.

Podem fer una representació gràfica així...

.. Imagen tipo UML de las dos clases alineadas por arriba.

Clarament, la part superior de ``Empleat`` i ``Jefe`` es la mateixa.

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


Utilització de classes derivades: els detalls
=============================================

Accés a membres desde fora
--------------------------


Accés a membres base a la classe derivada
-----------------------------------------


Crida al constructor base
-------------------------


Cassos d'utilització de l'herència
==================================

Per expressar petites diferències en un mateix programa
-------------------------------------------------------


Per fer servir llibreries
-------------------------




.. [1] Amb perdó de la "castellanada".
