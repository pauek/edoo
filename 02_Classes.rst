
.. 
   FALTA: - Mètodes modificadors i consultors!

=======
Classes
=======

Objectius
=========

- Descriure què és una classe, un objecte, i un mètode.

- Descriure els diferents tipus de mètodes d'una classe.

- Descriure els diferents tipus de constructors.

- Implementar TADs en C++ fent servir ``class``.


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
  d.dia = 35; // je je...

El fet d'accedir directament, però, incompleix les regles d'ús d'un
TAD, que diuen que només s'ha d'accedir als mètodes, no als membres
directament. El codi hauria de ser així::

  Data p;
  p.inicialitza(2.5, 4.8);

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
    void inicialitza(int _dia, int _mes, int _any);
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
  private: // ho diem explícitament
    int dia, mes, any;
  public:
    void inicialitza(int _dia, int _mes, int _any);
    void dia() const;
    void mes() const;
    void any() const;
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

.. exercici::

   Escriu la declaració exacta del constructor que es crida quan obrim
   un fitxer de sortida així::

      ofstream fout("dades.txt");


Altres detalls sobre constructors
---------------------------------

Absència de constructor per defecte
"""""""""""""""""""""""""""""""""""

Si una classe no té constructor per defecte, llavors la única forma de
crear objectes és passant els parametres del constructor que hi ha.

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

En absència del constructor de còpia, C++ en posa un, que el que fa és
copiar, un per un, cada atribut de la classe. El següent programa és
un cas::

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
    Parella(double velocitat);
  };

La classe ``Processador`` no té constructor per defecte, i per tant la
única forma de construir un objecte ``Processador`` és utilitzar el
constructor de què disposem, obligatòriament amb 1 paràmetre (com es
comenta més amunt).

Si la classe ``Ordinador`` té com a atribut un objecte de la
classe ``Processador``::

  class Ordinador {
    Processador _cpu;
    
  public:
    Ordinador(double velocitat);
  };

per força el constructor de ``Ordinador`` haurà de cridar al
constructor de ``Processador``, passant-li la ``velocitat``. Per fer
aquesta crida s'ha d'utilitzar una sintaxi especial. La implementació
del constructor de ``Ordinador`` serà::

  Ordinador::Ordinador(double velocitat)
    : _cpu(velocitat)  // cridem el constructor del Processador
  {
  }

La sintaxi consisteix en posar "``:``" i fer una crida al constructor
amb el nom de l'atribut i els paràmetres entre parèntesis. Si hi ha
més d'un atribut en aquesta situació, les diferents crides es separen
per comes. Per altra banda, donat que no hi ha més atributs en la
classe ``Ordinador``, l'únic que es fa és cridar al constructor de
``Processador``, i el cos de la funció queda buit.

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

.. problema::

   Implementa la classe ``Frase`` de forma que el següent programa
   funcioni perfectament com dóna a entendre::

      int main() {
        Frase f;
	f.afegeix_paraula("Ser");
	f.afegeix_paraula("o");
	f.afegeix_paraula("no");
	f.afegeix_paraula("ser");
	f.mostra(cout);
	cout << "La frase té " << f.num_paraules() << " paraules" <<  endl;
	
	string nom;
	cout << "El teu nom? ";
	cin >> nom;
	
	f.esborra();
	f.afegeix_paraula("Hola,");
	f.afegeix_paraula(nom);
	f.mostra(cout);
      }      


Bibliografia
============

Bjarne Stroustrup, *The C++ Programming Language*, Third
Edition. Addison-Wesley, 2004. Capítol 10, Classes.

`http://en.wikipedia.org/wiki/Class_(computer_science) <http://en.wikipedia.org/wiki/Class_(computer_science)>`_
