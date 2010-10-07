
.. tema:: pimd

.. 
  La idea es hacer una descripción tipo "Java" de la memoria dinámica y
  punteros. Super-simplificado. Muy funcional, para poder hacer
  programas con un mínimo de comprensión, sin entrar en detalles.

==========================
Punters i Memòria Dinàmica
==========================

.. rubric:: Objectius

- Declarar punters a una classe qualsevol. Accedir als mètodes d'un
  objecte apuntat.

- Escriure programes que utilitzen correctament els operadors ``new``
  i ``delete`` per reservar memòria de qualsevol tipus.

- Desciure els errors típics derivats de la gestió incorrecta de la memòria.

Punters
=======

Un punter és una variable que conté una referència a una altra variable
-----------------------------------------------------------------------

En aquesta secció treballarem amb la classe ``Data``, que tindrà la
declaració següent::

  class Data {
    // ...
  public:
    Data();
    Data(int dia, int mes, int any);
    int dia() const;
    int mes() const;
    int any() const;
    void llegeix(istream& i);
    void escriu(ostream& o) const;
    // ...
  };


En C++ no només podem declarar variables de qualsevol classe i dels
tipus propis del llenguatge, sinó que podem declarar variables que es
refereixen a altres variables::

  Data d, e;
  Data *p, *q;

Les variables ``p`` i ``q`` són *punters* (com unes "fletxes"). Un
punter es declara en general posant el tipus de variable al que volem
que apunti, i posant un asterisc ('``*``') a davant del nom de la
variable. 

Quan creem la variable ``p``, tal com totes les variables, té un valor
indeterminat (es diu que no "apunta" enlloc). Però la podem fer apuntar a
una altra variable::

  p = &d;

Aquesta instrucció el que fa és dir que ``p`` es referirà a la
variable ``d`` (d'una classe ``Data`` hipotètica). 

El diagrama seria el següent:

.. image:: img/punter_simple.*
   :align: center

És important veure, tanmateix, que ``p`` és realment una
variable i per tant conté un cert valor. De fet, el que conté ``p`` és
l'*adreça* de la variable ``d``. En la inicialització anterior hem
assignat a ``p`` l'adreça de ``d``. Hem fet servir l'operador ``&``,
que extreu l'adreça d'una variable.

Es diu, doncs, que ``p`` apunta a ``d``. Això ens permet accedir a
``d`` a través de ``p``.

.. exercici::

   Escriu dues instruccions que facin que la variable ``q`` apunti a
   ``d`` i ``p`` apunti a ``e``.

.. exercici::

   Segons el codi::

     Rectangle r, s;
     Rectangle *p, *q;
     p = &r;
     q = p;

   A qui apunta ``q``?

.. exercici::

   Donada una classe ``tImatge``, declara una imatge ``I`` i un punter
   ``p`` que apunti a la imatge ``I``.


L'operador ``->`` permet accedir als membres de l'objecte apuntat
-----------------------------------------------------------------

Per accedir als mètodes d'un objecte indirectament a través d'un punter, es fa
servir l'operador ``->``. Si tenim::

  Data d(2, 10, 2004);
  Data *p = &d;

Podem mostrar l'any de la data ``d`` a través de ``p``::

  cout << p->any() << endl;

Per pantalla sortirà::

  2004

.. exercici::
	
   Donada la classe::
    
     class A {
       // ...
     public:
       A(int n);
       void metode1(int x);
       int  metode2() const;
       // ...
     };

   Escriu instruccions per:

   - Crear un objecte ``x`` de la classe ``A``.

   - Crear un punter a ``x``.

   - Cridar els 2 mètodes de ``A`` a través del punter.

   Utilitza dades inventades per satisfer els paràmetres dels mètodes.


Gestió de la memòria
====================

La gestió dinàmica de la memòria permet sobrepassar certes limitacions
----------------------------------------------------------------------

Quan un programa s'executa té dues zones de memòria que pot utilitzar:

- La pila (o *stack*): és una zona petita i de tamany fix. En aquesta
  zona es situen les variables locals que declarem a les funcions.

- El *heap* (o *free store*): és una zona expandible i amb tamany
  limitat només per la memòria disponible. És en aquesta zona a on
  podem reservar memòria dinàmicament.

Llavors, quan declarem una variable en un programa:

A. es fa servir una porció de la pila per col·locar-la; i

B. la porció de memòria que ocupava la variable es recicla quan la
   funció on hem declarat la variable finalitza.

Necessitem fer servir memòria dinàmica, doncs, quan:

A. el tamany de la zona que volem utilitzar és gran (més gran que el
   tamany estàndar de la pila), o

B. algunes dades del nostre programa han de sobreviure a la funció a
   on són creades, és a dir, han de residir en una zona pròpia un cop
   la funció ha finalitzat.


L'operador ``new`` reserva memòria i retorna un punter
------------------------------------------------------

Per reservar memòria de forma dinàmica, farem servir l'operador
``new``, que es crida així:

   ``new A(...)``: on ``A`` és el nom d'una classe i els paràmetres
   que l'acompanyen són els d'un constructor de la classe ``A``.

La crida a ``new`` retorna una adreça a la zona de memòria
reservada, que s'ha de guardar en un punter del tipus pertinent.

Un exemple pot ser el següent: si tenim una classe ``Punt3D`` que
representa punts tridimensionals amb la següent declaració::

  class Punt3D {
    // ...
  public:
    Punt3D(); // inicialitza amb (0, 0, 0)
    Punt3D(double x, double y, double z);
    double get_x() const;
    double get_y() const;
    double get_z() const;
  };

podem reservar un ``Punt3D`` en memòria dinàmica així::

  Punt3D *p = new Punt3D(0.0, 1.0, 0.5);
  cout << "El punt és: (" 
       << p->get_x() << ", " 
       << p->get_y() << ", "
       << p->get_z() << ")" << endl;

.. 
   exercici::

   Fes un programa que reservi una taula de 2000000 de Booleans i
   omple les caselles parelles amb ``true`` i les senars amb
   ``false``.

.. exercici::

   Donada la declaració següent::

     class Data {
     public:
       Data();
       Data(int dia, int mes, int any);
       int dia() const;
       int mes() const;
       int any() const;
       void llegeix(istream& i);
       void escriu(ostream& o) const;
       void incrementa(int dies);
     };

   Fes un programa que demani a l'usuari una data, i mostri per
   pantalla quin dia serà passades 3 setmanes (el mètode
   ``incrementa`` permet incrementar una data un cert número de
   dies). 

   Fes servir una data reservada en memòria dinàmica.

.. _seq_int:

Exemple: Mostrar una seqüència al revés sense límits
----------------------------------------------------

Aquest és un programa que no podiem fer fins ara. Es tracta d'un
programa que llegeix una seqüència d'enters acabada en -1 i tot seguit
la mostra per pantalla al revés, però la seqüència pot tenir un tamany
qualsevol, només limitat per la quantitat de memòria disponible. Per
fer-ho ha d'emmagatzemar la seqüència sencera en memòria, no hi ha cap
altra manera. Fins ara, havíem de suposar un tamany màxim per a la
seqüència, però amb la memòria dinàmica, si ens arriba un nou element,
el podem posar a una zona nova reservada dinàmicament, i així no hem
d'imposar un límit arbitrari.

Per emmagatzemar els elements de la seqüència farem servir un
``struct`` molt peculiar:

.. literalinclude:: ../src/06_Memoria_Dinamica/seq_int.cpp
   :lines: 5-8

Aquest ``struct`` és com una peça d'una cadena. Pot emmagatzemar un
enter i a part també un punter a un altre peça de la cadena (un
``Element``), que hem anomenat ``anterior`` perquè apuntarà a la peça
prèvia.

El programa és el següent:

.. literalinclude:: ../src/06_Memoria_Dinamica/seq_int.cpp
   :linenos:

Aquest programa utilitza un punter ``actual`` que apunta a
l'``Element`` actual. Al principi aquest punter és 0, perquè no hi ha
cap peça. Tot seguit llegeix cada element de la seqüència, i quan ho
fa, emmagatzema l'element amb un ``Element``  ``nou`` que reserva en
memòria (línia 16). A ``nou`` hi posa l'enter i l'adreça de la peça anterior
(que és l'``actual``), per no perdre el fil (línies 17 i 18). Finalment, la nova peça
es converteix en l'``actual`` (línia 19). Cada enter que llegim incrementa una
mica la memòria que el programa té reservada, però no reservem cap
tamany concret al principi.

Un cop llegida la seqüència, si "tibem del fil", és a dir si a partir
de la peça actual anem mirant el camp ``anterior`` i anem saltant de peça
en peça, trobarem tots els enters que hem anat posant. Això és el que
fa la iteració que mostra els enters (línies 24 a 27).

.. exercici::

   Modifica el ``struct Element`` del programa anterior perquè sigui
   una classe. Tindrà la declaració següent

   .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_class.cc
      :lines: 5-14

   Modifica el programa per fer servir la nova classe.

.. exercici::

   Considera la classe ``Contenidor`` amb la declaració i
   implementació següents
    
   .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_stack.cc
      :lines: 29-62

   Aquesta classe fa servir ``Element`` per emmagatzemar enters amb
   els mètodes ``posa`` i ``treu`` (una diferència és que ``treu`` ara
   fa ``delete`` dels elements, tal com ha de ser). Llegeix atentament
   cada mètode per entendre què fa, comparant amb el programa original
   per veure-ho.

   Reimplementa ara el programa fent servir la classe ``Contenidor``.

.. exercici::

   Afegeix el mètode amb declaració::

      int num_elements() const;

   a la classe ``Contenidor`` i implementa'l.

 
L'operador ``delete`` allibera la memòria que indica un punter
--------------------------------------------------------------

Per alliberar un objecte de la memòria (indicar al sistema que ja
no la fem servir), farem servir l'operador ``delete``. Aquest operador
es crida sobre un punter (suposem que es diu ``p``)::

  delete p;

Per exemple, si fem servir la class ``Punt3D`` de més
amunt::
  
  Punt3D *p = new Punt3D(1.0, 1.0, 0.0);
  // treballa amb el punt
  delete p;


Quan es gestiona la memòria dinàmicament és fàcil cometre certs errors
----------------------------------------------------------------------



Accedir a un objecte a través d'un punter no inicialitzat
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Si declarem un punter però no hi posem cap adreça, el punter apunta a
algun lloc igualment. El problema és que l'adreça a la que apunta pot
ser qualsevol. Si el programa intenta accedir a aquesta adreça,
típicament serà abortat pel sistema operatiu amb un missatge que a
Windows és similar a: "Este programa ha realizado una operación
inválida y se cerrará".

Un exemple d'aquest problema seria::

  Data *d;
  d->escriu(cout);

Com es pot veure, just després de declarar el punter es fa servir per
invocar el mètode escriu sense haver-hi posat cap adreça vàlida. Això
provoca el problema.

El mateix problema apareix si posem el valor 0, ja que l'adreça 0 de la
memòria no és accessible per a cap programa.


No alliberar la memòria que ja no es fa servir
""""""""""""""""""""""""""""""""""""""""""""""

En un programa a on tota la memòria que es reserva es fa servir fins
al final, no és necessari alliberar-la, ja que quan el programa acaba,
la memòria que tenia reservada s'allibera automàticament. A
l':ref:`exemple anterior <seq_int>` no feiem servir ``delete`` per
aquest motiu precisament.

Però si un programa utilitza memòria reservada dinàmicament, és
possible que ja no li faci falta més endavant. Quan això succeeix, la
memòria s'ha d'alliberar. Si no ho fem, el sistema operatiu creu que
encara la utilitzem, i la té marcada com a "propietat nostra". Si li
demanem més memòria, ens donarà una altra porció
diferent. Eventualment, si el programa va demanant memòria sense
allibrerar la que no fa servir, acapararà tota la memòria del sistema
(això fa que l'ordinador vagi molt lent i que no es puguin executar
altres programes). Aquest tipus d'error s'anomena una "fuita de
memòria" (un *memory leak*).

Un exemple senzill a on això passa és un programa com Photoshop. Quan
obrim una imatge amb Photoshop, el programa reserva memòria per poder
treballar amb la imatge. Si la tanquem, allibera aquesta memòria. Si
no ho fés, en una sessió en que obrim 25 o 30 imatges consecutivament
(o sigui, no totes alhora), de seguida s'ompliria la memòria de
imatges que ja no estan obertes ni s'estan utilitzant, i s'hauria de
tancar el programa i tornar-lo a obrir (perquè quan el tanques, tota
la memòria s'allibera per força). Això seria inacceptable i per tant
és clar que Photoshop allibera la memòria que no fa servir.


Alliberar una posició de memòria dues vegades
"""""""""""""""""""""""""""""""""""""""""""""

Si per error nostre, en un programa fem un ``delete`` de la mateixa
adreça dues vegades, el programa donarà un error d'execució. Un cop
alliberada una adreça de memòria, *és un error alliberar-la un altre
cop*. El següent programa::

  int main() {
    Data *d = new Data(23, 1, 1789);
    delete d;
    delete d;
  }

dóna un error d'execució. Aquest tipus d'error és fàcil de cometre
quan copiem punters, ja que si tenim una mateixa adreça en dos llocs
diferents, és més fàcil caure al parany de cridar a ``delete`` amb els
dos.


Problemes
=========

No n'hi ha cap de moment.



.. rubric:: Bibliografia

Bjarne Stroustrup, *The C++ Programming Language*, Third
Edition. Addison-Wesley, 2004. Capítol 6, secció 6.2.6.

Bruce Eckel, `Thinking in C++ <http://www.mindview.net/Books/TICPP/ThinkingInCPP2e.html>`_, Volume
1, 2nd Edition. Prentice Hall, 2000. **Capítol 13**. Aquest llibre és de
lliure distribució i d'aquest capítol existeix una 
`traducció al castellà <http://arco.esi.uclm.es/~david.villa/pensar_en_C++/products/vol1/C13.html>`_.

   




