
==============
TADs i Classes
==============

Objectius
=========

- Canvi de TAD a classe.

- Ús del control d'accés.

- Implementació de constructors.


De struct a class
=================

Un cop fets els canvis per a fer servir el TAD ``Pixel``, ja només caldrà accedir a l'atribut ``valor`` desde les tres funcions membre que hem definit (``llegeix``, ``inverteix`` i ``escriu``). Ara podem transformar el TAD ``Pixel`` en una classe. Cal recordar que el canvi ha de mantenir les funcions membre com a publiques per a que siguin accessibles des de la funció main.

.. exercici::

   Converteix el TAD ``Pixel`` en una classe. Per a fer-ho caldrà canviar de ``struct`` a ``class`` a la seva declaració. A més caldrà utilitzar la instrucció ``public`` amb les funcions membre.
   

Constructors
============

Enfosquir una imatge
--------------------

Ara que tenim el TAD ``Pixel`` podem afegir noves funcions membre que manipulin pixels individuals. Per exemple, si afegim la següent funció membre, que divideix la intensitat del color del pixel a la meitat::

  void Pixel::enfosquir()
  {
    valor = valor / 2.0;
  }
  
podrem enfosquir la imatge canviant la crida a ``inverteix`` per una crida a ``enfosquir``.

.. exercici::

   Canvia la crida a la funció membre ``inverteix`` per una crida a ``enfosquir``. Compila i executa el programa per a veure el resultat d'aplicar el nou algorisme a una imatge.
   
Constructor de còpia
--------------------

Tenim totes les eines per a fer que el programa generi la imatge invertida (el negatiu) i una versió enfosquida a la vegada, però com només tenim un objecte del TAD ``Imatge`` si apliquem una operació perdem la imatge original. Podríem tenir dos objectes del TAD ``Imatge`` i fer-los servir per a llegir la mateixa imatge dos cops, però això no seria eficient. 

La manera de resoldre-ho eficientment consisteix en llegir la imatge un cop i fer-ne una còpia. Per a poder fer-ho caldrà afegir el constructor de còpia::

  struct Imatge
  {
    // Estructura Imatge
    ...
    Imatge(const Imatge &img);
    ...
  };
  
  Imatge::Imatge(const Imatge &img)
  {
    // Constructor de còpia
    tamx = img.tamx;
    ...
  }
  

.. exercici::

   Afegeix el constructor de còpia a l'estructura ``Imatge`` i implementa'l. Cal que el constructor faci una còpia de tots els atributs de l'estructura ``Imatge``.
   
.. exercici::

   Modifica el programa principal ``main`` per a poder tenir dues còpies de la imatge (fes servir el constructor de còpia). Aplica llavors la inversió a una imatge i l'enfosquiment a l'altre. Escriu el resultat en dos fitxers.
   
Com que hem definit un constructor on abans no n'hi havia cap, hem perdut el constructor per defecte. Per tant, el compilador donarà error quan creem un objecte de tipus ``Imatge`` sense paràmetres, com per exemple::

  Imatge I;
  
Per a que no doni error cal definir el constructor per defecte::

  struct Imatge
  {
    // Estructura Imatge
    ...
    Imatge();
    Imatge(const Imatge &img);
    ...
  };

.. exercici::

   Afegeix el constructor per defecte a l'estructura ``Imatge`` i també la seva implementació. No cal que el constructor per defecte faci res (no té codi).


