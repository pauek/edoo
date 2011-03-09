
.. tema:: md

Memòria Dinàmica
================

.. contents:: Contingut 
   :depth: 2
   :local:

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


Cas 1: l'operador ``new`` en objectes individuals
-------------------------------------------------

L'operador ``new`` reserva memòria i retorna un punter al nou objecte
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

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

   .. solucio::
      ::

         int main() {
           Data *d = new Data();
           cout << "Data? ";
           d->llegeix(cin);
           d->incrementa(21);
           cout << "Passades tres setmanes la data serà: ";
           d->escriu(cout);
           delete d;
         }
      
..
  No ponemos este ejemplo, demasiado difícil

  include:: Memoria_Dinamica_Exemple_1.rst

L'operador ``delete`` allibera la memòria que indica un punter
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Per alliberar un objecte de la memòria (indicar al sistema que ja
no la fem servir), farem servir l'operador ``delete``. Aquest operador
es crida sobre un punter (suposem que es diu ``p``)::

  delete p;

Per exemple, si fem servir la classe ``Punt3D`` de més
amunt::
  
  // Declarem un punter i reservem un Punt3D dinàmicament
  Punt3D *p = new Punt3D(1.0, 1.0, 0.0);

  // treballem amb 'p'
  // ...

  // Finalment alliberem 'p'
  delete p;

Cas 2: l'operador ``new`` per a taules
--------------------------------------

L'operador ``new`` pot retornar més d'un objecte
""""""""""""""""""""""""""""""""""""""""""""""""

Un altra forma d'utilitzar l'operador ``new`` és per reservar taules
en memòria. Un exemple d'utilització de l'operador per reservar taules
és el següent::

  int main() {
    int *p_enters = new int[500]; // Reservem una taula de 500 enters
  }

En general s'ha d'escriure: ``new``, un tipus i entre corxets, i
després el tamany requerit (``new int[500]``). Per reservar, doncs,
1000 reals seria així::

  new double[1000]

Aquesta expressió retorna l'adreça a on hi ha la taula de 1000
reals. Per poder utilitzar la taula hem d'emmagatzemar-la primer a un
punter::

  double *p_reals = new double[1000];

El primer avantatge de l'operador ``new`` és que el tamany pot ser
qualsevol expressió, és a dir, el tamany és variable::

  int main() {
    int N;
    cout << "Quants reals vols? ";
    cin >> N;
    double *p_reals = new double[N];

    // ... el programa continua
  }

És a dir, el tamany es pot especificar com a una expressió entera
qualsevol, incloent la variable ``N`` que s'utilitza a l'exemple. 

El segon avantatge, i aquest és l'important, és que *el tamany de la
taula que es demana està limitat només per la memòria disponible a
l'ordinador*. Això contrasta amb el fet que si en un programa creem
una variable taula normalment::

  int main() {
    double taula[100];
  }

el seu tamany màxim és molt petit, en comparació amb la memòria de
l'ordinador [2]_.

.. exercici::

   Per determinar el tamany màxim d'una taula reservada *sense*
   memòria dinàmica, compila el següent programa:
     
   .. literalinclude:: ../src/edoo/taula_limit.cpp
      :lines: 2-7

   Compila el programa posant diferents valors de ``N`` (1000, 10000,
   100000, 1000000) fins que el programa doni un error de Windows
   tipus: "Aquest programa ha deixat de funcionar...". El programa
   realment no fa res útil, però quan superes el límit, dóna aquest
   error.

   Ara fes un programa equivalent que si que reserva memòria dinàmica
   i comprova com pots compilar-lo normalment amb un tamany igual o
   més gran.


Per alliberar la memòria d'una taula es fa amb ``delete[]``
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

En el cas de les taules, la crida a ``delete`` és una mica diferent,
ja que s'ha d'indicar amb corxets que quan s'ha reservat memòria era
per una taula. Si reservem memòria per 100 objectes ``Data`` [1]_::

  Data *p_dates = new Data[100];

Després haurem d'alliberar aquesta memòria amb::

  delete[] p_dates;

La diferència amb el cas anterior és només que s'han afegit els
corxets (``[]``) com a sufix de ``delete``.


Exemple: taula de tamany variable
---------------------------------

En aquesta secció farem una classe ``Taula`` que permetrà emmagatzemar
un número variable de reals. Començarem per declarar la classe:

.. literalinclude:: ../src/edoo/taula.h
   :start-after: 0+
   :end-before: 0-
   :linenos:

La declaració diu que la classe només té dos atributs: un ``p_reals``
que és un punter a reals, i un enter per guardar el tamany. Aquest
punter tindrà l'adreça del principi de la taula de reals que farà
servir cada objecte de tipus ``Taula``. Després tenim 4 constructors,
entre ells el constructor per defecte i el de còpia. Els 2
constructors normals permeten especificar un tamany per a la ``Taula``
i un d'ells permet indicar quin valor inicial volem. Finalment, tenim:

- ``get``: que permet obtenir una casella de la taula.
- ``set``: que permet modificar una casella de la taula.
- ``tamany``: que permet obtenir quin és el tamany de la taula.

Anem a veure, doncs, la implementació de cada un.

Al constructor per defecte (línia 5) el que farem és posar un valor al punter
``p_reals`` que indica que la taula està buida. Aquest valor serà 0,
simplement. L'adreça de memòria 0 mai es pot consultar en un programa
i per tant serveix per dir que el punter no apunta enlloc. També
posarem el ``_tamany`` a 0:

.. literalinclude:: ../src/edoo/taula.cpp
   :start-after: 1+
   :end-before: 1-

En el constructor que rep un tamany (línia 6), hem de reservar memòria per als
reals i posar-hi algun valor (un 0, per exemple). També hem de guardar
el tamany que se'ns ha passat en la crida al constructor i
inicialitzar la taula sencera a 0.0:

.. literalinclude:: ../src/edoo/taula.cpp
   :start-after: 2+
   :end-before: 2-

En el constructor que rep un tamany i un valor (línia 7), hem de fer
el mateix que en el constructor anterior i en comptes de posar un 0.0
a tot arreu, posar el valor que ens passen:

.. literalinclude:: ../src/edoo/taula.cpp
   :start-after: 3+
   :end-before: 3-

L'últim constructor, el de còpia, ha de reservar tant d'espai com té
la taula que ens copiem i copiar cada casella:

.. literalinclude:: ../src/edoo/taula.cpp
   :start-after: 4+
   :end-before: 4-


Ara ja podem implementar els mètodes ``get``, ``set`` i ``tamany``,
que són més senzills. Comencem pel més fàcil:

.. literalinclude:: ../src/edoo/taula.cpp
   :start-after: 5+
   :end-before: 5-

Els mètodes ``get`` i ``set`` permeten obtenir el valor d'una casella
(``get``) i posar-hi un valor (``set``). Així doncs:

.. literalinclude:: ../src/edoo/taula.cpp
   :start-after: 6+
   :end-before: 6-

Un cop la classe està acabada, podem fer un programa principal per
provar-la. El següent programa llegeix una seqüència de reals d'un
fitxer ``valors.txt`` i mostra per pantalla la diferencia de cada
element amb la mitjana:

.. literalinclude:: ../src/edoo/taula_main.cpp
   :lines: 2-32   

..
  No hablamos de errores, inútil por ahora...

  include:: Memoria_Dinamica_Errors.rst


.. [1] Per poder fer això ha d'existir el constructor per defecte de ``Data``.

.. [2] El límit està més o menys entre 4 i 8 Megabytes, quan les memòries actuals
       són d'alguns Gigabytes, que és de l'ordre de mil de cops més gran.
