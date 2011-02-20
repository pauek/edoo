
.. tema:: ops

.. Meter funciones friend!!

========================
Operadors i Sobrecàrrega
========================

.. rubric:: Objectius

- Determinar quina funció concreta es fa servir en una crida
  sobrecarregada.

- Definir operadors per a una classe donada. Definir l'operador
  d'entrada i de sortida.


Sobrecàrrega
============

Sobrecarregar és posar el mateix nom a funcions diferents
---------------------------------------------------------

En C++ funcions diferents poden tenir exactament el mateix nom (això
inclou també mètodes). Per exemple, en comptes d'haver de posar un nom
diferent a les diferents funcions per intercanviar dos valors::

   void swap_int(int& a, int& b);
   void swap_char(char& a, char& b);
   void swap_string(string& a, string& b);

podem posar el mateix nom::

   void swap(int& a, int& b);
   void swap(char& a, char& b);
   void swap(string& a, string& b);

Com es pot saber, doncs, en el moment de cridar una funció, de quina
es tracta? Doncs a partir de la seva *signatura*.

signatura 
  La signatura d'una funció és tota aquella informació que permet
  identificar-la. Es tracta de (1) el nom, (2) el número de paràmetres
  i (3) els *tipus* dels paràmetres. El tipus de retorn **no** forma
  part de la signatura, o sigui que no es poden distingir funcions
  diferents pel tipus de retorn.

Es veu clar, doncs, que el nom és només una de les característiques
rellevants i que es pot repetir sempre i quan les altres coses siguin
diferents (ja sigui el número de paràmetres o el tipus dels
paràmetres).

De fet, quan declarem una funció estem declarant una signatura de
funció i per tant no és necessari posar el *nom* dels paràmetres, amb
el tipus és suficient. Les declaracions següents són equivalents a les
vistes anteriorment::

  void swap(int&, int&);
  void swap(char&, char&);
  void swap(string&, string&);

Es pot distingir quina funció concreta s'utilitza en certa crida
perquè la signatura ha de ser evident::

  int i = 5, j = 7;
  swap(i, j);

Pel fet que crido a l'accio ``swap`` amb dos enters, s'entén que es
cridarà la versió ``swap(int&, int&)``. Si cridem una funció i no hi
ha cap versió amb aquell nom que tingui la signatura compatible,
llavors és quan hi ha un error de compilació::

  char c;
  double x;
  swap(c, x);   // error: no hi ha cap funció amb aquesta signatura

.. exercici::

   Donada la declaració de les següents funcions::

     void manipula(int x, int y);         // 1
     void manipula(double x, double y);   // 2
     void manipula(char c);               // 3
     void manipula(string s);             // 4
     int  manipula(int x, int y, bool t); // 5
     void manipula(int x, bool t);        // 6

   i assumint que en un programa hipotètic existeixen les següents
   declaracions::
   
     int a, b;
     char l, m;
     string x, y;
     bool p, q;
     double r, s;

   digues quina de les funcions ``manipula`` en concret s'utilitza per
   a les següents crides o si no hi ha cap funció compatible::

     manipula(a, true);           manipula(3, 4, p);
     manipula(r, s);              manipula(a, 5.7);
     manipula(4, q);              manipula(r, "Fiji");
     manipula(a, 5);              manipula(char(98));
     manipula(68);                manipula(17, q);
     
   .. solucio::
  
      ======================= ====== =================================================
      Crida                   Funció Comentaris
      ----------------------- ------ -------------------------------------------------
      ``manipula(a, true)``   6
      ``manipula(r, s)``      2
      ``manipula(4, q)``      2
      ``manipula(a, 5)``      1
      ``manipula(68)``        3      Es converteix el caracter a enter implícitament
      ``manipula(3, 4, p)``   5
      ``manipula(a, 5.7)``    2      ``a`` es converteix a double implícitament     
      ``manipula(r, "Fiji")`` X      No hi ha cap funció compatible
      ``manipula(char(98))``  3
      ``manipula(17, q)``     6
      ======================= ====== =================================================

Operadors
=========
        
Un operador és una funció amb un nom especial
---------------------------------------------

En C++, la creació de nous tipus (típicament classes) comporta,
d'alguna manera, que estiguem "ampliant" el llenguatge. Si implementem
un tipus ``Complex`` per representar números complexos, estem ampliant
els tipus numèrics com ``int`` i ``float``. 

El següent programa assumeix l'existència d'una classe ``Complex`` i
llegeix dos números complexos fent servir un mètode ``llegeix`` (no
definit), calcula la suma (fent servir el constructor de còpia i el
mètode ``suma``, tampoc definit) i finalment mostra el resultat per
pantalla::

  Complex c1, c2;
  c1.llegeix(cin);
  c2.llegeix(cin);
  Complex c3(c1.suma(c2));
  c3.escriu(cout);
  cout << endl;

Aquest codi, però, és molt diferent del codi que resultaria de fer
les mateixes operacions amb ``double``\s::

  double d1, d2;
  cin >> d1 >> d2;
  cout << d1 + d2 << endl;

De fet, no ens ha calgut la variable ``d3`` per emmagatzemar la suma,
ja que la podem posar directament a la instrucció ``cout``.

El que voldriem, doncs, és poder fer el mateix per a nombres
complexos, poder escriure una cosa com::

  Complex c1, c2;
  cin >> c1 >> c2;
  cout << c1 + c2 << endl;

És possible aconseguir això en C++ amb l'ajuda dels operadors. Amb
això, podrem dir que les classes que fem seran tan completes i
"creïbles" com els propis tipus bàsics de C++: ``int``, ``char``,
``float``, i ``bool`` (i sembla que haguem oblidat ``string`` però
``string`` resulta que és una classe, no un tipus bàsic).

operador 
  Funció de C++ amb un nom especial: ``operator`` seguit del símbol de
  l'operador. Els següents operadors es poden definir en C++ (excepte
  per als tipus bàsics): ``+``, ``-`` (binari i unari), ``*``, ``/``,
  ``%``, ``=`` (assignació), ``<`` (menor), ``>`` (major), ``<=``,
  ``>=``, ``<<`` (sortida), ``>>`` (entrada), ``&&`` (and), ``||``
  (or), ``++`` (increment), ``[]`` (accés a taula), ``+=``, ``-=``,
  ``*=``, ``/=``, i alguns més, una mica més complicats. Els
  operadors, per ser funcions, es poden sobrecarregar.


Una expressió es pot transformar en una crida a un operador
-----------------------------------------------------------

Vegem un exemple::
  
  Vector2D v1, v2;
  Vector2D v3 = v1 + v2;

La suma "``v1 + v2``" es tradueix com la crida a una funció operador::

  operator+(v1, v2);

El fet que es pugui sumar amb objectes de diferents tipus implica que
puc tenir vàries funcions ``operator+`` amb paràmetres de tipus
diferent, i per tant vol dir que els operadors típicament estan
sobrecarregats.

Declaració d'operadors
""""""""""""""""""""""

Per altra banda, el significat original dels operadors fa que les
funcions en què es transformen tinguin un número de paràmetres i uns
tipus concrets. Per exemple, l'operador suma extern té aquesta
signatura::

  Vector2D operator+(const Vector2D& v1, const Vector2D& v2);

És a dir, sumar dos vectors implica rebre com a paràmetre aquests
vectors i retornar-ne un altre. Els paràmetres no es veuen modificats
per la suma, per tant s'han de passar amb ``const``.

Per exemple, la comparació de números complexos tindria la següent
signatura::

  bool operator<(const Complex& c1, const Complex& c2);

És a dir, el resultat de comparar dos números complexos és cert o
fals, o sigui un ``bool``. Finalment, els operadors unaris (amb només
un operand), tal com el canvi de signe, lògicament reben només un
paràmetre::

  Complex operator-(const Complex& c); // canvi de signe

.. exercici::

   Escriu les declaracions (per a la classe ``Complex``) dels operadors
   ``*``, ``<=``. 

   .. solucio::

      L'operador multiplicació es declararia com::

        Complex operator*(const Complex& c1, const Complex& c2);
   
      L'operador de "menor o igual" seria::
   
        bool operator<=(const Complex& c1, const Complex& c2);

.. exercici::

   L'operador d'assignació també és una funció, si tenim que ``c1`` i
   ``c2`` són objectes de la classe ``Complex``, l'assignació::

      c1 = c2;

   es pot escriure també com::

      operator=(c1, c2);
   
   Escriu la declaració d'aquest operador.

   .. solucio::
   
      La declaració de l'operador d'assignació, degut a que modifica l'operand de l'
      esquerra (la variable la que assignem) té la següent declaració::
   
        Complex operator=(Complex& var, const Complex& valor);
   
      A part, per poder fer assignacions en cadena, tal com::
    
        a = b = c;
   
      l'operador ha de retornar un ``Complex``, ja que la assignació en cadena es 
      pot veure com::
   
        a = (b = c);


La prioritat dels operadors
---------------------------

La transformació de crides pot implicar més d'un operador, i llavors
s'ha de seguir la prioritat relativa entre ells. Per exemple, si
``v1``, ``v2`` i ``v3`` són vectors, les expressions::

   v1 + v2 * v3
   v1 + v2 - v3
   2 * v1 + v2

es transformaran (respectivament) en::

   operator+(v1, operator*(v2, v3));
   operator-(operator+(v1, v2), v3);
   operator+(operator*(2, v1), v2);

Això concorda amb l'ordre d'avaluació de les crides a funcions: en el
primer cas, per exemple, per cridar ``operator+(v1, ...)``, haig
d'haver obtingut el valor dels operands, i per tant haig d'haver
cridat primer ``operator*(v2, v3)``.

.. exercici::

   Suposant les declaracions::
    
     int x, y, z;
     char c, d;
     bool p, q, r;
     float f, g;

   escriu la traducció a crides d'operadors de les expressions
   següents, tenint en compte la prioritat dels operadors de C++::

     -x
     x - y
     x / y / z
     p || q && r
     !q
     x + 1 < y - 2

   .. solucio::

      ========================== =======================================================
      Expressió                  Traducció
      -------------------------- -------------------------------------------------------
      ``-x``		               ``operator-(x)``
      ``x - y``		            ``operator-(x, y)``
      ``x / y / z``	            ``operator/(operator/(x, y), z)``
      ``p || q && r``	         ``operator||(p, operator&&(q, r))``
      ``!q``     	  	            ``operator!(q)``
      ``cout << f << endl``      ``operator<<(operator<<(cout, f), endl)``
      ``x + 1 < y - 2``	         ``operator<(operator+(x, 1), operator-(y, 2))``
      ``cout << z + 3 << endl``  ``operator<<(operator<<(cout, operator+(z, 3)), endl)``
      ========================== =======================================================

Implementació d'operadors
-------------------------

Els operadors són funcions normals, però amb un nom concret. La seva
implementació ha de ser fidel al significat que tenen, al que esperem
que succeeixi quan els fem servir.

Vegem un exemple complet. Partim de la classe ``Vector2D`` amb la
declaració següent::

  class Vector2D {
    double _x, _y;
  public:
    Vector2D(double x, double y);
    double get_x() const;
    double get_y() const;
  };

Les implementacions dels mètodes serien::

  Vector2D::Vector2D(double x, double y) {
    _x = x;
    _y = y;
  }

  Vector2D::get_x() const { return _x; }
  Vector2D::get_y() const { return _y; }

Llavors volem afegir un operador de suma, per tal de poder escriure
una cosa com::

  Vector v1(1.0, 0.0), v2(0.0, 1.0);
  Vector v3 = v1 + v2;

La implementació del mètode serà::

  Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
    double x = v1.get_x() + v2.get_x();
    double y = v1.get_y() + v2.get_y();
    Vector2D res(x, y);
    return res;
  }

Això ens mostra com la suma de vectors és un vector a on cada
component per separat és la suma de les components dels vectors
sumats. Aquesta interpretació de la suma de vectors és realment la
suma matemàtica i per tant és fidel al que s'espera.

A vegades, però, el significat de cridar certs operadors no és gaire
clar. Per exemple, què significa multiplicar 2 vectors? Tenim vàries
opcions:

- Fer el producte escalar.
- Multiplicar cada component.
- Fer el producte vectorial.

En general, si un operador no fa una cosa òbvia, és important
documentar quina funció fa exactament per tal que no hi hagi confusió
(i fins i tot evitar fer-los servir si hi pot haver la més mínima
confusió).

.. exercici::

   Observa la implementació del següent operador::

      Vector2D operator*(const Vector2D& v, double d) {
        Vector2D res(v.get_x() / d, v.get_y() / d);
        return res;
      }

   Quin nom hauria de tenir realment?

   .. solucio::

      L'operador hauria de dir-se ``operator/``, ja que realitza la "divisió" d'un vector de 
      dues dimensions per un real.


Els operadors d'E/S retornen un tipus especial per poder-los encadenar
----------------------------------------------------------------------

Quan volem mostrar per pantalla un enter, fem::
  
   cout << 2;

Això, realment és una crida a un operador::

   operator<<(cout, 2);

No només això, sinó que per poder encadenar vàries crides a
l'operador::

   cout << "Hola, em dic " << nom;

que es tradueix així::

   operator<<( operator<<(cout, "Hola, em dic "), nom );

el que s'ha de fer és retornar un ``ostream&`` en l'operador. És a
dir, podriem veure l'expressió de dalt com::

  (cout << "Hola, em dic ") << nom;

Primer es fa la operació amb ``"Hola, em dic "`` i el resultat
d'aquesta operació és el primer operand de la segona (i per tant també
ha de ser un ``ostream``.

operador sortida
  ::

    ostream& operator<<(ostream& o, const ClasseX& objx) {
      // codi per mostrar l'objecte 'objx'
      return o;
    }

  La última instrucció ``return o`` permet, doncs, encadenar vàries
  sortides amb l'operador ``<<``.

operador entrada
  ::

    istream& operator>>(istream& i, ClasseX& objx) {
      // codi per llegir l'objecte 'objx'
      return i;
    }

  Ara, però, el paràmetre ``ClasseX`` ja no és ``const`` perquè la
  lectura de objectes implica que l'objecte es modifica.

.. exercici::

   Transforma el codi següent en el seu equivalent amb crides a
   operadors::

      int a, b;
      cin >> a >> b;
      cout << " a + b = " << a + b << endl;

   .. solucio::
   
      El codi transformat serà::
   
        int a, b;
        operator>>( operator>>(cin, a), b );
        operator<<( operator<<( operator<<(cout, " a + b = "), a + b ), endl );

.. exercici::

   Considera la classe ``Assignatura``::
 
     class Assignatura {
       string nom;
       int codi;
       bool lliure_eleccio, fase_selectiva;
     public:
       // ...
     };

   Implementa els operadors d'entrada i sortida per a aquesta
   classe. Escriu tant la declaració com la implementació.

   .. solucio::
   
      Per poder accedir als membres d'``Assignatura``, farem l'operador una funció ``friend``. 
      La declaració serà, doncs::
   
        class Assignatura {
          // ...
        public:
          // ...
          friend ostream& operator<<(ostream& o, const Assignatura& A);
        };
   
      La implementació pot ser::
   
        ostream& operator<<(ostream& o, const Assignatura& A) {
          o << A.nom << ' ' << A.codi << ' ';
          if (A.fase_selectiva) o << "[fase_selectiva] ";
          if (A.lliure_eleccio) o << "[lliure_eleccio]";
          return o;
        }
   
   
Els operadors poder ser mètodes
-------------------------------

Realment, hi ha dues versions de l'operador suma per a ``Vector2D``::

  operator+(v1, v2);  // versió normal, "externa".
  v1.operator+(v2);   // versió mètode

La segona és un mètode (funció membre de la classe ``Vector2D``) i la
primera és una funció normal. I potser més important, la versió amb
mètode només rep un paràmetre, en comptes de dos. Això s'explica
perquè el primer operand serà l'objecte per al qual cridem al mètode.

Si un operador és mètode d'una classe, això li dóna accés als membres
de la classe. Com que moltes vegades, per realitzar la operació que
se'ns demana, necessitem accedir als atributs d'un objecte, és
relativament típic que molts operadors siguin mètodes.

Reprenent l'exemple del ``Vector2D``, la implementació de l'operador
de suma extern era molt feixuga. La implementació amb un mètode té,
ara, dues parts: afegir la declaració del mètode::

   class Vector2D {
     // ...
   public:	
     Vector2D operator+(const Vector2D& v) const;
   };

La declaració és molt diferent. Només té un paràmetre perquè l'operand
de l'esquerra serà l'objecte per al qual cridem el mètode. I és
``const`` perquè una suma com ``a + b`` no modifica ni la variable
``a`` ni la ``b``. La implementació serà, doncs::

   Vector2D Vector2D::operator+(const Vector2D& v) const {
     Vector2D res(_x + v._x, _y + v._y);
     return res;
   }

Degut a que podem accedir als atributs del vector directament, la
operació una mica més senzilla.

.. exercici::

   Considera la classe ``Data``::

     class Data {
       int _epoch;  // número de dies desde 1/1/2000
     public:
       Data();
       Data(const Data& d);
       Data(int dia, int mes, int any);
     };

   El membre ``_epoch`` és un enter que indica el número de dies que
   han passat desde l'1 de Gener de 2000. Fes, doncs, un operador de
   suma que permeti fer el següent::
     
     Data d1, d2;
     // ...
     d2 = d1 + 10; // d2 és d1 + 10 dies

   Fes la suposició que l'operador d'assignació ja existeix.

   .. solucio::

      L'operador per sumar dies a una data serà senzill perquè la
      classe fa servir un enter que representa el número de dies
      directament i per tant no hem de tenir en compte el mes de l'any
      ni quants dies té, etc. L'operador és la suma amb un enter, i si
      el fem com a mètode, es declararia aixi::
   
        class Data {
          // ...
        public:
          Data operator+(int num_dies);
        };
   
      La implementació ha de crear una data nova (perquè la que se
      suma no canvia) i a la nova data posar-li la suma dels dies de
      la data sumada + el número que ens passen::
    
        Data Data::operator+(int num_dies) {
          Data d;
          d._epoch = _epoch + num_dies;
          return d;
        }


.. exercici::

   Suposant una declaració d'una classe ``Patata`` tal com::
 
     class Patata {
       // ...
     public:
       // ...
       friend Patata operator+(Patata p, int x);
       friend double operator<<(double f, Patata p);
       friend ostream& operator&&(ostream& o, Patata p);
       int operator*(int x);
       int operator/(int x);
     };

   Digues de quin tipus serien (quin és el tipus resultat) i com
   s'interpretarien en termes de crides a operadors les següents
   expressions (quan siguin correctes). Si no hi ha cap operador
   disponible que permeti avaluar l'expressió correctament,
   indica-ho. Les variables ``p`` i ``pp`` són de tipus ``Patata``::

     1.5 + p
     p + 2.0
     cin >> p
     p / 3
     cout && p
     p * 7
     7.5 << p << pp

   .. solucio::
   
      ========================== ==========================================
      Expressió                  Traducció
      -------------------------- ------------------------------------------
      ``1.5 + p``		            [Error: no hi ha cap operador disponible]
      ``p + 2.0``                ``operator+(p, 2.0)``
      ``cin >> p``		         [Error: no hi ha cap operador disponible]
      ``p / 3``  		            ``p.operator/(3)``
      ``cout && p``	            ``operator&&(cout, p)``
      ``p * 7``		            ``p.operator*(7)``
      ``7.5 << p << pp``	      ``operator<<(operator<<(7.5, p), pp)``
      ========================== ==========================================
   

Problemes
=========

.. problema::

   Considera la següent declaració d'una classe ``Vector10``::

     class Vector10 {
       double comp[10]; // les 10 components del vector
     public:
       // ...  
     };
  
   Declara un operador per a la suma ("``+``") de ``Vector10``, que
   suma component a component. Implementa l'operador com a mètode.

   .. solucio::
      
      Primer declarem l'operador dins de la classe (ja que és intern)::
        
        class Vector10 {
          // ...
        public:
          double operator*(const Vector10& v) const;
        };

      Tot seguit l'implementem::
   
        void Vector10::operator*(const Vector10& v) const {
          double acum = 0.0;
          for (int k = 0; k < 10; k++) {
            acum += comp[k] * v.comp[k];
          }
          return acum;
        }
   
   
.. problema::

   Fes una classe ``Hora`` que permeti manipular dades temporals
   (hores, minuts i segons). Implementa la classe completa: 
   
   - Separa la declaració i la implementació en fitxers diferents
     (``.h`` i ``.cpp``).

   - Fes tots els operadors convenients: comparació, menor (i menor o
     igual), major (i major o igual), suma de dues hores (suma dels
     temps), resta de dues hores (resta dels temps).

   - Implementa operadors de sortida que mostrin la hora en format
     ``05:39:03``, i la llegeixin en el mateix format.

   - Implementa un mètode per obtenir el número de segons i un
     constructor per crear una hora a partir d'un número de segons.

   .. solucio::
   
      Primer fem el fitxer :download:`hora.h <../src/03_Operadors/hora.h>`
      que contingui la declaració de la classe ``Hora``:
    
      .. literalinclude:: ../src/03_Operadors/hora.h
   
      Tot seguit creem el fitxer :download:`hora.cpp <../src/03_Operadors/hora.cpp>`
      que contingui la implementació de la classe ``Hora`` (incloent el fitxer ``hora.h``):
   
      .. literalinclude:: ../src/03_Operadors/hora.cpp
   

.. problema::

   Fent servir la classe ``Hora`` de l'exercici anterior, implementa un
   programa que llegeixi una sequència d'intervals (parelles d'hores)
   i calculi la mitjana de la durada temporal de cada interval (en
   hores, minuts i segons).

   .. solucio::
   
      El programa seria el següent (:download:`hora_main.cpp <../src/03_Operadors/hora_main.cpp>`)
   
      .. literalinclude:: ../src/03_Operadors/hora_main.cpp
   
      Confeccionar un :download:`fitxer de prova <../src/03_Operadors/intervals.txt>` amb 
      uns intervals temporals pot anar bé per provar el programa.


.. rubric:: Bibliografia

Bjarne Stroustrup, *The C++ Programming Language*, Third
Edition. Addison-Wesley, 2004. Capítol 11.

Bruce Eckel, `Thinking in C++ <http://www.mindview.net/Books/TICPP/ThinkingInCPP2e.html>`_, Volume
1, 2nd Edition. Prentice Hall, 2000. **Capítol 12**. Aquest llibre és de
lliure distribució i d'aquest capítol existeix una 
`traducció al castellà <http://arco.esi.uclm.es/~david.villa/pensar_en_C++/products/vol1/C12.html>`_.

