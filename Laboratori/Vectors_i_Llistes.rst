
======================
STL: Vectors i llistes
======================

.. tema:: lab.vl

Objectius
=========

- Aprendre a fer servir vector.

- Aprendre a fer servir list.

- Utilitzar iteradors per a recorrer contenidors STL.


Vectors
=======

Hem vist a classe de teoria la classe contenidora ``vector`` de la
llibreria STL. Aquesta classe ens permet definir un array d'elements
que pot canviar de tamany dinàmicament.

L'objectiu del primer exercici serà fer un programa que demani dades
de discos musicals a l'usuari, les emmagatzemi i sigui capaç
d'escriure-les per pantalla. Per a poder fer-ho primer necessitareu
una classe Disc::

  class Disc
  {
    // Aquí haureu d'afegir els atributs i mètodes
    // que cregueu que facin falta.
  }

.. exercici::

   Implementeu la classe ``Disc`` per a que emmagatzemi les dades dels
   discos que creieu adients. Com a mínim hauria de tenir nom, grup i
   any.
   
.. exercici::

   Fent servir un vector de discos, feu un programa que doni a
   l'usuari les següents opcions: entrar un nou disc, llistar tots els
   discos i sortir. El programa ha de demanar a l'usuari quina de les
   tres opcions vol, i mentre l'usuari no seleccioni sortir haurà de
   complir la funció corresponent. L'opció de llistar tots els discos
   requereix recorrer el vector. Això s'ha de fer utilitzant
   iteradors.


List
====

Però posem que volguessim mantenir la llista de discos ordenats per
any. Una manera seria cada vegada que afegim un nou element al
contenidor, posar-lo de tal manera que els elements continuin estant
ordenats. Per exemple, si ja tenim discos dels anys: {1996, 1997,
2009, 2010}, i volem afegir un de nou de l'any 2005, el posaríem entre
el disc de l'any 1997 i el del 2009, obtenint: {1996, 1997, 2005,
2009, 2010}.

Si recordeu fer aquesta operació (inserir al mig) amb la classe
*vector* no és eficient. És millor utilitzar *list*.

.. exercici::

   Modifiqueu l'exercici anterior per a que es faci servir *list* en
   comptes de *vector*. De moment, es pot continuar inserint els nous
   discos al final.
   
Per a poder inserir ordenadament, primer cal buscar a on volem afegir
el nou disc. Per a fer això ens caldrà un iterador, que haurem
d'avançar fins que l'element actual sigui d'un any posterior al que
volem inserir, o fins que arribem al final. Recordeu que l'operació
*insert* de llistes afegeix el nou element abans de l'element apuntat
per l'iterador que se li passa.

.. exercici::

   Mitjançant un iterador, i abans d'inserir el nou disc, cerqueu la
   posició a la que s'haurà de posar.
   
.. exercici::

   Fent servir el mètode *insert* (mireu els apunts) de la classe
   *list*, inserteu l'element. Si tot va com cal, haurieu de poder
   afegir diversos discos i a l'escriure'ls haurien de sortir
   ordenats.
   

