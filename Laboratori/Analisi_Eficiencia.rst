
====================
Anàlisi d'eficiència
====================

Objectius
=========

- Comparar execucions d'algorismes per diferentes entrades.

- Analitzar l'eficiència d'algorismes.


Anàlisi empíric d'algorismes
============================

Mesura del temps d'execució d'un programa
-----------------------------------------

Suposem que volem mesurar el temps que triga en executar-se el següent
programa

.. literalinclude:: src/eficiencia1.cc
   :end-before: Local variables

Per mesurar-ne el temps d’execució, podem fer servir la funció
``clock`` de la llibreria ``ctime``, que ens retorna el temps del
rellotge intern de l'ordinador. Fent la resta entre dos valors
obtinguts amb aquesta funció abans i després del tros que ens
interessa mesurar, obtenim el número de cicles de rellotge de
diferència, i dividint per ``CLOCKS_PER_SEC`` sabrem els segons.

El següent programa introdueix la class ``Cronometre`` que implementa
això, precisament.

.. literalinclude:: src/eficiencia2.cc
   :end-before: Local variables

.. exercici::

   Compila el programa i canvia el valor 20000 per 10000 i 100000 per
   veure com afecta al temps d'execució.

Mesura de diferents algorismes d'ordenació
------------------------------------------

Es tracta d’estudiar empiricament els algorismes d’ordenació per
selecció i per inserció. Per això mesurarem els temps d’execució dels
programes amb diferents dades d’entrada, i comparem aquests resultats
empírics que ens permetrà treure conclusions sobre l’eficiència dels
diferents algorismes.

Mètode de Selecció
""""""""""""""""""

El següent algorisme ordena una taula mitjançant el
mètode de selecció:

.. literalinclude:: src/eficiencia_seleccio.cc
   :end-before: Local variables

.. exercici::
   
   Utilitza la classe ``Cronometre`` per mesurar el temps d'execució
   del programa.

.. exercici::

   Dona diferents valors a la constant N (mira la taula al final de la
   pràctica) i pren nota dels temps d’execució per cada
   valor de N.

.. exercici::

   Fes una acció ``ompleTaulaDescendent`` que ompli la taula
   amb valors decreixents. Repeteix les mesures del temps
   d’execució del programa amb aquesta nova versió.

.. exercici::

   Fes una acció ``ompleTaulaAleatori`` que ompli la taula amb valors
   aleatoris. Per obtenir un valor aleatori es pot cridar la funció
   ``rand`` que té la declaració (cal afegir ``cstdlib`` als
   ``#include``\s)::
    
      int rand();

   Repeteix les mesures del temps d'execució un cop més.

Mètode d'inserció
"""""""""""""""""

.. exercici::

   Canvia l'algorisme d'ordenació del programa pel següent

   .. literalinclude:: src/ordena_insercio.cc

.. exercici::

   Repeteix les mesures del temps d’execució amb aquest nou algorisme
   d'ordenació, per cadascuna de les tres versions d’omplir la taula
   utilitzades anteriorment.
   
.. exercici::

   Compara la complexitat dels mètodes estudiats fent servir la taula
   següent (entra la taula en un full de càlcul)
   
   +------------+-----------------------+-------------------------+-----------------------+
   | Valor de N | Omplir taula creixent | Omplir taula decreixent | Omplir taula aleatori |
   +------------+-----------------------+-------------------------+-----------------------+
   |    10000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |    20000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |    50000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |    80000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |   100000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |   150000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   
   Dibuixa amb el full de càlcul una gràfica amb cada temps d’execució
   obtingut. A l’eix X poses el valor de la N, i a l’eix Y el temps
   d’execució.

.. exercici::

   Per què la gràfica que s’obté és una paràbola? 
   Justifica la resposta matemàticament.


