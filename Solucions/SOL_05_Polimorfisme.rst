
.. tema:: poli

==============
Polimorfisme
==============

.. exercici::

   Per fer aquest exercici ens hem de fixar an l'assignació localment
   (no en les instruccions prèvies, a on es pot haver posat un valor
   que finalment sí que concorda). Si un punter potencialment pot
   tenir un objecte d'un tipus que no concorda amb el punter al que
   assignem, estarà malament::

     A *x = new B;  
     B *y = new C;  // error
     B *z = x;      // error (veure comentari)
     A *t = new D;
     C *u = new E;
     E *v = t;      // error
     B *w = y;

   El cas ``z = x`` mereix un comentari. Malgrat en principi veiem que
   l'assignació seria correcta (perquè ``x`` apunta a un objecte de tipus
   ``B``), en el moment que el compilador veu una assignació d'un
   punter d'una classe base a una derivada ho considerarà un error.

.. exercici::

   La sortida del programa és::
   
     $$##$${x}{y}{z}
