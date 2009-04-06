
================
Memòria Dinàmica
================

.. rubric:: Objectius

- Escriure programes que utilitzen correctament els operadors ``new``
  i ``delete`` per reservar memòria de qualsevol tipus.

- Desciure els errors típics derivats de la gestió incorrecta de la memòria.

- Descriure la utilitat del destructor en el context de la memòria
  dinàmica.

- Implementar classes que continguin punters com a membres i reservin
  memòria dinàmicament.


Gestió de la memòria
====================

La gestió dinàmica de la memòria permet sobrepassar certes limitacions
----------------------------------------------------------------------

Quan un programa s'executa té dos zones de memòria que pot utilitzar:

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
``new``, que es pot cridar de 3 formes diferents (si bé s'assemblen bastant):

1. ``new A[n]``: on ``A`` és un tipus bàsic i ``n`` és un
   enter. Aquesta versió retorna un punter a una taula de ``n``
   elements del tipus ``A``. El valor de ``n`` pot provenir d'una
   variable, no ha de ser una constant. Si ``n`` és 1, també es pot
   posar ``new A``.

2. ``new B(...)``: on ``B`` és el nom d'una classe (o un ``struct``) i
   els paràmetres que l'acompanyen són els d'un constructor de la
   classe ``B``.

3. ``new C[n]``: on ``C`` és el nom d'una classe *amb constructor per
   defecte* i ``n`` un enter. Es retorna un punter a una taula de
   ``n`` objectes de tipus ``C`` inicialitzats amb el constructor per
   defecte. Si aquest no existeix, hi haurà un error de compilació. El
   valor de ``n`` pot no ser una constant.

En tots 3 cassos, ``new`` retorna una adreça a la zona de memòria
reservada, que s'ha de guardar en un punter del tipus pertinent.

Vegem exemples de cada cas. El següent programa reserva espai per a
una taula d'1000000 d'enters, i després l'omple amb els enters de l'1
al 1000000. És un exemple del cas 1::

  int main() {
    int *pI, *p;
    pI = new int[1000000];
    p = pI;
    for (int k = 1; k <= 1000000; k++) {
      *p = k;
      p++;
    }
  }

Un exemple del cas 2 pot ser el següent. Si tenim una classe
``Punt3D`` que representa punts tridimensionals amb la següent
declaració::

  class Punt3D {
    // ...
  public:
    Punt3D(); // inicialitza amb (0, 0, 0)
    Punt3D(double x, double y, double z);
    double get_x() const;
    double get_y() const;
    double get_z() const;
  };

Podem reservar un ``Punt3D`` en memòria dinàmica així::

  Punt3D *p = new Punt3D(0.0, 1.0, 0.5);
  cout << "El punt és: (" 
       << p->get_x() << ", " 
       << p->get_y() << ", "
       << p->get_z() << ")" << endl;

El cas 3 seria si volem crear una taula de ``n`` punts, per exemple::

  int npunts;
  cout << "Numero de punts? ";
  cin >> npunts;
  Punt3D *pT = new Punt3D[npunts];

Aquest últim cas també demostra com és possible crear una taula del
tamany que indiqui l'usuari (amb les conseqüències que això pot
tenir).

.. exercici::

   Fes un programa que reservi una taula de 2000000 de Booleans i
   omple les caselles parelles amb ``true`` i les senars amb
   ``false``.


Quan ``new`` no pot reservar la memòria, retorna ``NULL``
---------------------------------------------------------

Fins ara no hem tingut en compte el cas que potser si intentem
reservar més memòria que la que hi ha disponible, no se'ns podrà
concedir. Quan això succeeix, l'operador ``new`` retorna un punter a
l'adreça 0, que també rep el nom de ``NULL``. El següent codi, doncs
reserva una taula però comprova primer si ha pogut reservar la memòria
demanada::

  int nelem;
  cout << "Número d'elements? ";
  cin >> nelem;
  double *p = new double[nelem];
  if (p == NULL) {
    cout << "No s'ha pogut reservar la taula" << endl;
  }
  else {
    // treballar amb la taula
  }

..    Exercici complicat
..    exercici

..    Fes un programa que determini el tamany màxim de memòria que tens
..    disponible. Per fer-ho, fes un bucle que reservi un cert tamany de
..    memòria (una taula de ``char``\s de 1 MegaByte) mentre la crida a
..    ``new`` retorna un punter diferent de ``NULL``. El bucle ha de
..    parar en el moment que ``new`` et retorni ``NULL``, dient quin
..    tamany total has reservat.

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

.. literalinclude:: src/06_Memoria_Dinamica/seq_int.cpp
   :lines: 5-8

Aquest ``struct`` és com una peça d'una cadena. Pot emmagatzemar un
enter i a part també un punter a un altre peça de la cadena (una
``Dada``), que hem anomenat ``prev`` perquè apuntarà a la peça prèvia.

El programa és el següent:

.. literalinclude:: src/06_Memoria_Dinamica/seq_int.cpp

Aquest programa utilitza un punter ``actual`` que apunta a la peça
actual. Al principi aquest punter és ``NULL``, perquè no hi ha cap
peça. Tot seguit llegeix cada element de la seqüència, i quan ho fa,
emmagatzema l'element amb una peça ``nova`` que reserva en memòria. A
``nova`` hi posa l'enter i l'adreça de la peça anterior (que és
l'``actual``), per no perdre el fil. Finalment, la nova peça es
converteix en l'``actual``. Cada enter que llegim incrementa una mica
la memòria que el programa té reservada, però no reservem cap tamany
concret al principi.

Un cop llegida la seqüència, si "tibem del fil", és a dir si a partir
de la peça actual anem mirant el camp ``prev`` i anem saltant de peça
en peça, trobarem tots els enters que hem anat posant. Això és el que
fa el bucle que mostra els enters.

 
L'operador ``delete`` allibera la memòria que indica un punter
--------------------------------------------------------------

Per alliberar una zona de memòria (indicar al sistema operatiu que ja
no la fem servir), farem servir l'operador ``delete``. Aquest operador
es crida sobre un punter (suposem que es diu ``p``) i té dues
versions:

1. Si hem reservat una taula (hem fet servir una versió de ``new`` que
   té corxets), hem de fer servir ``delete[] p``.

2. Si hem reservat un sol objecte fem servir ``delete p``.

Vegem exemples dels dos cassos. Un exemple del primer cas pot ser::

  int *pT = new char[1000];
  // treballa amb la taula
  delete[] pT;

Un exemple del segon cas podria ser, si fem servir la class ``Punt3D``
de més amunt::
  
  Punt3D *p = new Punt3D(1.0, 1.0, 0.0);
  // treballa amb el punt
  delete p;


Quan es gestiona la memòria és fàcil cometre certs errors
---------------------------------------------------------

En un programa a on tota la memòria que es reserva es fa servir fins
al final, no és necessari alliberar-la, ja que quan el programa acaba,
la memòria que tenia reservada s'allibera automàticament. A
l':ref:`exemple anterior <seq_int>` no feiem servir ``delete`` per
aquest motiu precisament. Però en general això no és així.

No alliberar la memòria que ja no es fa servir
""""""""""""""""""""""""""""""""""""""""""""""

Si un programa utilitza memòria dinàmica de forma temporal, és
possible que una porció que hagi reservat ja no li faci falta més
endavant. Quan això succeeix, la memòria s'ha d'alliberar. Si no ho
fem, el sistema operatiu creu que encara la utilitzem, i la té marcada
com a "propietat nostra". Si li demanem més memòria, ens donarà una
altra porció diferent. Eventualment, si el programa va demanant
memòria sense allibrerar la que no fa servir, acapararà tota la
memòria del sistema (això fa que l'ordinador vagi molt lent i que no
es puguin executar altres programes). Aquest tipus d'error s'anomena
una "fuita de memòria" (un *memory leak*).

Un exemple senzill a on això passa és un programa com Photoshop. Quan
obrim una imatge amb Photoshop, el programa reserva memòria per poder
treballar amb la imatge. Si la tanquem, allibera aquesta memòria. Si
no ho fés, en una sessió en que obrim 25 o 30 imatges, de seguida
s'ompliria la memòria de imatges que ja no estan obertes ni s'estan
utilitzant, i s'hauria de tancar el programa i tornar-lo a obrir
(perquè quan tanques un programa, la memòria que ha anat reservant
s'allibera per força). Això seria inacceptable i per tant és clar que
Photoshop allibera la memòria que no fa servir.


Alliberar una posició de memòria dues vegades
"""""""""""""""""""""""""""""""""""""""""""""

Si per error nostre, en un programa fem un ``delete`` de la mateixa
adreça dues vegades, el programa donarà un error d'execució. Un cop
alliberada una adreça de memòria, *és un error alliberar-la un altre
cop*. El següent programa::

  int main() {
    int *p = new int[10];
    delete[] p;
    delete[] p;
  }

dóna un error d'execució. Aquest tipus d'error és fàcil de cometre
quan copiem punters, ja que si tenim una mateixa adreça en dos llocs
diferents, és més fàcil caure al parany de cridar a ``delete`` amb els
dos. Això és força clar en classes que tenen camps que són punters,
com es veurà a la propera secció.


Alguns mètodes son importants en la gestió de memòria
-----------------------------------------------------

Per evitar els dos tipus d'errors comentats anteriorment, quan
implementem una classe que fa reserva dinàmica de memòria, és molt
important implementar correctament: 1) el :ref:`destructor <destructor>`, 2) el
:ref:`constructor de còpia <copyconstr>`, i 3) l':ref:`operador d'assignació <assigop>`.

.. _destructor:

El destructor
"""""""""""""

Si una classe reserva memòria en el moment que es crea un objecte
(perquè aquest objecte té un membre que és un punter), quan l'objecte
desapareix, s'ha d'alliberar la memòria.

Aquesta simetria creació/destrucció en C++ es resol amb un mètode
especial per destruir un objecte: el destructor. Per a una classe
``X`` el destructor té el nom ``~X``, és a dir el mateix que el
constructor però amb un símbol ``~`` de prefix. El destructor *no té
paràmetres*, i es crida automàticament (no el podem cridar nosaltres)
quan un objecte desapareix, i això succeeix quan el bloc de codi que
l'engloba s'acaba. Per exemple::

  {
     Punt3D p1(0.0, 0.5, 1.0); // es construeix p1
     // ...

  } // es destrueix p1

Normalment, el bloc a on resideix un objecte és el de la funció que el
conté (ja sigui la funció ``main`` o una altra). De vegades, però,
tenim variables dins del bloc d'un ``for`` o ``while`` o inclús un
bloc que creem nosaltres mateixos expressament.

En una classe que reserva memòria típicament el constructor crida a
``new`` i el destructor crida a ``delete``. Vegem un exemple::

  class Frase {
    char *_inici, *_capsal;
    int _tam, _ple;
  public:
    Frase(int llarg);
    ~Frase();
    void afegeix(string s);
  };

  Frase::Frase(int llarg) {
    _inici = _capsal = new char[llarg];
    _tam = llarg;
    _ple = 0;
  }

  Frase::~Frase() {
    delete[] _inici;
  }

  void Frase::afegeix(string s) {
    if (_ple + s.size() < _tam) {
      for (int k = 0; k < s.size(); k++) {
        *_capsal = s[k];
        _capsal++;
        _ple++;
      }
    }
  }

Aquesta classe ``Frase`` reserva espai per a una frase de la llargada
indicada en la crida al constructor i quan la frase desapareix, es
crida al destructor, que allibera la memòria. La classe té dos
punters, un a l'inici del text, i un altre al punt actual d'inserció
(``_capsal``). També té dos enters que indiquen el tamany total i el
tamany omplert. El mètode ``afegeix`` permet afegir text a la frase, tret
d'un ``string``.

.. _copyconstr:

El constructor de còpia
"""""""""""""""""""""""

Sens dubte, en la gestió de memòria, el constructor de còpia és un
mètode perillós. El perill prové de que si no el definim, se'n crea un
que copia les dades membre a membre. El problema és que si es copien
punters, llavors l'error de cridar a ``delete`` dues vegades està
assegurat. Si tenim una còpia de dos objectes amb un punter a dins,
quan es cridi al destructor de cadascún es cridarà a ``delete`` amb la
mateixa adreça dos cops. Vegem-ne un cas, si fem servir la classe
``Frase`` definida a l'apartat anterior així::

  int main() {
    Frase f1(250);
    f1.afegeix("The best way to predict the future is to invent it");

    Frase f2(f1);
  }

El programa dóna un error d'execució. Al final de la funció ``main``,
s'alliberen dues adreces de memòria iguals ja que ``f2._inici`` té la
mateixa adreça que ``f1._inici``.

.. exercici::

   Compila el :download:`programa anterior <src/06_Memoria_Dinamica/frase_crash.cpp>` 
   i comprova com dóna un error d'execució.


Per arreglar-ho hem d'implementar el constructor de còpia. En aquest
constructor, hem de reservar memòria i *copiar* la taula que obtenim 
de l'altre frase::

  class Frase {	
    // ...
  public:
    Frase(const Frase& F);
  };

  // ...
   
  Frase::Frase(const Frase& F) {
    _inici = new char[F._tam];
    char *pdest = _inici, *porig = F._inici;
    while (porig != F._capsal) {
      *pdest = *porig;
      pdest++; porig++;
    }
    _capsal = pdest;
    _tam = F._tam;
    _ple = F._ple;
  }

.. _assigop:

L'operador d'assignació
"""""""""""""""""""""""

Si el constructor de còpia és un mètode problemàtic, l'operador
d'assignació encara ho és més. La raó és que l'operador d'assignació
no només fa una còpia membre a membre, sino que la fa d'un objecte que
*ja s'havia creat*, i per tant ja havia reservat memòria. A part del
problema del "doble ``delete``", tindrem una fuita de memòria. Això
succeeix si fem un programa com el següent::

  int main() {
    Frase f1(300);
    f1.afegeix("A programming language is for thinking about programs,");
    f1.afegeix("not for expressing programs you've already thought of.");
    f1.afegeix("It should be a pencil, not a pen.");
    
    Frase f2(100);
    f2 = f1; // igual que f2.operator=(f1);
  }

En el moment que fem "``f2 = f1``", la memòria que ``f2`` havia
reservat (100 caracters) no es podrà alliberar, ja que sobreescrivim
l'adreça de ``f2._inici`` amb ``f1._inici``. I a part, tindrem un
altre cop el problema del "doble ``delete``".

Per arreglar-ho, hem de definir l'operador d'assignació::

  class Frase {
    // ...
  public:
    void operator=(const Frase& F);  
  };

  void Frase::operator=(const Frase& F) {
    delete[] _inici;
    _inici = new char[F._tam];
    char *pdest = _inici, *porig = F._inici;
    while (porig != F._capsal) {
      *pdest = *porig;
      pdest++; porig++;
    }
    _capsal = pdest;
    _tam = F._tam;
    _ple = F._ple;
  }

Com es pot veure, la implementació és la mateixa que el constructor de
còpia però amb una instrucció a dalt de tot que posa ``delete[]
_inici`` (ja que l'assignació només es fa sobre objectes ja construits
i la ``Frase`` ha reservat memòria segur). Normalment, per evitar
aquesta repetició, es fa un mètode privat que faci una còpia d'un
altre objecte i es crida tant des del constructor com desde l'operador
d'assignació.

En definitiva, aquelles classes que tenen punters com a membres amb
tota seguretat hauràn d'implementar el destructor, el constructor de
còpia i l'operador d'assignació. La classe ``Frase`` implementada
correctament seria::

  class Frase {
    char *_inici, *_capsal;
    int _tam, _ple;
    
    void _copia(const Frase& F); // mètode privat
  public:
    Frase(int llarg);
    Frase(const Frase& F);
    ~Frase();

    void operator=(const Frase& F);
    void afegeix(string s);
  };

  Frase::Frase(int llarg) {
    _inici = _capsal = new char[llarg];
    _tam = llarg;
    _ple = 0;
  }

  Frase::Frase(const Frase& F) {
    _copia(F);
  }

  Frase::~Frase() {
    delete[] _inici;
  }

  void Frase::operator=(const Frase& F) {
    delete[] _inici;
    _copia(F);
  }

  void Frase::_copia(const Frase& F) {
    _inici = new char[F._tam];
    char *pdest = _inici, *porig = F._inici;
    while (porig != F._capsal) {
      *pdest = *porig;
      pdest++; porig++;
    }
    _capsal = pdest;
    _tam = F._tam;
    _ple = F._ple;
  }

  void Frase::afegeix(string s) {
    if (_ple + s.size() < _tam) {
      for (int k = 0; k < s.size(); k++) {
        *_capsal = s[k];
        _capsal++;
        _ple++;
      }
    }
  }


Exemple: una taula de tamany variable
=====================================

En C++ si declarem una taula, aquesta té un tamany fix i no es pot
"ampliar". Si hem creat la taula amb 500 caselles i resulta que
després en necessitem més, no podem canviar el tamany. Amb les
classes, però, podem simular això. Podem reservar memòria per a cert
tamany i si després en necessitem més, reservem una zona més gran i
traslladem la taula (la copiem). 

La classe que implementarem es dirà ``Taulavar``, i serà una taula
d'enters, de tamany variable. La seva declaració completa és la
següent:

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.h

La implementació fa servir un punter (el principi de la taula) i dos
enters, un per al tamany màxim (el reservat) i un altre per al tamany
ocupat. La taula té 4 constructors. Hem posat l'operador d'assignació
i el destructor ja que fem servir punters i memòria dinàmica (i també
el constructor de còpia). Amb previsió hem afegit el mètode ``_copia``
que cridaràn tant el constructor de còpia com l'operador d'assignació,
i també un mètode ``_copia_dades`` que només copia dades donats dos
punters i un tamany.

Primer implementem el constructor per defecte, que posarà un ``NULL``
al punter ``_dades``. Això ens permetrà saber si hem reservat memòria
o no (la taula està buida):

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _1+
   :end-before: _1-

El constructor normal reserva una taula amb cert tamany i l'omple de zeros:

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _2+
   :end-before: _2-

Ara implementem els mètodes privats ``_copia`` i ``_copia_dades``:

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _3+
   :end-before: _3-

Amb aquests mètodes, podem implementar tant el constructor de còpia
com l'operador d'assignació:

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _5+
   :end-before: _5-
 
Els mètodes simples d'aquesta classe són obtenir el tamany, consultar
una posició de la taula i modificar una posició de la taula. En
aquests dos últims tenim l'avantatge de que podem comprovar la posició
que ens donen i mirar si està en els límits:

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _6+
   :end-before: _6-

El mètode ``redimensiona`` permet canviar el tamany de la taula (el
màxim reservat, els valors no han de canviar):

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _7+
   :end-before: _7-

Finalment, tenim el mètode ``afegeix``, que fa la taula més gran (en 1
element) i si necessita moure la taula a una zona més gran ho fa
reservant el doble d'espai:

.. literalinclude:: src/06_Memoria_Dinamica/taulavar.cpp
   :start-after: _8+
   :end-before: _8-

Problemes
=========

.. problema::

   Implementa una classe ``Imatge`` que reservi memòria
   dinàmicament. Fes els operadors d'entrada/sortida de manera que
   llegeixin la imatge en format PNM (opcionalment, que detectin si és
   en blanc i negre o en color). Fes mètodes per accedir a un pixel de
   la imatge i per canviar-lo, i per fer operacions simples com
   invertir la imatge o donar-li la volta en l'eix X i Y.  Fes un
   programa que faci servir la classe per realitzar operacions sobre
   imatges reals.

.. rubric:: Bibliografia

Bjarne Stroustrup, *The C++ Programming Language*, Third
Edition. Addison-Wesley, 2004. Capítol 6, secció 6.2.6.

Bruce Eckel, `Thinking in C++ <http://www.mindview.net/Books/TICPP/ThinkingInCPP2e.html>`_, Volume
1, 2nd Edition. Prentice Hall, 2000. **Capítol 13**. Aquest llibre és de
lliure distribució i d'aquest capítol existeix una 
`traducció al castellà <http://arco.esi.uclm.es/~david.villa/pensar_en_C++/products/vol1/C13.html>`_.

   




