
.. tema:: poli

==============
Polimorfisme
==============

.. rubric:: Objectius

- Identificar quins mètodes es cridaran en una crida a mètode ``virtual``.

- Implementar llistes heterogènies.

.. El punter ``this``
.. ==================
.. .. Un buen ejemplo donde necesitas esto? Que no sea Qt?

Punters a objectes de classes derivades
=======================================

Suposem que tenim una classe ``Instrument`` com la següent\ [1]_::

  class Instrument {
  public:
    void toca(int freq) const;
  };
  
  void Instrument::toca(int freq) const {
    cout << "Instrument::toca: " << freq << endl;
  }

Donada la classe ``Instrument``, declarem llavors la classe ``Flauta``::

  class Flauta : public Instrument {
  public:
    void toca(int freq) const;
  };
  
  void Flauta::toca(int freq) const {
    cout << "Flauta::toca: " << freq << endl;
  }

La classe ``Flauta`` simplement redefineix el mètode ``toca`` de forma diferent
que ``Instrument``. Pel fet que és una classe derivada, però, diem que
una ``Flauta`` **és** un ``Instrument``.

Aquest fet, però, té conseqüències en relació als punters: si una
``Flauta`` és un ``Instrument``, llavors podem fer que un punter a un
``Instrument`` apunti a una ``Flauta``. En la pràctica és correcte,
per tant, escriure el següent::

  Flauta f;
  Instrument *i;
  
  i = &f;

O també::

  Instrument *i = new Flauta;

El recíproc, però, no és tant cert. Imaginem que ara tenim una altra
classe::

  class Guitarra : public Instrument {
  public:
    void toca(int freq) const;
  };
  
  void Guitarra::toca(int freq) const {
    cout << "Guitarra:toca: " << freq << endl;
  }

Si en un programa escrivim el següent::

  Instrument *i = new Guitarra;
  Flauta *f;
  
  f = i; // error

Això succeeix perquè en general, si tenim un punter a un
``Instrument`` no tenim perquè suposar que és una ``Flauta``, com
implica l'assignació "``f = i``". De fet, en l'exemple, el punter
``i`` apunta a una ``Guitarra``, que clarament no és una
``Flauta``. Per tant, quan fem servir punters, podem transformar
punters a les classes base (més generals) lliurement, però no a la
inversa. La regla general és que una assignació de punters com::

  X *a;
  Y *b;
  a = b;

és correcta només quan ``X`` és una classe base de ``Y``.

.. exercici::

   Suposant les declaracions següents::

     class A { ... };
     class B : public A { ... };
     class C : public A { ... };
     class D : public C { ... };
     class E : public C { ... };

   indica quines instruccions són incorrectes::
    
     A *x = new B;
     B *y = new C;
     B *z = x;
     C *t = new A;
     D *u = new E;
     E *v = t;
     B *w = y;

``dynamic_cast`` converteix punters a classes derivades
-------------------------------------------------------

Malgrat normalment no es pot assegurar que un punter a una classe base
es pugui transformar a un punter d'una classe derivada, C++ introdueix
un operador que intenta fer la transformació i si no és vàlida,
retorna el punter 0 (que no apunta enlloc). L'operador és ``dynamic_cast``::
  
  X *p;
  Y *q = dynamic_cast<Y *>(p);

i s'aplica com si fos una funció sobre punters de tipus que s'indica a
dins dels angles (important observar la presència de l'asterisc
``*``).

L'exemple, en el cas dels ``Instruments``, seria::

  Instrument *i = new Guitarra;
  Guitarra *g = dynamic_cast<Guitarra *>(i);

A dins dels angles ("``<``" i "``>``") hi va la classe derivada a la
que volem transformar el punter, en aquest cas ``Guitarra``. Com que en
aquest cas la transformació és vàlida, el punter ``g`` serà diferent
de 0. En el cas següent, però::

  Instrument *i = new Flauta;
  Guitarra *g = dynamic_cast<Guitarra *>(i);

el punter ``g`` valdrà 0 perquè clarament ``i`` apunta a una
``Flauta`` que no es pot transformar en una ``Guitarra``.

Detecció de tipus en temps d'execució
-------------------------------------

Seguint amb l'exemple dels instruments podem fer sel següent programa
per comprovar com "sonen" els instruments::

  int main() {
    Flauta f;
    Guitarra g;
    f.toca(440); // un La 3
    g.toca(880); // un La 4
  }

Si executem aquest programa, per pantalla sortirà::

  Flauta::toca: 440
  Guitarra::toca: 880

Fins aquí, res de nou, en principi. El problema apareix si fem un
programa lleugerament diferent::

  int main() {
    Flauta f;
    Guitarra g;
    Instrument *i = f, *j = g; // accedim a f, g a través de i, j
    i->toca(440);
    j->toca(880);
  }

Ara, si executem el programa, esperem la mateixa sortida i en
canvi la sortida és::

  Instrument::toca: 440
  Instrument::toca: 880

que conceptualment és incorrecte, ja que els objectes apuntats per
``i`` i ``j`` no són de classe ``Instrument``, sinó de classe
``Flauta`` i ``Guitarra`` respectivament, i les dues classes han
redefinit el mètode ``toca``!

La idea subjacent és que el compilador de C++, quan té un punter a un
``Instrument`` no s'ho pensa dos cops i crida el mètode
``Instrument::toca`` sense parar atenció a si l'objecte és *realment*
un ``Instrument`` o una classe derivada.

El modificador ``virtual``
""""""""""""""""""""""""""

Per tal que el compilador de C++ faci l'"esforç" de mirar si un mètode
cridat està o no redefinit a una classe derivada en temps d'execució
hem d'indicar-li nosaltres explícitament. Per fer-ho hem de modificar
una mica la declaració de la classe ``Instrument``::

  class Instrument {
  public:
    virtual void toca(int freq) const;
  };

Simplement hem afegit ``virtual`` com a prefix al mètode ``toca``. El
modificador ``virtual`` és com una marca amb la missió d'alertar el
compilador. En un mètode ``virtual`` el compilador es *mira realment
quin és el tipus de l'objecte apuntat, i crida el mètode
corresponent*.  La definició del mètode no cal que porti
``virtual``, només és necessari posar ``virtual`` a la declaració.

Amb aquest simple canvi, ara el segon programa es comportarà correctament::

  Flauta::toca: 440
  Guitarra::toca: 880

Així doncs, donat que tenim la opció de no posar-lo, és la nostra
responsabilitat marcar els mètodes amb ``virtual`` quan això sigui
necessari\ [2]_.

.. exercici::

   Determina la sortida d'aquest programa:

   .. literalinclude:: ../src/Polimorfisme/exercici_virtual.cc
      :start-after: <<<
      :end-before: >>>


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

.. exercici:: 
   
   Indica quin és el problema a la classe següent::

     class A {
     public:
       void metode() = 0;
     }

.. basta con poner "= 0" en la declaración para decir que no tiene implementación.

.. Refinamos la técnica para incluir el caso que la clase base no
.. tiene implementación lógica, sólo las clases derivadas tienen sentido.

.. [1] Aquesta classe no té cap utilitat real, és només una excusa per
       explicar el tema actual.

.. [2] En altres llenguatges, com per exemple Java o Python, no és
       necessari posar ``virtual`` perquè es considera normal que el
       llenguatge cridi els mètodes redefinits per defecte. En això
       C++ és força especial.
