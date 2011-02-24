
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

Els tres errors més típics es comenten en les seccions següents.

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





