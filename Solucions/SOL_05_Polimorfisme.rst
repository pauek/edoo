
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

.. exercici::
   
   El programa sencer (que pots :download:`descarregar <../src/Polimorfisme/teoria_llistes_heterogenies.cc>`) és:

   .. literalinclude:: ../src/Polimorfisme/teoria_llistes_heterogenies.cc

.. exercici::

   Primer hem de declarar i implementar la classe ``Cercle``
   ::

      class Cercle {
        float x, y, radi;
      public:
        Cercle(istream& i);
	bool a_dins(const Punt& p) const;
      };
      
      Cercle::Cercle(istream& i) {
        i >> x >> y >> radi;
      }

      Cercle::a_dins(const Punt& p) const {
        float dx = p.x - x;
	float dy = p.y - y;
	return sqrt(dx*dx + dy*dy) < radi;
      }

   Després hem de modificar ``llegeix_figures`` per tenir en compte
   els cercles::

      if (tipus == "rectangle") {
        ...   
      }
      else if (tipus == "cercle") {  // +
        nova = new Cercle(Ff);       // +
      }                              // +
      else {
        ...
      }

   Les línies noves estan marcades amb "``// +``".
     
.. exercici::

   [Triangle]

.. exercici::

   El problema és que s'ha fet servir el sufix "``= 0``" en un mètode
   que no és ``virtual`` i això no té sentit.


