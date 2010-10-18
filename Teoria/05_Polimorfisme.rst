
.. tema:: poli

==============
Polimorfisme
==============

.. rubric:: Objectius

- Identificar quins mètodes es cridaran en una crida a mètode ``virtual``.

- Implementar llistes heterogènies.

El punter ``this``
==================

.. Un buen ejemplo donde necesitas esto? Que no sea Qt?

Punters a objectes de classes derivades
=======================================

.. Puedes tener un puntero a una classe base y poner un objeto de una
.. clase derivada

.. problema que aparece si tengo un puntero a una clase base y invoco
.. una función que está redefinida (se invoca la de la clase base).
.. Bruce Eckel -> instrumentos.


Detecció en temps d'execució: el modificador ``virtual``
--------------------------------------------------------

.. simplemente añadimos el modificador `virtual` y se arregla todo.


Terminologia
------------

polimorfisme 
  De *poli* (múltiples) i *morf* (forma), o sigui "vàries formes". El
  terme es refereix a que tenint un punter a una classe base, podem
  tenir un objecte de qualsevol de les classes derivades i per tant
  aquest punter pot referirse a una d'entre vàries formes.

Llistes heterogènies
====================

.. Aplicación de la técnica de funciones virtuales a programas donde
.. tienes un bucle que invoca diferentes métodos en función del objeto.

.. Otro ejemplo donde aparece el problema de qué poner en la
.. implementación de la case base, porque no tiene sentido.

Una classe abstracta té algun mètode ``virtual`` sense implementació
--------------------------------------------------------------------

.. basta con poner "= 0" en la declaración para decir que no tiene implementación.

.. Refinamos la técnica para incluir el caso que la clase base no
.. tiene implementación lógica, sólo las clases derivadas tienen sentido.
