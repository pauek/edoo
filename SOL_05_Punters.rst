
=======
Punters
=======

.. exercici::
   
   La primera adreça d'un ordinador amb 4Gb de memòria és 0 i la
   última és :math:`4 \times 1024^3`, és a dir 4294967296.

   Es necessiten 32 bits per emmagatzemar una adreça d'aquest tamany,
   10 bits per a cada 1024 (n'hi ha 3) i 2 bits més (pel 4). En un
   ordinador amb 32 bits, la màxima memòria adreçable és 4Gb, doncs.

.. exercici::

   Les adreces que surten si executem el programa depenen tant de
   l'ordinador que es fa servir. Si l'ordinador és de 64 bits (el meu
   cas), surten 3 adreces de 64 bits::

      0x7fff6755d918 0x7fff6755d91f 0x7fff6755d914

   El format en què es representen aquestes adreces és `hexadecimal
   <http://en.wikipedia.org/wiki/Hexadecimal>`_. Cada vegada que
   s'executa el programa poden sortir adreces diferents. No es pot
   saber a on exactament el compilador col·locarà les dades.

.. exercici::
   ::

      Complex *pc1, *pc2;

.. exercici::

   La sortida del programa serà "3". La variable ``a`` ocupa certa
   posició de memòria que estem incrementant indirectament a través
   de dos punters que apunten a la posició de ``a``.

.. exercici::

   La sortida del programa serà::

     0.5 1.5

   El resultat s'explica perquè els punters ``pf1`` i ``pf2``
   contenen, inicialment, les adreces de ``x`` i ``y`` respectivament,
   i després, utilitzant ``pf3`` com a variable temporal, aquestes
   adreces s'intercanvien, de manera que ``pf1`` apuntarà a ``y`` i
   ``pf2`` apuntarà a ``x``. Llavors se suma 0.5 a ``*pf1`` (que és
   ``y``), i ``*pf2`` (que és ``x``) es divideix per 2.

.. exercici::

   La sortida serà "11 7". L'acció ``f`` en realitat intercanvia els
   valors continguts a les adreces ``a`` i ``b``. El programa
   principal simplement crida la funció amb valors llegits del teclat.


.. exercici::

   Tal com deiem abans, aquest programa pot donar diferents resultats
   en funció de la màquina en què estiguem. En el meu ordinador el
   resultat és::

     0x7fff80ae1e9c
     0x7fff80ae1ea0

   Que indica que un enter ocupa 4 bytes (de ``9c`` a ``a0`` hi ha una
   distància de 4 en `hexadecimal <http://en.wikipedia.org/wiki/Hexadecimal>`_).

.. exercici::

   Si un ``float`` ocupa 4 bytes, una taula de 10 floats n'ocupa 40,
   tots seguits en memòria.


.. exercici::
   
   La sortida serà "c". El punter ``p`` s'inicialitza a la 4 casella
   de la taula (``'d'``), però al mostrar-lo per pantall se li resta 1
   i es mira el valor d'aquella posició.

.. exercici::

   La sortida serà::

      5 9 5

   La raó és que ``p`` primer es posa a la primera casella, però de
   seguida se li suma 2 (i es coloca a la tercera). Llavors es
   divideix per 3 el valor de la casella (el 15), es decrementa ``p``
   (estem a la segona casella) i se li resta 1 al valor al que apunta
   ``p`` (el 10).

.. exercici::

   La sortida del programa serà::

     Gran Frase

   La raó és que ``pf`` s'inicialitza al principi de la frase ``F``,
   però després se li sumen 7 valors (salta 7 lletres). Llavors el
   punter que rep ``cout`` és d'una taula acabada en 0 a partir de la
   ``'G'``, i per això mostra només aquesta part.

.. exercici::

   *[Aquest exercici encara no està implementat...]*

.. exercici::
   
   *[Aquest exercici encara no està implementat...]*

.. exercici::
   
   *[Aquest exercici encara no està implementat...]*

.. exercici::
   ::

     void copia(int *orig, int *dest) {
       while (*orig != -1) {
         *dest = *orig;
	 orig++; dest++;
       }
       *dest = -1;
     }

.. exercici::

   La funció és més fàcil amb punters perquè no s'ha de calcular
   l'índex a partir d'on ha d'anar la segona taula, el punter ``res``
   ja està situat a lloc::
  
     void concatena(char *c1, char *c2, char *res) {
       while (*c1 != char(0)) {
         *res = *c1;
	 res++; c1++;
       }
       while (*c2 != char(0)) {
         *res = *c2;
	 res++; c2++;
       }
       *res = char(0);
     }
