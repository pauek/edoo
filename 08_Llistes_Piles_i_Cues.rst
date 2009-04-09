
=====================
Llistes, Piles i Cues
=====================

Llistes
=======

llista
  Una llista és un contenidor que emmagatzema les dades formant una doble
  cadena de punters:

  .. image:: img/list.png
     :align: center
     :scale: 80

  Cada element té un punter a l'element següent i també a l'anterior,
  i la llista guarda un punter al primer element (el ``front``) i a
  l'últim (el ``back``). Per utilitzar la classe ``list`` és necessari
  fer un ``#include`` com::
   
    #include <list>

Iteradors ``const``
-------------------

Per assegurar la "constància" de les dades, les funcions que reben
contenidors ``const`` han de fer servir iteradors de tipus
``const_iterator``. Això succeeix en funcions que rebin contenidors
com a *paràmetres d'entrada*. Per exemple, la següent funció determina
quantes caselles d'un ``vector<bool>`` tenen el valor ``true``::

   int compta_certs(const vector<bool>& v) {
     int c = 0;
     vector<bool>::const_iterator i;
     for (i = v.begin(); i != v.end(); i++) {
       if (*i) c++;
     }
     return c;
   }

El contenidor que la funció rep com a paràmetre no es modifica, i per
això porta ``const``. Per poder iterar un contenidor ``const``, és
necessari fer servir un iterador especial, que és el
``const_iterator``.  L'únic canvi en el codi, respecte al codi vist
fins ara és la declaració de l'iterador::
 
   vector<bool>::const_iterator i;

.. exercici::
   
   Fes una funció que rebi un vector de reals i retorni la seva
   suma, fent servir iteradors.

Declaració de llistes
---------------------

Per declarar una llista, hem d'esciure el següent (el tipus ``T`` pot
ser qualsevol)::

   list<T> L;

L'object és ``L``, i el seu tipus és ``list<T>``. La llista contindrà
objectes del tipus ``T``. Per exemple, per tenir una llista de
``string``\s i una llista de ``bool``\s, faríem::

   list<string> ls;
   list<bool> lb;

Tal com en el cas dels vectors, si disposem d'una classe ``Racional``,
per tenir una llista de ``Racionals`` farem::

   list<Racional> lr;

La classe ``list<T>`` defineix els següents constructors:

.. list-table::
   :widths: 28, 55

   * - ``list<T>()``
     -  Constructor per defecte, crea la llista buida.

   * - ``list<T>(int size)``
     - Crea una llista amb un tamany ``size`` i cada element de la llista
       serà el resultat de cridar el constructor per defecte de la classe
       ``T`` (ha d'existir, per tant). Per exemple, per crear una llista de
       40 ``bool``\s, farem::

          list<bool> l1(40);


   * - ``list<T>(int size, const T& t)``
     - Crea una llista amb un tamany ``size`` i omple tots els elements
       fent servir ``t`` com a model (farà servir el constructor de còpia
       de la classe ``T``, per tant aquest ha d'existir). Per crear una
       llista de 5 paraules en què totes tinguin el valor ``"SFDK"``,
       farem::
         
	 list<string> paraules(5, "SFDK");

   * - ``list<T>(const list<T>& L)``
     - Constructor de còpia, crea una llista a partir d'una altra, copiant
       tots els elements.


.. exercici::
 
   Declara les següents llistes:

   - Una llista de 40 reals.
   - Una llista buida a on cada element és un ``Punt2D`` (fes la
     suposició que disposes d'aquesta classe).
   - Una llista de 100 caràcters plens del valor ``'X'``.
   - Una llista a on cada element sigui un vector d'enters.


Mètodes
-------

Mètodes consultors
''''''''''''''''''

Les llistes també tenen els mètodes consultors estàndar de contenidors
d'STL:

.. raw:: latex

   \vspace{-1.5mm}

.. list-table:: 
   :widths: 28, 55

   * - ``int size() const`` 
     - Per obtenir el tamany. Suposant que ``n`` és el tamany de la llista,
       aquesta funció té un cost O(``n``), és a dir, linial.

   * - ``bool empty() const``
     - Retorna ``true`` si la llista està buida. Aquesta funció té cost
       O(1), i és molt més eficient que escriure ``size() == 0``.

   * - ``const T& front() const``
     - Retorna una referència l'últim element.

   * - ``const T& back() const``
     - Retorna una referència al primer element.

Mètodes modificadors
''''''''''''''''''''

Com també els següents mètodes modificadors estàndar:

.. raw:: latex

   \vspace{-1.5mm}

.. list-table::
   :widths: 28, 55

   * - ``void clear()``
     - Esborra tots els elements de la llista.

   * - ``void resize(int n)``
     - Redimensiona la llista.

   * - ``void resize(int, const T& t)``
     - Redimensiona la llista, omplint els elements nous amb el valor
       ``t`` (si és necessari).

   * - ``void push_back(const T& t)``
     - Afegeix al final.

   * - ``void push_front(const T& t)`` 
     - Inserta al principi.

   * - ``void pop_back()`` 
     - Esborra un element del final.


Mètodes especials de ``list``
'''''''''''''''''''''''''''''

.. raw:: latex

   \vspace{-1.5mm}

.. list-table::
   :widths: 28, 55

   * - ``void pop_front()``
     - Esborra un element del principi, opera igual que ``pop_back`` però
       al principi de la llista (no existeix en vectors).

   * - ``void remove(const T& val)`` 
     - Esborra els elements de la llista que tinguin el valor ``val`` (fa
       servir el ``operator==``). Per exemple, si una llista ``L`` conté els
       elements 1, 2, 3, 4, i 5 en aquest ordre, si fem::

         L.remove(3);

       llavors la llista tindrà els elements 1, 2, 4 i 5.

   * - ``void reverse()``
     - Canvia d'ordre els elements d'una llista (eficiència O(``n``)). És a
       dir, si una llista conté (1, 2, 3), després d'haver cridat ``reverse``
       contindrà (3, 2, 1).


.. exercici::

   Digues quins elements conté la llista ``A`` al final del següent codi::

     list<int> A(10, -1);
     A.push_back(3);
     A.push_back(-3);
     for (int k = 0; k < 5; k++) A.pop_front();
     A.front() = 5;
     A.remove(-1);
     A.push_front(4);
     A.reverse();

.. exercici::

   Escriu codi per crear una llista buida i omple-la amb els elements
   (en aquest ordre exactament): 9, 7, 5, 3, 1, 2, 4, 6, 8, 10. Per
   fer-ho fes una iteració de 1 a 10 i inserta el elements parells al
   final i els imparells al principi.


Iteradors de llistes
--------------------

Els iteradors per a llistes són iguals que per a vectors (incloent els
iteradors ``const``): el concepte és el mateix, i la forma d'utilitzar
els iteradors també. Per obtenir un iterador a una llista simplement
hem de canviar el prefix en el tipus d'iterador. Per exemple, la
següent declaració és d'un iterador a una llista d'enters::

   list<int>::iterator i;

La similitud amb els iteradors dels vectors és notable (aquest és un
dels punts forts de la STL). La generalitat dels iteradors es veu
clara quan convertim una funció que itera un vector a una funció que
itera una llista. En la taula següent tenim la mateixa funció
implementada per a vectors (a l'esquerra) i per a llistes (a la
dreta):

.. raw:: latex
   
   \vspace{-1mm}

.. list-table::
   
   * - ::

        double vmitjana(const vector<double>& V) {
          double suma = 0.0;
          vector<double>::const_iterator i;
          for (i = V.begin(); i != V.end(); i++) {
            suma += *i;
          }
          return suma/double(V.size());
        }

     - ::

        double lmitjana(const list<double>& L) {
          double suma = 0.0;
          list<double>::const_iterator i;
          for (i = L.begin(); i != L.end(); i++) {
            suma += *i;
          }
          return suma/double(L.size());
        }

Ens hem limitat a *substituir a tot arreu* ``vector<double>`` per
``list<double>``. 

.. exercici::

   Fes una funció que rebi una llista de ``bool``\s i retorni ``true``
   només si tots els valors de la llista són ``false``.


Inserció i esborrat d'elements al mig
'''''''''''''''''''''''''''''''''''''

Les llistes permeten insertar elements al mig a través de mètodes
especials. Vegem aquests mètodes:

.. raw:: latex
   
   \vspace{1mm}

.. list-table::
   :widths: 45, 40

   * - ``void insert(iterator pos, const T& t)``
     - Inserta el valor ``t`` *abans* de l'element apuntat per l'iterador
       ``pos``.

   * - ``void insert(iterator pos, int n, const T& t)``
     - Inserta ``n`` vegades el valor ``t`` *abans* de l'element apuntat
       per l'iterador ``pos``.

   * - ``iterator erase(iterator pos)``
     - Esborra l'element apuntat per ``pos`` i retorna un iterador a
       l'element següent (ja que si s'esborra l'element al que apuntava
       l'iterador aquest ja no serà vàlid).

   * - ``iterator erase(iterator first, iterator last)``
     - Esborra els elements entre els iteradors ``first`` i ``last``
       incloent l'element al que apuntava ``first`` però *no* l'element al
       que apuntava ``last``. Això se simbolitza amb ``[first, last)``. El
       valor retornat és ``last`` (un iterador al primer element vàlid).

Exemple d'esborrat d'elements
'''''''''''''''''''''''''''''

L'ús típic del mètode ``erase`` és el següent: per fer un recorregut per una
llista de paraules ``par`` i anar esborrant les que tenen una longitud
menor que 5::

  list<string>::iterator i = par.begin();
  while (i != par.end()) {
    if ((*i).size() < 5) {
      i = par.erase(i);
    }
    else i++;
  }    

És important veure que *no* s'incrementa l'iterador ``i`` quan
esborrem una paraula ja que el valor que retorna ``erase`` és el de
l'element següent i per tant assignar el valor retornat a ``i`` ens
permet continuar la iteració.

.. exercici::

   Fes una funció que, donada una llista d'enters ``L`` ordenada de
   forma creixent i un enter ``k``, inserti ``k`` a ``L`` de forma que
   la llista segueixi estant ordenada. Busca primer la posició a on ha
   d'anar ``k`` amb una iteració i després fes servir ``insert``.

.. exercici:: 

   Fes una funció que rebi una llista de punts bidimensionals
   (``Punt2D``) i esborri aquells que estiguin fora del cercle unitat
   (amb distància a l'origen major que 1). Fes la suposició la classe
   ``Punt2D`` té una declaració com la següent::

     class Punt2D {
       // ...
     public:
       Punt2D(float x, float y);
       float dist() const;        // distància a l'origen.
     };

Eficiència de les operacions sobre llistes
------------------------------------------

Les operacions sobre llistes tenen les següents eficiències,
comparades amb el vector:

.. csv-table:: 
   :header: "Operació", "``list``", "``vector``"
   :widths: 30, 5, 5
   
   "Accedir al primer element", "O(1)", "O(1)"
   "Accedir a l'últim element", "O(1)", "O(1)"
   "Accedir a un element intermig", "O(n)", "O(1)"
   "Inserir/Esborrar al principi", "O(1)", "O(n)"
   "Inserir/Esborrar al final", "O(1)", "O(1)"
   "Inserir/Esborrar al mig", "O(1)", "O(n)"

El punt fort de les llistes, doncs, és la inserció i esborrat, en les
que el vector és molt més ineficient, ja que per mantenir l'estructura
ordenada en memòria, el vector ha de moure els elements quan
insertem. Per contrapartida, accedir a elements intermitjos en una
llista és ineficient, ja que s'ha de resseguir tota la cadena
d'elements per arribar a un cert element, quan amb el vector és tan
senzill com fer servir un índex.


Piles
=====

adaptadors
   Alguns contenidors de la STL s'implementen a partir d'altres. És a
   dir, defineixen mètodes nous però fan servir les operacions
   d'altres contenidors per treballar.

pila 
   *Stack* en anglès. Estructura de dades *Last In First Out*, o LIFO
   (l'últim que va entrar és el primer que surt). Si imaginem les
   piles com estructures verticals (que és la forma que adopten les
   piles d'objectes físics, com ara plats), podem interpretar que
   l'element que ha entrat l'últim està a dalt de tot (el *top*).


Per fer servir piles hem de fer l'``include`` corresponent::

   #include <stack>

Per declarar una pila es fa com amb els altres contenidors de la STL::

   stack<int> S;

que declara una pila d'enters buida. 

Operacions amb piles
--------------------

Les piles són estructures molt bàsiques, només tenen 3 operacions
principals:

- **apilar**, *push* en anglès, que posa un element al damunt de tot
  de la pila. 

- **desapilar**, *pop* en angès, que treu l'element de dalt de tot (i
  deixa al descobert el següent).

- **consultar** el primer, per obtenir el *top*, l'element de dalt de tot, sense
  treure'l de la pila.

Aquestes operacions típiques tenen 3 mètodes especials


Mètodes de la classe ``stack``
------------------------------

Constructors:

.. raw:: latex

   \vspace{-1.5mm}

.. list-table:: 
   :widths: 28, 55

   * - ``stack<T>()`` 
     - Crea una pila buida.

   * - ``stack<T>(const stack<T>& s)``
     - Crea una pila a partir d'una altra.

Els mètodes de la classe ``stack`` són els següents:

.. raw:: latex

   \vspace{-2.5mm}

.. list-table:: 
   :widths: 28, 55

   * - ``int size() const`` 
     - Per obtenir el tamany.

   * - ``bool empty() const``
     - Per saber si la pila està buida. 

   * - ``T& top()``
     - Retorna una referència a l'element de dalt de tot.

   * - ``void push(const T& t)``
     - Apila un element a dalt de tot.

   * - ``void pop()``
     - Elimina l'elemnt de dalt de tot.

.. exercici::

   Què mostra per pantalla el següent codi?
   ::
     
      stack<char> S;
      S.push('l'); S.push('e'); S.push('a');
      S.push('r'); S.push('z'); S.push('A');
      while (!S.empty()) {
        cout << S.top();
	S.pop();
      }

.. exercici::
   
   Fes una acció ``opera`` que rebi una pila d'enters i un caracter
   (que podrà ser només un de ``'+'``, ``'-'``, ``'*'`` i ``'/'``), i
   tregui els 2 valors superiors de la pila, realitzi la operació que
   indica el caracter, i posi el resultat a la pila. En el cas
   de la resta, si el *top* és ``a`` i el de sota ``b``, la resta ha
   de fer ``b - a`` (i semblant amb la divisió).

.. exercici::

   Imagina un programa que fa servir una pila d'enters i rep una
   seqüència d'enters i operacions. Quan rep un enter, l'apila, i quan
   rep una operació, tal com amb l'acció de l'exercici anterior,
   realitza la operació amb els 2 enters de dalt de la pila. Si el
   programa rep "``3 2 +``" deixarà un 5 a la pila. Si rep ``1 1 + 2
   *`` deixarà un 4. Calcula el resultat de les seqüències següents:

   - ``3 3 3 + *``
   - ``3 4 5 1 * + -``
   - ``1 2 + 3 -``
   - ``5 4 * 100 + 2 3 * 10 * -``

   Escriu aquestes expressions de la forma habitual (amb
   parèntesis). Per exemple, la seqüència ``1 1 + 2 *`` seria ((1 +
   1) * 2). La notació amb forma de seqüència s'anomena postfixa o
   polaca (algunes calculadores la fan servir).

.. exercici::
   
   L'acció següent intenta convertir un ``string`` en un enter i si
   pot, retorna ``true`` i fa servir el paràmetre ``val`` per retornar
   el resultat. Si no pot, retorna ``false``. Per fer-la servir és
   necessari fer un ``include`` especial: ``#include <sstream>``.
   ::

      bool es_enter(string s, int& val) {
        istringstream sin(s);
        sin >> val;
        return !sin.fail();
      }

   Amb l'ajuda, doncs, de l'acció ``es_enter`` i l'acció ``opera`` de
   l'exercici anterior, fes un programa que rebi una seqüència de
   paraules (acabada en ``"."``) que poden ser interpretats com enters
   o operadors, en notació polaca. Un exemple de seqüència seria::

      3 2 1 + * .
      
   El programa he de tenir una pila d'enters, i ha de llegir la
   seqüència com si fós de ``string``\s. Donat un element, si aquest
   representa un enter s'ha d'apilar, i si no s'ha de cridar a
   ``opera`` amb el caracter corresponent (podem suposar que la
   seqüència només conté les 4 operacions amb enters). Un cop rebut
   l'últim element (el ``"."``), s'ha de mostrar el *top* de la pila
   per pantalla.
  
Cues
====

cua
   *Queue* en anglès. Estructura de dades *First In First Out*, o FIFO
   (el primer que va entrar és el primer que surt).

Per fer servir cues hem de fer l'``include`` corresponent::

   #include <queue>

Per declarar una cua es fa com amb els altres contenidors de la STL::

   queue<int> S;

que declara una cua d'enters buida.

Operacions amb cues
-------------------

Les cues són estructures també molt bàsiques, i com les piles, només
tenen 3 operacions principals:

- **posar** (també *push*), que inserta un element al final de
  la cua.

- **treure** (també *pop*), que treu l'element del principi de la cua
  (el *front*).

- **consultar** el primer, per obtenir el *front*, el primer element.


Mètodes de la classe ``queue``
------------------------------

Constructors:

.. raw:: latex

   \vspace{-1.5mm}

.. list-table:: 
   :widths: 28, 55

   * - ``queue<T>()`` 
     - Crea una cua buida.

   * - ``queue<T>(const queue<T>& s)``
     - Crea una cua a partir d'una altra.

Altre mètodes:

.. raw:: latex

   \vspace{-2.5mm}

.. list-table:: 
   :widths: 28, 55

   * - ``int size() const`` 
     - Per obtenir el tamany.

   * - ``bool empty() const``
     - Per saber si la cua està buida. 

   * - ``T& front()``
     - Retorna una referència al primer element.

   * - ``T& back()``
     - Retorna una referència a l'últim element.

   * - ``void push(const T& t)``
     - Inserta un element al final de la cua.

   * - ``void pop()``
     - Elimina el primer element.

.. exercici::

   Determina el que mostrarà el següent codi per pantalla::

     queue<int> Q;
     for (int k = 3; k < 9; k++) Q.push(k);
     int& f = Q.front();
     f = 5;
     int& b = Q.back();
     b = 11;
     while (!Q.empty()) {
       cout << Q.front() << ' ';
       Q.pop();
     }
     
Problemes
---------

.. problema::

   Fes un programa que llegeix una seqüència de matrícules de cotxe
   d'un fitxer ``matricules.txt`` i mostri la seqüència al revés. Les
   matrícules tenen un enter i 3 lletres, com per exemple ``3451 JKK``.
