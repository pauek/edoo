
.. tema:: cl

.. 
   FALTA: - Mètodes modificadors i consultors!

=======
Classes
=======

.. rubric:: Objectius

- Descriure què és una classe, un objecte, i un mètode.

- Descriure els diferents tipus de mètodes d'una classe.

- Descriure els diferents tipus de constructors.

- Determinar si és possible l'accés als membres d'una classe donada la
  seva declaració.

- Implementar TADs en C++ fent servir ``class``.

.. contents:: Contingut 
   :depth: 2
   :local:

Conceptes
=========

Els següents conceptes sobre orientació a objectes no són únics de C++
sinó que són comuns en molts altres llenguatges de programació com
SmallTalk, Java, C#, Python, etc.

classe 
  Tipus Abstracte de Dades implementat amb un llenguatge orientat a
  objectes (tal com C++). 

objecte 
  Una instància d'una classe (una variable d'un TAD concret). De
  classe només n'hi ha una i d'objectes de la mateixa classe n'hi pot
  haver molts.

atribut 
  Cada un dels membres d'un TAD que no són funcions (que són
  dades). Cada objecte té valors diferents en els atributs. 

mètode
  Funció membre d'una classe (funció que forma part del conjunt
  d'operacions d'un TAD). Aquesta nomenclatura és més comú que "funció
  membre".


De ``struct`` a ``class``
=========================

La implementació de TADs en C++ es pot fer amb ``struct`` (les tuples
típiques), però el llenguatge ens proporciona eines més potents si
implementem els TADs fent servir ``class``. La idea principal és:

- Substituir la paraula ``struct`` per ``class`` a la declaració del TAD
  (que es manté gairebé igual que abans). 

La diferència principal entre ``struct`` i ``class`` és que l'accés a
membres està *controlat*. Accedir a un membre d'una tupla és,
bàsicament, fer servir "``.``" per "entrar" dins de la tupla.  Per
entendre millor les diferències d'accés, treballarem amb un exemple
d'un TAD per emmagatzemar una data.

Implementació amb ``struct``: accés lliure
------------------------------------------

Per exemple, considerem la següent declaració d'un TAD implementat amb
un ``struct``::

  struct Data {
    double _dia, _mes, _any;

    void inicialitza(int dia, int mes, int any);
    int dia() const;
    int mes() const;
    int any() const; 
  };

En un programa, podem declarar una ``Data`` i accedir als seus
membres així::

  Data d;
  d.dia = 12;
  d.mes = 4;
  d.any = 1495;

El fet d'accedir directament, però, incompleix les regles d'ús d'un
TAD, que diuen que només s'ha d'accedir als mètodes, no als membres
directament. El codi hauria de ser així::

  Data d;
  d.inicialitza(12, 4, 1495);

La idea, és que amb ``struct`` no tenim manera de **prohibir** que en
alguna part del codi del programa aparegui un accés als camps ``dia``,
``mes`` i ``any`` directament. És a dir, no podem fer complir la regla
que els TADs es manipulen amb mètodes exclusivament. Això és
degut a que les tuples tenen accés lliure.


Implementació amb ``class``: accés controlat
--------------------------------------------

Si implementem la ``Data`` com un ``class``::

  class Data {
    int _dia, _mes, _any;
  public:
    void inicialitza(int dia, int mes, int any);
    void dia() const;
    void mes() const;
    void any() const;
  };

la cosa canvia. Els canvis en la sintaxi, bàsicament, són posar
``class`` en comptes de ``struct`` i afegir ``public:`` abans dels
mètodes. Però hi ha un altre canvi important, no tan visible. Si
intentem compilar les instruccions següents::

  Data d;
  d.dia = 1; // error!
  d.mes = 9; // error!

el compilador ens dóna error (que significa que no vol compilar el
programa!), i per tant, o bé canviem l'accés directe als camps ``dia`` i
``mes`` o llavors no compilarà. Si llavors posem::

  Data p;
  p.inicialitza(1, 9, 1571);

no hi haurà cap problema. 

.. exercici::
   
   Compila el següent programa i mira amb atenció l'error que
   produeix::
   
     class Prova {
       int x;
     };

     int main() {
       Prova p;
       p.x = 1;
     }    

   .. solucio::

      L'error el dóna en l'accés i diu, exactament::
   
         acces.cpp: In function ‘int main()’:
         acces.cpp:3: error: ‘int Prova::x’ is private
         acces.cpp:8: error: within this context
   
      Primer senyala el camp ``x`` al que intentem accedir (a la línia 3
      del programa ``acces.cpp``) i després diu en quin context l'accés
      és privat (la línia 8 de ``acces.cpp``, el punt exacte a on hem
      intentat accedir).

Accés ``public`` i ``private``
------------------------------

public
  Els membres del TAD són accessibles des de qualsevol lloc, tant des
  dels mètodes com des del codi que fa servir el TAD.

privat        
  Els membres del TAD només són accessibles desde les operacions del
  TAD (els mètodes). Només desde la barrera d'abstracció cap
  endins podem accedir, desde fora es produeix un error.

De fet, la paraula ``public:`` de la declaració de ``Data`` indica
que, a partir d'allà, els membres declarats *són* accessibles. Tot el
que hi ha abans és privat, o sigui no accessible. Per tant, la
declaració de la classe es podria haver fet així::

  class Data {
  public:
    void inicialitza(int dia, int mes, int any);
    void dia() const;
    void mes() const;
    void any() const;
  private: // ho diem explícitament
    int _dia, _mes, _any;
  };

Les dues clàusules ``private:`` i ``public:`` canvien l'accés dels
membres del TAD que venen a continuació. Per tant ``_dia``, ``_mes`` i
``_any`` són privats i els mètodes ``inicialitza``, ``dia``, ``mes`` i
``any`` són públics. Per defecte, en un ``class`` un membre és
privat. Per exemple, la següent classe té tots els membres privats::

  class ForatNegre {
    double massa;    
    void emet_llum();
  };

La distinció entre ``public`` i ``private`` té efecte quan l'accés es
fa desde fora de la barrera d'abstracció, és a dir, en parts del
programa que no siguin la implementació del TAD. Quan definim el
mètode ``inicialitza``::

  void Data::inicialitza(int dia, int mes, int any) {
    _dia = dia; _mes = mes; _any = any;
  }

l'accés als membres és correcte, ja que ``inicialitza`` forma part del
TAD, i ha de poder accedir tranquilament als membres ``private`` (qui
ha de poder, si no?).

.. exercici::

   Considera les següents declaracions::
     
     struct A {     class B { 	   class C {     class D {
       int x, y;      int x, y;    public: 	 private:
     };		    };               int x;	   int x, y;
     				   private:	 public:
         	    		     int y;        int z;
         	    		   };            };

   i suposant els 4 objectes::

     A a; B b; C c; D d;

   digues si els següents accessos donarien un error::

     a.x = 1;  b.y = 2;
     c.x = 3;  d.y = 4;
     a.y = 5;  b.x = 6;
     c.y = 7;  d.z = 8;

   .. solucio::
      
      ::
                                              
        a.x = 1; // ok  			   
        b.y = 2; // error: y és privat a B	   
        c.x = 3; // ok			   
        d.y = 4; // error: y és privat a D	   
        a.y = 5; // ok			   
        b.x = 6; // error: x és privat a B	   
        c.y = 7; // error: y és privat a C	   
        d.z = 8; // ok                        

.. exercici::

   Donada la següent classe::
    
     class tExemple { 
       int a;  
       char c; 
     public: 
       string s; 
       void posa_a(int x); 
       string mostra_s() const; 
     };

   i assumint que en un programa donat apareix la declaració::

     tExemple e;
 
   justifica perquè les següents instruccions són correctes o
   incorrectes en cada cas::

     e.a = 1;
     e.posa_a(5);
     posa_a(e,7);
     mostra_s(e);
     e.mostra_s(7);
     e.mostra_s = 7;
     e.c = 'a';
     e.s = "hola";
     e.c = 5; 
     e.s = 'y';

   .. solucio::

      ::
                                                                          
        e.a = 1;        // error: 'a' és privat			       
        e.posa_a(5);    // ok					       
        posa_a(e,7);    // error: 'posa_a' s'ha de cridar sobre	       
                        //   algun objecte				       
        mostra_s(e);    // error: 'mostra_s' s'ha de cridar sobre	       
                        //   algun objecte i no té paràmetres	       
        e.mostra_s(7);  // error: 'mostra_s' no té paràmetres	       
        e.mostra_s = 7; // error: 'mostra_s' és un mètode, no un atribut  
        e.c = 'a';      // error: 'c' és privat			       
        e.s = "hola";   // ok					       
        e.c = 5;        // error: 'c' és privat i de tipus 'char'	       
        e.s = 'y';      // error: 's' és de tipus 'string', no 'char'.    


.. exercici::

   Transforma el codi següent de tal manera que faci servir ``class``
   en comptes de ``struct`` i les operacions del TAD siguin
   mètodes. Implementa també els mètodes ``get_y``, ``get_z`` i
   ``resta_vectors``::
   
     struct tVector3D { double comp[3]; // Les 3 components };
 
     double get_x(const tVector3D& v) { return comp[0]; }  
     // get_y, get_z
 
     void suma_vectors(tVector3D& v1, const tVector& v2) { 
       for (int i = 0; i < 3; i++) 
          v1.comp[i] += v2.comp[i]; 
     } 
     // resta_vectors
 
     double norma(const tVector3D& v) { 
       double acum = 0.0; 
       for (int i = 0; i < 3; i++) 
         acum += v.comp[i]*v.comp[i]; 
       return sqrt(acum); 
     }

   .. solucio::
    
      ::
      							      
         class tVector3D {					      
           double comp[3];					      
         public:						      
           tVector3D();					      
         							      
           double get_x() const;				      
           double get_y() const;				      
           double get_z() const;				      
         							      
           void   suma_vectors(const tVector3D& v2);	      
           void   resta_vectors(const tVector3D& v2);	      
           double norma() const;				      
         };						      
         							      
         tVector3D::tVector3D() {				      
           comp[0] = comp[1] = comp[2] = 0.0;		      
         }							      
         							      
         double tVector3D::get_x() const { return comp[0]; }     
         double tVector3D::get_y() const { return comp[1]; }     
         double tVector3D::get_z() const { return comp[2]; }     
         							      
         void tVector3D::suma_vectors(const tVector3D& v2) {     
           for (int i = 0; i < 3; i++) 			      
             comp[i] += v2.comp[i];			      
         }							      
         							      
         void tVector3D::resta_vectors(const tVector3D& v2) {    
           comp[0] -= v2.comp[0];				      
           comp[1] -= v2.comp[1];				      
           comp[2] -= v2.comp[2];				      
         }							      
         							      
         double tVector3D::norma() const {			      
           double acum = 0.0;				      
           for (int i = 0; i < 3; i++) acum += comp[i]*comp[i];  
           return sqrt(acum);				      
         }                                                       

Mètodes consultors i modificadors
---------------------------------

Amb freqüència passa que necessitem mètodes per consultar o modificar
els atributs d'una classe, pel fet que un cop els posem com
``private`` no es podran accedir directament:

- **Mètodes consultors** (*getters*): Són mètodes senzills que
  serveixen per obtenir una dada d'un objecte (com ara el mètode
  ``size`` de la classe ``string``, que permet obtenir el tamany d'un
  ``string``).

- **Mètodes modificadors** (*setters*): Són mètodes també senzills que
  permeten canviar una propietat d'un objecte.

La nomenclatura *getters* i *setters* vé del significat de *get*, que
és "obtenir" i de *set*, que és "posar" o "canviar".

Exemple amb la classe ``Vector2D``
""""""""""""""""""""""""""""""""""

Els mètodes consultors i modificadors es poden veure amb un exemple::

  class Vector2D {
    double _x, _y;
  public:
    Vector2D();
    Vector2D(double x, double y);

    // mètodes consultors 
    double get_x() const;
    double get_y() const;
    
    // mètodes modificadors
    void set_x(double x);
    void set_y(double y);
  };

Els mètodes ``get_x`` i ``get_y`` ens permeten obtenir la 'x' i la 'y'
del vector, i els mètodes ``set_x`` i ``set_y`` ens permeten
modificar-les. Les implementacions de tots 4 són::

  double Vector2D::get_x() const {
    return _x;
  }

  double Vector2D::get_y() const {
    return _y;
  }

  void Vector2D::set_x(double x) {
    _x = x;
  }

  void Vector2D::set_y(double y) {
    _y = y;
  }

Els mètodes consultors porten, generalment, un ``const`` darrere
perquè com que no modifiquen el vector, només consulten una de les
coordenades. 


Constructors
============

En C++ existeix un tipus de mètode especial encarregat de la
inicialització. Aquesta tasca, en la classe ``Data``, la feia la funció
``inicialitza``, ja que si els membres ``_dia``, ``_mes`` i ``_any``
són privats, posar els valors inicials no és possible desde fora de la
barrera d'abstracció.

constructor 
  Mètode especial encarregat exclusivament d'inicialitzar un
  objecte. Un constructor *no té tipus de retorn*. Per poder
  identificar un mètode com a constructor se li ha de posar el mateix
  nom que a la classe. Una classe pot tenir més d'un constructor.

En l'exemple de la classe ``Data`` anterior, per transformar el mètode
``inicialitza`` en un constructor hem de fer 2 canvis: canviar el nom
de ``inicialitza`` per ``Data``, i treure el tipus de retorn (eliminar
el ``void``). La declaració de la classe seria, doncs::

  class Data {
    int _dia, _mes, _any;
  public:
    Data(int dia, int mes, int any);
    
    int dia() const;
    int mes() const;
    int any() const;
  };

La implementació del constructor seria::

  Data::Data(int dia, int mes, int any) {
    _dia = dia;
    _mes = mes;
    _any = any;
  }

Tipus de constructors
---------------------

Hi ha 3 tipus de constructors:

- Per defecte: un constructor que no rep paràmetres. Aquest
  constructor, ja que no rep dades amb les que inicialitzar un
  objecte, hauria de posar els valors "típics" que han de tenir els
  membres d'un objecte si no es diu res més.

- De còpia: un constructor que rep un sol paràmetre i és una
  referència constant a un objecte de la classe que s'està
  definint. 

- La resta, els "normals", reben paràmetres de qualsevol tipus.

Si posem els 3 tipus de constructors a la classe ``Data``, tindrem::

  class Data {
    int _dia, _mes, _any;
  public:
    Data();              // per defecte
    Data(const Data& d); // de còpia
    Data(int dia, int mes, int any); 

    int dia() const;
    int mes() const;
    int any() const;    
  };

Les implementacions serien::

  // Constructor per defecte
  Data::Data() {
    // posem una data de "referència"
    _dia = 1;
    _mes = 1;
    _any = 2000;
  }

  // Constructor de còpia
  Data::Data(const Data& d) {
    // copiem els valors de la data que ens passen
    _dia = d._dia;
    _mes = d._mes;
    _any = d._any;
  }

La implementació del constructor normal es pot veure en l'exemple de
més amunt.

Crida al constructor
--------------------

Els constructors no són com els mètodes normals, perquè no es criden
amb la notació de tuples (amb el "``.``"). De fet es criden
automàticament quan es crea un objecte (per exemple, quan declarem una
variable de la classe). A més, la creació d'un objecte d'una classe
*obligatòriament* crida algun constructor. La idea, doncs, és que en
el moment de crear un nou objecte d'una classe podem utilitzar un
constructor o un altre en funció de com creem l'objecte.

Ús del constructor per defecte
""""""""""""""""""""""""""""""

Si declarem una variable com ho hem fet sempre::
  
   Data d;

es crida el constructor per defecte.

Ús del constructor de còpia
"""""""""""""""""""""""""""

La crida al constructor de còpia té dues versions::

   Data d;     // per defecte
   Data e1 = d; // versió 2
   Data e2(d);  // versió 1

La primera versió vol imitar la inicialització d'un valor tal com en::

   int a = 1;

La segona és per imitar l'ús del constructor normal, que porta els
arguments de la crida entre parèntesis.

Ús del constructor normal
"""""""""""""""""""""""""

Per fer servir el constructor normal, hem de fer la declaració d'un
objecte de la classe ``Data`` afegint els paràmetres entre
parèntesis::

   Data d(25, 2, 2009);

És una mescla entre una declaració de variable i la crida a una
funció. Els paràmetres 25, 2 i 2009 es passen en l'ordre que posem,
tal com en les crides a funcions, i inicialitzaran els camps de la
data de la forma correcta. Ara es veu com la versió 2 de l'ús del
constructor de còpia és semblant al normal.

A part, en relació a l'ús dels parèntesis en constructors també cal
dir una cosa important: el constructor per defecte **NO** es pot
cridar així::

   Data d();

Potser és contraintuïtiu, però això dóna un error de compilació. Per
cridar el constructor per defecte no es posen parèntesis, tal com s'ha
esmentat anteriorment.

Crides barrejades
"""""""""""""""""

També és possible, fer més d'una crida a constructors diferents en una
mateixa línia, fent servir comes per separar, com per exemple::

   Data d(4, 8, 1976), e(17, 11, 1975), f;
   Data g(d), h = d, i, j(23, 1, 2005);

.. 
   exercici::

   Determina la sortida del següent programa::

     class X {
       int a, b;
     public:
       int get_a() const;
       int get_b() const;
     };

     int X::get_a() const { return a; }
     int X::get_b() const { return b; }

     int main() {
       X x;
       cout << x.get_a() << ' ' << x.get_b() << endl;
     }


.. exercici::
   
   Declara i implementa els 3 constructors típics per a la classe següent::

      class Punt2D {
        double x, y;
      public:
        // ...
      };   

   .. solucio::

      La declaració serà::
   
        class Punt2D {
          double _x, _y;
        public:	 
          Punt2D();                // per defecte
          Punt2D(const Punt2D& p); // de còpia
          Punt2D(double x, double y);
        };
   
      La implementació, doncs, és::
   
        Punt2D::Punt2D() {
          _x = 0.0;
          _y = 0.0;
        }
   
        Punt2D::Punt2D(const Punt2D& p) {
          _x = p.x;
          _y = p.y;
        }
   
        Punt2D::Punt2D(double x, double y) {
          _x = x;
          _y = y;
        }
   
.. exercici::

   Escriu la declaració exacta del constructor que es crida quan obrim
   un fitxer de sortida així::

      ofstream fout("dades.txt");

   .. solucio::
   
      La declaració del constructor per a ``ofstream`` ha de ser::
     
        class ofstream {
          // ...
        public:
          // ...
          ofstream(string nom_fitxer);
        };
   
      Es tracta d'un constructor normal, no és de còpia ni per
      defecte. A part de la declaració d'aquest constructor no sabem res
      més, però la declaració del constructor aniria dins de la de la
      classe ``ofstream``.
   
Altres detalls sobre constructors
---------------------------------

Absència de constructors
""""""""""""""""""""""""

Si una classe *no té cap constructor* declarat, es crea un constructor
per defecte que no fa res (no inicialitza els atributs). La següent
classe::

  class Frase {
    string paraules[100];
    int nparaules;
  public:
    void llegeix(istream& i);
    void escriu(ostream& o) const;
  };

no té constructors i malgrat això, podem crear objectes de la classe
``Frase``::

  int main() {
    Frase F;
    cout << "Escriu una frase: ";
    F.llegeix(cin);
  }

Absència de constructor per defecte
"""""""""""""""""""""""""""""""""""

Si una classe no té constructor per defecte, però en té un de normal,
llavors la única forma de crear objectes és passant els parametres del
constructor que hi ha.

El següent programa dóna un error de compilació::

  class X {
    int _a;
    char _c;
  public:
    X(int a, char c);
  };

  X::X(int a, char c) { _a = a; _c = c; }
  
  int main() {
    X x; // error!
  }

La idea és que la declaració de l'objecte ``x`` hauria de portar els 2
paràmetres requerits pel constructor (un enter i un caràcter).


Si no hi ha constructor de còpia, se'n posa un
""""""""""""""""""""""""""""""""""""""""""""""

En tots els cassos, en absència del constructor de còpia, C++ en posa
un, que el que fa és copiar, un per un, cada atribut de la classe. El
següent programa és un cas::

  class Y {
    string _s;
    double _d;
  public:
    Y(string s, double d);
    string get_s() const;
    double get_d() const;
  };

  Y::Y(string s, double d) {
    _s = s; _d = d;
  } 
  
  string Y::get_s() const { return _s; }
  double Y::get_d() const { return _d; }
    
  int main() {
    Y a("hola", 1.5);
    Y b = a; // es fa servir el constructor de còpia
    cout << b.get_s() << ' ' << b.get_d() << endl;
  }

El programa mostra per pantalla::

  hola 1.5

ja que mostream les dades de ``b``, que és una còpia de ``a``.


Constructors en classes compostes
"""""""""""""""""""""""""""""""""

Una classe composta té atributs que alhora són objectes d'altres
classes. Una classe ``Ordinador``, per exemple, té un atribut que és
un ``Processador``, d'una classe diferent.

Suposem que ``Processador`` és::

  class Processador {
    // ...
  public:
    Processador(double velocitat); // constructor normal
  };

La classe ``Processador`` no té constructor per defecte, i per tant la
única forma de construir un objecte ``Processador`` és utilitzar el
constructor de què disposem, obligatòriament amb 1 paràmetre (com es
comenta més amunt).

Si la classe ``Ordinador`` té com a atribut un objecte de la
classe ``Processador``::

  class Ordinador {
    Processador _cpu1, _cpu2;
    
  public:
    Ordinador(double velocitat); // constructor normal
  };

per força el constructor de ``Ordinador`` haurà de cridar al
constructor de ``Processador``, passant-li la ``velocitat``. Per fer
aquesta crida s'ha d'utilitzar una sintaxi especial. La implementació
del constructor de ``Ordinador`` serà::

  Ordinador::Ordinador(double velocitat)
    : _cpu1(velocitat), _cpu2(velocitat) // crida als constructors
  {
  }

La sintaxi consisteix en posar "``:``" i fer una crida als
constructors amb el nom de l'atribut i els paràmetres entre
parèntesis. En aquest cas la crida al constructor no es pot fer amb el
nom de la classe (``Processador``) perquè si n'hi ha dos, com en
aquest cas, no es podria distingir quin és cadascún. Si hi ha més d'un
atribut, les diferents crides se separen per comes. Per altra banda,
donat que ``Ordinador`` només té els atributs ``_cpu1`` i  ``_cpu2``,
el cos del constructor (entre ``{`` i ``}``) queda buit.

.. exercici::
   
   Tenint en compte les declaracions següents::
  
     class Motor {
       // ...
     public:
       Motor(string marca, double cilindrada);
     };

     class Cotxe {
       Motor _motor;
     public:
       Cotxe(string marca_motor, double cilindrada);
     };
     
   Implementa el constructor de la classe ``Cotxe``.

   .. solucio::

      ::
        
         Cotxe::Cotxe(string marca_motor, double cilindrada)
           : _motor(marca_motor, cilindrada)
         {        
         }



   

Problemes
=========

.. problema::

   Es vol fer un programa per classificar les notes dels alumnes per
   intervals d'un punt. És a dir, volem comptar quants alumnes tenen
   una nota entre 0 i 1, entre 1 i 2, etc. fins a 10. Una gràfica que
   mostri aquestes dades s'anomena histograma.

   #. Fes un programa que, donada una seqüència de notes acabada en
      -1.0, mostri per pantalla el número d'alumnes que tenen notes en
      cada interval fent servir la classe ``Histograma``::

        class Histograma {
          // ...
        public:
          Histograma();
	  void afegeix(double valor); // afegeix un valor
  	  int  quantitat(int index);
	};

      El mètode ``quantitat`` retorna el número de valors que s'han
      afegit entre ``index`` i ``index + 1``.

   #. Implementa la classe ``Histograma``.

   .. solucio::
      
      Primer fem la funció principal. Es tracta de fer servir un objecte
      concret ``Histograma`` per anar emmagatzemant els valors que anem
      llegint::
    
        int main() {
          Histograma H;
          double nota;
          
          // Llegim les dades
          cin >> nota;
          while (nota != -1.0) {
          	 H.afegeix(nota);
            cin >> nota;
          }            
   
          // Mostrem els resultats
          for (int k = 0; k < 11; k++) {
            cout << "Entre " << k << " i "<< k+1 
   	      << "  " << H.quantitat(k) << endl;
          }
        }
   
      A l'hora de mostrar els resultats es posa també la columna 10 (que
      conté les Matrícules d'Honor), per això l'índex ``k`` arriba fins
      al 10.
   
      Un cop implementada la funció principal, implementem la classe
      ``Histograma``. Farem la implementació fent servir una taula de
      comptadors, a cada casella hi haurà el nombre de valors que hem
      vist en aquell rang (a la casella 2 el número de valors entre 2 i
      3). La declaració amb els atributs posats és::
   
         class Histograma {
           int _columnes[11]; // 11 per poder posar MH de nota.
         public:
           Histograma();
   	void afegeix(double valor); // afegeix un valor
   	int  quantitat(int index);
         };
   
      La implementació del constructor ha d'inicialitzar la taula de
      comptadors, posant cada casella a 0::
   
         Histograma::Histograma() {
           for (int k = 0; k < 11; k++) 
   	  _columnes[k] = 0;
         }
   
      La implementació d'``afegeix`` converteix el valor a enter (trunca
      el valor, traient els decimals). Per assegurar el tret, abans de
      fer la conversió, truncarem el valor real amb la funció
      ``floor``. Amb el valor enter, podem anar a la casella amb aquest
      índex i incrementar-ne el contingut, primer comprovant que no se
      surt de la taula::
   
         void Histograma::afegeix(double valor) {
           int i = int(floor(valor));
   	if (i >= 0 && i < 11)
   	  _columnes[i]++;
   	else
   	  cout << "Advertència: fora de rang" << endl;
         }
   
      Finalment, quan s'ha de retornar el valor de l'``Histograma`` per a
      certa columna (el mètode ``quantitat``), es pot retornar
      directament el valor d'aquesta casella, primer comprovant que
      l'índex no se surt del rang::
   
         int Histograma::quantitat(int index) {
           if (index >= 0 && index < 11)
   	  return _columnes[index];
   	else 
   	  return 0; // no comptem fora d'aquest rang
         }
   
.. problema::
   
   Implementa una classe que sigui un conjunt d'enters petit (de com a
   màxim 1000 elements i els elements han de ser enters entre 0 i
   999). El TAD ha de permetre les següents operacions sobre el conjunt:
      
   - afegir un enter,
   
   - eliminar un enter,
   
   - determinar si un enter hi pertany,
   
   - obtenir el número d'elements,
     
   - afegir tots els enters d'un altre conjunt,
   
   - eliminar tots els enters d'un altre conjunt,
   
   - determinar si el conjunt és igual a un altre.
   
   Implementa el constructor per defecte i el de còpia.
   
   .. solucio::
    
      .. Utilizar "literalinclude" con :lines: 10-20 para incluir
      .. porciones!

      Primer declarem la classe, decidint els paràmetres i els noms del
      mètodes (i si són ``const`` o no). Un cop fet això decidim quina
      implementació farem::
   
         class Conjunt {
           // ...
         public:
           Conjunt(); // c. per defecte
	   Conjunt(const Conjunt& C); // c. de còpia
	   void afegeix(int n);
	   void elimina(int n);
	   bool pertany(int n) const;
	   int  tamany() const;
	   void afegeix_tots(const Conjunt& C);
	   void elimina_tots(const Conjunt& C);
	   bool igual(const Conjunt& C) const;
	 };

      Un cop feta la declaració podem implementar el ``Conjunt`` de dues
      maneres:
    
      - Com una taula d'enters, de màxim 1000 elements, a on
        emmagatzemem els valors de cada enter per separat. La taula es
        mantindrà ordenada, per facilitar la cerca d'elements i la
        comparació de conjunts.

      - Com una taula de ``bool``\s, a on cada casella representa un
        dels enters, i conté ``true`` si l'enter pertany al conjunt i
        ``false`` si no.

      Farem les dues implementacions. 

      **Versió amb taula d'enters**

      Hem de declarar els atributs de la classe (els membres de dades)::

          class Conjunt {
            int _elem[1000];
            int _nelem;
          public:
            // igual que més amunt
          };

      Amb aquest implementació, el constructor ha de "buidar" el
      conjunt::

         Conjunt::Conjunt() {
           _nelem = 0;
         }

      i el constructor de còpia s'ha de copiar la taula parcialment
      plena (només a on interessa)::

        Conjunt::Conjunt(const Conjunt& C) {
          for (int i = 0; i < C._nelem; i++) {
            _elem[i] = C._elem[i];
          }
          _nelem = C._nelem;
        }

      Llavors venen les operacions d'afegir i esborrar. Per poder-les
      implementar fàcilment, necessitarem poder insertar elements a
      certa posició, esborrar elements a certa posició i cercar
      elements. Aquestes operacions són necessàries per al implementació
      però no són mètodes que vulguem cridar desde fora (no formen part
      del TAD), per tant les farem privades (i posarem un subratllat
      "``_``" a davant per cridar l'atenció sobre aquest fet). Cal
      afegir a la declaració::

         class Conjunt {
           // ...
         	 
         private:
           void _inserta(int n, int pos);
           void _esborra(int pos);
           int  _cerca(int n) const;
              
         public:
           // ...
         };

      Si posem aquestes tres declaracions immediatament després dels
      atributs ``_elem`` i ``_nelem``, llavors no caldria posar
      "``private:``" abans. Implementem les 3::
     
         void Conjunt::_inserta(int n, int pos) {
           for (int k = _nelem; k > pos; k--) {
             _elem[k+1] = _elem[k];
           }
           _elem[pos] = n;
           _nelem++;
         }
         
         void Conjunt::_esborra(int pos) {
           for (int k = pos; k < _nelem - 1; k++) {
             _elem[k] = _elem[k+1];
           }
           _nelem--;
         }
         
         // Retornem la posició de l'element major o igual que 'n'
         // [Cerca linial, potser podria ser binària]
         int Conjunt::_cerca(int n) const {
           int k = 0;
           while (k < _nelem && _elem[k] < n) {
             k++;
           }
           return k;
         }

      La inserció i l'esborrat fan tot el moviment dels valors amunt i
      avall de la taula, copiant en l'ordre correcte entre caselles
      adjacents per anar desplaçant tots els elements que s'han de moure.
      
      La cerca aprofita el fet que la taula ``_elem`` està ordenada i si
      veu que l'element pel que passa és més gran, ja hauriem d'haver
      vist el número que busquem i per tant surt del bucle. De fet surt
      quan l'element és major o igual, de manera que si el trobem, al
      sortir del bucle la ``k`` ha parat a la posició exacta. Desde fora
      podem comprovar si la posició que es retorna correspon a l'element
      buscat o no. Això serà util a l'hora d'insertar (per veure si
      l'element ja hi pertanyia al conjunt).
      
      Amb aquestes 3 funcions podem implementar més fàcilment la
      inserció i l'esborrat (en aquesta implementació)::

         void Conjunt::afegeix(int n) {
           int pos = _cerca(n);
           if (_elem[pos] != n) {
             _inserta(n, pos);
           }
         }
   
         void Conjunt::elimina(int n) {
           int pos = _cerca(n);
           if (_elem[pos] == n) {
             _esborra(pos);
           }
         }
   
      Fent servir ``_cerca`` podem implementar també el mètode
      ``pertany``::

         bool Conjunt::pertany(int n) const {
           int pos = _cerca(n);
           return _elem[pos] == n;
         }

      Per obtenir el número d'elements retornem simplement ``_nelem``::

         int Conjunt::tamany() const {
           return _nelem;
         }

      Per afegir tots els elements d'un altre conjunt, que hem anomenat
      ``afegeix_tots``, farem un bucle i cridarem a ``afegeix`` amb cada un, i
      el mateix per ``elimina_tots``::
    
         void Conjunt::afegeix_tots(const Conjunt& C) {
           for (int i = 0; i < C._nelem; i++)
             afegeix(C._elem[i]);
         }
      
         void Conjunt::elimina_tots(const Conjunt& C) {
           for (int i = 0; i < C._nelem; i++)
             elimina(C._elem[i]);
         }

      Per saber si dos conjunts són iguals, ja que les taules que
      contenen els elements estan ordenades, es pot mirar si són iguals
      (quan vegi una sola diferència puc dir que no són iguals)::

         bool Conjunt::igual(const Conjunt& C) const {
           bool iguals = true;
           int k = 0;
           while (k < _nelem && k < C._nelem && iguals) {	
             if (_elem[k] != C._elem[k]) {	 
               iguals = false;
             }
             else k++;
           }
           return iguals;
         }

      Aquí finalitza la implementació d'aquesta versió de
      l'exercici. Pots :download:`descarregar el codi d'aquest exercici<../src/Classes/conjunt_v1.cpp>`.

      **Versió amb taula de Booleans**

      L'altra versió seria implementar la classe amb un vector que
      indica si un element pertany o no al conjunt amb un valor ``bool``.

      .. literalinclude:: ../src/Classes/conjunt_v2.cpp   
   
      Pots :download:`descarregar aquest codi<../src/Classes/conjunt_v2.cpp>`.


.. problema::

   Implementa la classe ``Frase`` de forma que el següent programa
   (:download:`frase_main.cpp <../src/Classes/frase_main.cpp>`) funcioni
   perfectament com dóna a entendre

   .. literalinclude:: ../src/Classes/frase_main.cpp

   .. solucio::

      El problema de la frase té un fitxer de capçalera
      (:download:`frase.h <../src/Classes/frase.h>`) com el següent

      .. literalinclude:: ../src/Classes/frase.h

      La implementació es faria a :download:`frase.cpp
      <../src/Classes/frase.cpp>` i seria així

      .. literalinclude:: ../src/Classes/frase.cpp



.. rubric:: Bibliografia

Bjarne Stroustrup, *The C++ Programming Language*, Third
Edition. Addison-Wesley, 2004. Capítol 10, Classes.

`http://en.wikipedia.org/wiki/Class_(computer_science)
<http://en.wikipedia.org/wiki/Class_(computer_science)>`_

Bruce Eckel, `Thinking in C++ <http://www.mindview.net/Books/TICPP/ThinkingInCPP2e.html>`_, Volume
1, 2nd Edition. Prentice Hall, 2000. **Capítol 5**. Aquest llibre és de
lliure distribució i d'aquest capítol existeix una 
`traducció al castellà <http://arco.esi.uclm.es/~david.villa/pensar_en_C++/products/vol1/C5.html>`_.
