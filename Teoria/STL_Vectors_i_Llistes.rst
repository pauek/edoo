
.. tema:: vl

======================
Vectors i Llistes
======================

.. contents:: Contingut 
   :depth: 2
   :local:


Contenidor
  Tipus abstracte de dades que conté a dins una col·lecció d'objectes
  i que ens permet afegir, esborrar i accedir als elements. Els
  diversos tipus de contenidors que hi ha (llistes, vectors, taules
  associatives, conjunts) tenen propietats diferents en quant a
  l'**eficiència** d'aquestes operacions bàsiques.

STL
  La *Standard Template Library* és una llibreria de "plantilles"
  (en anglès, *templates*) que permet crear contenidors per a objectes
  de qualsevol classe que nosaltres haguem implementat (incloent els
  tipus bàsics de C++). Els contenidors que estudiarem són, per a una
  classe ``T`` i ``K`` qualssevol:

  - ``vector<T>``, una taula de tamany variable.
  - ``list<T>``, una llista doblement enllaçada.
  - ``stack<T>`` i ``queue<T>``, una pila i una cua.
  - ``set<T>``, un conjunt.
  - ``map<K,T>``, una taula associativa.

  La STL té tots aquests contenidors i també:

  - Tots els contenidors implementen: el constructor de còpia i
    l'operador d'assignació (``operator=``).

  - Un conjunt d'*iteradors*, que permeten recórrer els contenidors de
    forma genèrica.

  - Un conjunt d'*algorismes genèrics* típics per a contenidors
    (ordenació, cerca, comptatge, etc.).

  La documentació central sobre la STL es pot trobar a
  `http://www.sgi.com/tech/stl/ <http://www.sgi.com/tech/stl/>`_.


Vectors
=======

vector (classe ``vector``)
  Un vector és una versió millorada de les taules ordinàries de
  C++. En particular, és una classe que implementa una *taula de
  tamany variable*, i que sobrecarrega l'``operator[]``, per poder
  accedir a les caselles tal com s'ha fet fins ara amb les taules. 

Declaració de vectors
---------------------

La classe ``vector`` està declarada en el fitxer de capçalera del
mateix nom. Per poder-la fer servir hem de posar::

  #include <vector>

Donat que la classe pertany al ``namespace std``, també caldrà
afegir::

  using namespace std;

tot i que això ja ho hem de posar habitualment si fem servir ``cin``
o ``cout``.

Per declarar un objecte de tipus ``vector``, hem d'esciure el següent
(el tipus ``T`` pot ser qualsevol)::
  
   vector<T> v;

L'objecte és ``v``, i el seu tipus és ``vector<T>``. El vector
contindrà objectes del tipus ``T``. Per exemple, per tenir un vector
d'enters i un vector de reals faríem::

   vector<int> vi;
   vector<float> vf;

Si disposem d'una classe ``Complex`` de nombres complexos, per crear
un vector de nombres complexos farem::

   vector<Complex> vc;

La idea és que, a dins dels angles (``<`` i ``>``) hi va el tipus dels
objectes que el vector contindrà (tots els contenidors de la STL
segueixen aquest patró). Donat que aquestes declaracions criden als
constructors de la classe vector, cal dir de quins constructors
disposem:

.. cpp:function:: vector<T>()
     
   Constructor per defecte, crea el vector buit.


.. cpp:function:: vector<T>(int size)
 
   Constructor amb un tamany (``size``), crea el vector amb un tamany
   concret que especifiquem nosaltres. És necessari que el tipus ``T``
   *tingui constructor per defecte*. Per exemple, si volem crear un
   vector de 20 enters farem::
 
     vector<int> v1(20);
    

.. cpp:function:: vector<T>(int size, const T& t)
 
   Constructor que rep un paràmetre de tamany i un element amb què omplir
   el vector. Si volem un vector de 50 caràcters amb una ``'z'`` a cada casella,
   farem::

     vector<char> lletres(50, 'z');


.. cpp:function:: vector<T>(const vector<T>& v)

   Constructor de còpia.
  

.. exercici::
   
   Declara els següents vectors:
  
   - Un vector de 50 enters.
   - Un vector de dates, suposant que existeix la classe ``Data``.
   - Un vector de 10 reals, cadascún amb el valor inicial 1.0.
   - Un vector de 100 nombres complexos (classe ``Complex``), amb el
     valor inicial (1.0, 0.0).
   - Un vector de 10 ``bool``\s. Suposa que tens un altre vector com
     aquest que es diu ``vb`` i fes-ne una còpia.

   .. solucio::

      ::
      
         vector<int> I(50);
         vector<Data> D;
         vector<float> R(10, 1.0);
         Complex c(1.0, 0.0);
         vector<Complex> vc(100, c);
         vector<bool> B(vb);

      El vector de ``Complex`` també es podria haver declarat així::
      
         vector<Complex> vc(100, Complex(1.0, 0.0));

      sense necessitat d'haver de declarar una variable ``c`` de tipus
      ``Complex``.
      

Accés a les caselles d'un vector
""""""""""""""""""""""""""""""""

Per accedir a les caselles d'un vector, es fa tal com amb les taules
normals de C++, fent servir els corxets '``[``\' i '``]``\'. Per exemple, el
següent codi, crea un vector de caràcters i l'omple amb les lletres
minúscules::

   vector<char> minusc(26);
   for (int k = 0; k < 26; k++) {
     minusc[k] = char(97 + k);
   }

.. exercici::
   
   Fes una acció que ompli un vector d'enters de la següent manera: si
   el tamany del vector és *N*, l'ha d'omplir amb N, N-1, N-2,
   etc. fins a l'1.

   .. solucio::
      ::

         void omple_descendent(vector<int>& v) {
           for (int i = 0; i < v.size(); i++) {
             v[i] = v.size() - i;
           }
         }

Mètodes consultors
------------------

Els mètodes consultors disponibles per a ``vector`` són:

.. cpp:function:: int vector<T>::size() const

   Retorna el tamany del vector.


.. cpp:function:: bool vector<T>::empty() const 

   Retorna ``true`` si el vector està buit.


.. cpp:function:: const T& vector<T>::front() const

   Retorna una referència al primer element del vector.


.. cpp:function:: const T& vector<T>::back() const
  
   Retorna una referència a l'últim element del vector.


.. exemple::
   
   Fes una acció que rep un vector d'enters i els mostra per
   pantalla. El format serà el següent:

   - Si el vector és buit, s'ha d'escriure::
   
       []

   - Si el vector té un element::
   
       [1]


   - Si el vector té més d'un element, s'han de separar per comes::

       [5, 1, 2, 4]

   .. solucio::

      Per fer aquest exercici cal recórrer amb un ``for`` el vector com
      una taula i per saber el tamany del vector podem fer servir el
      mètode ``size``. Una versió preliminar (que no respecta el
      format demanat) seria::

         void mostra_vector(const vector<int>& v) {
           for (int i = 0; i < v.size(); i++) {
             cout << v[i] << ' ';
           }
         }

      Ara, ens podem preocupar de posar els corxets i les comes. El
      truc és escriure primer l'element inicial i fer una iteració *a
      partir del segon element*::

        void mostra_vector(const vector<int>& v) {
           cout << '[';
           cout << v[0];
           for (int i = 1; i < v.size(); i++) {
             cout << ", " << v[i];
           }
           cout << ']';
        }

      El problema és que si el vector és buit, llavors el programa no
      funcionarà correctament, ja que accedir a la casella 0 és un
      error si aquesta no existeix (i no hi és en un vector buit). Per
      arreglar-ho comprovem primer si el vector és buit::
   
        void mostra_vector(const vector<int>& v) {
          cout << '[';
          if (!v.empty()) {
            cout << v[0];
            for (int i = 1; i < v.size(); i++) {
              cout << ", " << v[i];
            }
          }
          cout << ']';
        }


.. exercici::
 
   Fes una funció que rebi un vector d'enters per referència i calculi
   la suma dels seus elements. Si el vector està buit, s'ha de
   retornar -1.

   .. solucio::
      ::
   
        int vector_suma(const vector<int>& v) {
          if (v.empty()) return -1;
          int suma = 0, k;
          for (k = 0; k < v.size(); k++) {
            suma += v[k];
          }
          return suma;
        }
   

.. exercici::

   Fes una funció que rebi un vector de reals i retorni la mitjana
   entre el primer i l'últim element. Si el vector està buit s'ha de
   retornar -1.0.

   .. que pasa si el vector tiene 1 elemento?

   .. solucio::
      ::
   
         float mitjana_1_n(const vector<float>& v) {	
	   if (v.empty()) {
	     return -1.0;
           } else {
             return (v.front() + v.back()) / 2.0;
           }
         }


Mètodes modificadors
--------------------

.. cpp:function:: void vector<T>::resize(int n)

   Redimensiona el vector perquè tingui tamany ``n``.

.. cpp:function:: void vector<T>::resize(int n, const T& t)

   Redimensiona el vector perquè tingui tamany ``n`` i si és necessari
   fer-lo més gran, omple les noves caselles amb ``t``.

.. cpp:function:: void vector<T>::push_back(const T& t)

   Afegeix l'element ``t`` al final del vector (i per tant allarga
   el vector en 1 unitat).

.. cpp:function:: void vector<T>::pop_back()

   Esborra l'últim element del vector (no el retorna), i per tant
   escurça el vector en 1 unitat).

.. cpp:function:: void vector<T>::clear()

   Esborra tots els elements del vector.


.. exercici::

   Declara un vector de caràcters buit i omple'l amb les lletres
   minúscules fent servir ``push_back``.

   .. solucio::
      ::

         vector<char> v;
         for (k = 0; k < 26; k++) {
           v.push_back(char(97 + k));
         }
   

Eficiència de les operacions sobre ``vector``
"""""""""""""""""""""""""""""""""""""""""""""

Els vectors es caracteritzen per tenir un temps d'accés ràpid
(independent del tamany), però els temps d'inserció és gran. Suposant
que el tamany d'un vector és "n", el cost de les operacions sobre un
vector és:

=============================== ============
Operació                        ``vector``
=============================== ============
Accedir al primer element       :math:`O(1)`
Accedir a l'últim element       :math:`O(1)`
Accedir a un element intermig   :math:`O(1)`
Inserir/Esborrar al principi    :math:`O(n)`
Inserir/Esborrar al final       :math:`O(1)`
Inserir/Esborrar al mig         :math:`O(n)`
=============================== ============

.. exercici
.. Quin algorisme omple el vector més ràpidament, l'exercici 2 o el 6?
.. Ya no funciona   


Iteradors
---------

La STL proporciona un mètode per recórrer contenidors (i entre ells, els
vectors) que permet passar per tots els elements del vector de la forma més
ràpida possible (encara més ràpid que fent servir un índex). Per
fer-ho, es necessita crear un *iterador*.

iterador
  En la STL, un iterador és una abstracció d'un "punter". Un iterador
  és una variable que emmagatzema una *posició* dins d'un contenidor.

Per declarar iteradors, es fa servir la següent sintaxi::

   vector<T>::iterator i;

Això declara un iterador per a vectors amb elements de tipus ``T``. És
important veure que cada vector (en funció del tipus ``T``) té el seu
propi iterador.

.. exercici::

   Declara els següents iteradors:

   - Un iterador a un vector de reals.
   - Un iterador a un vector de dates (la classe ``Data``).

   .. solucio::
      ::

         vector<double>::iterator i;
         vector<Data>::iterator j;
  

Donat un iterador, per tal que apunti a una posició del vector
concreta, tenim els següents mètodes:

.. cpp:function:: vector<T>::iterator begin()
  
   Retorna un iterador a la primera posició del vector.

.. cpp:function:: vector<T>::iterator end()

   Retorna un iterador a la posició *immediatament posterior a la última*
   del vector.

El final d'un vector (el valor de ``end()``) és una posició especial
del vector ja que no conté cap valor (està fora del vector), però
serveix per marcar el final (tal com un sentinella).

.. exercici::

   Per a un vector d'enters ``vi``, declara un iterador ``i`` i
   inicialitza'l perquè apunti al principi i un altre ``iend`` perquè
   apunti al final.

   .. solucio::
      ::
 
         vector<int>::iterator i, iend;
         i = vi.begin();
         iend = vi.end();
   

Recorreguts amb iteradors
"""""""""""""""""""""""""

Els iteradors es fan servir tal com els punters. Per moure'ls, es fa
servir la suma (o l'operador ``++``), i per accedir al contingut de la
casella a la que apunten, es fa servir l'operador ``*``. Per exemple,
el següent codi defineix una funció que calcula la mitjana dels valors
d'un vector de reals::

  double mitjana(vector<double>& v) {
    double suma = 0.0;
    vector<double>::iterator i;
    for(i = v.begin(); i != v.end(); i++) {
      suma = suma + *i;
    }
    return suma / double(v.size());
  } 

Hi ha dos detalls importants. Per una banda, quan escrivim ``*i``,
accedim a la casella a la que apunta l'iterador i per tant, accedim a
un valor de tipus ``double``, ja que el vector és de reals. Per altra
banda, el final de la iteració es comprova amb ``i != v.end()``, ja
que la comparació d'iteradors (és a dir, si féssim ``i < v.end()``) no
està definida en general.

.. exercici::
  
   Fes una funció que ompli un vector d'enters amb la seqüència
   1,2,1,2,1,etc. fent servir iteradors.

   .. solucio::
      ::

         void omple_1_2(vector<int>& v) {
           vector<int>::iterator i;
           bool b = true;
           for (i = v.begin(); i != v.end(); i++) {
             if (b) { *i = 1; b = false; }
             else   { *i = 2; b = true; }
           }
         }
      

.. exercici::
  
   Fes una funció que cerqui un valor ``true`` en un vector de
   ``bool``\s, i retorni cert si l'ha trobat i fals si no.

   .. solucio::

      En aquest exercici s'hauria de fer servir la clàusula ``const`` en
      el vector però degut a què això implica fer servir un iterador
      constant i això encara no s'ha vist, es passa el vector per
      referència directament.
      ::
  
         bool cerca_true(vector<bool>& v) {
           vector<bool>::iterator i;
           bool trobat = false;
           while (i != v.end() && !trobat) {
             if (*i) trobat = true;
             else i++;
           }
           return trobat;
         }

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

   .. solucio::

      Aquest exercici requerirà l'ús d'un iterador ``const``.
      ::

        float suma_vector(const vector<float>& v) {
          float suma = 0.0;
          vector<float>::const_iterator i;	 
          for (i = v.begin(); i != v.end(); i++) {
 	    suma += *i;
          }
          return suma;
        }

      Només cal recordar de fer servir iteradors ``const`` amb paràmetres
      d'entrada (que portin ``const`` i ``&``).


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

.. cpp:function::  list<T>()

   Constructor per defecte, crea la llista buida.

.. cpp:function:: list<T>(int size)

   Crea una llista amb un tamany ``size`` i cada element de la llista
   serà el resultat de cridar el constructor per defecte de la classe
   ``T`` (ha d'existir, per tant). Per exemple, per crear una llista
   de 40 ``bool``\s, farem::

     list<bool> l1(40);


.. cpp:function:: list<T>(int size, const T& t)

   Crea una llista amb un tamany ``size`` i omple tots els elements
   fent servir ``t`` com a model (farà servir el constructor de còpia
   de la classe ``T``, per tant aquest ha d'existir). Per crear una
   llista de 5 paraules en què totes tinguin el valor ``"SFDK"``,
   farem::
         
     list<string> paraules(5, "SFDK");

.. cpp:function:: list<T>(const list<T>& L)

   Constructor de còpia, crea una llista a partir d'una altra, copiant
   tots els elements.


.. exercici::
 
   Declara les següents llistes:

   - Una llista de 40 reals.
   - Una llista buida a on cada element és un ``Punt2D`` (fes la
     suposició que disposes d'aquesta classe).
   - Una llista de 100 caràcters plens del valor ``'X'``.
   - Una llista a on cada element sigui un vector d'enters.

   .. solucio::

      Declaracions de llistes::

         list<float> l(40);
         list<Punt2D> lpunts;
         list<char> lch(100, 'X');
         list< vector<int> > lv;

      En la última declaració, és important deixar un espai entre l'últim
      '``>``\' i el penúltim, ja que si no, el compilador pensa que fem
      servir l'operador '``>>``\'[6~.


Mètodes
-------

Mètodes consultors
""""""""""""""""""

Les llistes també tenen els mètodes consultors estàndar de contenidors
d'STL:

.. cpp:function:: int list<T>::size() const
   
   Per obtenir el tamany. Suposant que :math:`n` és el tamany de la
   llista, aquesta funció té un cost :math:`O(n)`, és a dir, linial.


.. cpp:function:: bool list<T>::empty() const
   
   Retorna ``true`` si la llista està buida. Aquesta funció té cost
   O(1), i és molt més eficient que escriure ``size() == 0``.


.. cpp:function:: const T& list<T>::front() const

   Retorna una referència l'últim element.


.. cpp:function:: const T& list<T>::back() const

   Retorna una referència al primer element.

Mètodes modificadors
""""""""""""""""""""

Com també els següents mètodes modificadors estàndar:


.. cpp:function:: void list<T>::clear()
   
   Esborra tots els elements de la llista.


.. cpp:function:: void list<T>::resize(int n)
   
   Redimensiona la llista.


.. cpp:function:: void list<T>::resize(int, const T& t)
   
   Redimensiona la llista, omplint els elements nous amb el valor
   ``t`` (si és necessari).


.. cpp:function:: void list<T>::push_back(const T& t)
   
   Afegeix al final.


.. cpp:function:: void list<T>::pop_back()
   
   Esborra un element del final.

.. exercici::
   
   Fes una acció que rebi una llista d'enters per referència,
   n'esborri tots els elements i l'ompli amb els nombres 500, 499,
   498, ..., 2 i 1 fent servir ``push_front``. 

   .. solucio::
      ::

         void omple_llista(list<int>& L) {
           L.clear();
           for (int k = 0; k < 500; k++) {
             L.push_front(k);
           }
         }
   

Mètodes especials de ``list``
"""""""""""""""""""""""""""""

.. cpp:function:: void list<T>::push_front(const T& t)
   
   Inserta un element igual que ``t`` al principi. El tamany de la
   llista creix en una unitat.

.. cpp:function:: void list<T>::pop_front()
   
   Esborra el primer element. El tamany de la llista decreix en una
   unitat.


.. cpp:function:: void list<T>::remove(const T& val)
   
   Esborra els elements de la llista que tinguin el valor ``val`` (fa
   servir el ``operator==``). Per exemple, si una llista ``L`` conté
   els elements 1, 2, 3, 4, i 5 en aquest ordre, si fem::

     L.remove(3);

   llavors la llista tindrà els elements 1, 2, 4 i 5.


.. cpp:function:: void list<T>::reverse()
   
   Canvia d'ordre els elements d'una llista (eficiència :math:`O(n)`). És
   a dir, si una llista conté (1, 2, 3), després d'haver cridat
   ``reverse`` contindrà (3, 2, 1).

.. cpp:function:: void list<T>::unique()

   Elimina els elements de la llista que estiguin repetits
   consecutivament. Si la llista conté (1, 1, 2, 2, 2, 3, 3, 1, 1, 1,
   2, 2, 2), després d'haver cridat ``unique`` contindrà (1, 2, 3, 1,
   2). Aquest mètode requereix l'operador "``==``" de la classe ``T``.

.. cpp:function:: void list<T>::sort()

   Ordena els elements de la llista de forma ascendent. Aquest mètode
   requereix l'operador "``<``" de la classe ``T``.


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

   .. solucio::

      La llista conté {-3, 3, 5, 4}.

      

.. exercici::

   Escriu codi per crear una llista buida i omple-la amb els elements
   (en aquest ordre exactament): 9, 7, 5, 3, 1, 2, 4, 6, 8, 10. Per
   fer-ho fes una iteració de 1 a 10 i inserta el elements parells al
   final i els imparells al principi.

   .. solucio::

      ::

        list<int> l;
        for (int k = 1; k <= 10; k++) {
          if (k % 2 == 0) {
            l.push_back(k);
          } else {
            l.push_front(k);
          }
        }
   


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

   .. exercici::

      En aquest exercici també és important fer servir iteradors ``const``.
      ::
     
         bool tots_false(const vector<bool>& B) {
           vector<bool>::const_iterator i = B.begin();
           bool tots_false = true;
           while (i != B.end() && tots_false) {
             if (*i) tots_false = false;
             else i++;
           }
           return tots_false;
         }
      
      És un esquema de cerca en el que si veiem una casella del vector a
      ``true``, ja podem retornar el resultat (que *no* tots els valors
      són false).
   


Inserció i esborrat d'elements al mig
"""""""""""""""""""""""""""""""""""""

Les llistes permeten insertar elements al mig a través de mètodes
especials. Vegem aquests mètodes:

.. cpp:function:: void list<T>::insert(iterator pos, const T& t)
   
   Inserta el valor ``t`` *abans* de l'element apuntat per l'iterador
   ``pos``.

.. cpp:function:: void list<T>::insert(iterator pos, int n, const T& t)
   
   Inserta ``n`` vegades el valor ``t`` *abans* de l'element apuntat
   per l'iterador ``pos``.

.. cpp:function:: iterator list<T>::erase(iterator pos)
   
   Esborra l'element apuntat per ``pos`` i retorna un iterador a
   l'element següent (ja que si s'esborra l'element al que apuntava
   l'iterador aquest ja no serà vàlid).

.. cpp:function:: iterator list<T>::erase(iterator first, iterator last)
   
   Esborra els elements entre els iteradors ``first`` i ``last``
   incloent l'element al que apuntava ``first`` però *no* l'element al
   que apuntava ``last``. Això se simbolitza amb ``[first, last)``. El
   valor retornat és ``last`` (un iterador al primer element vàlid).


Exemple d'esborrat d'elements
"""""""""""""""""""""""""""""

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

   .. solucio::

      ::

        void inserta_ordenat(list<int>& L, int k) {
          list<int>::iterator i = L.begin();
     
          // Trobem la posició o potser 'end'
          while (i != L.end() && *i > k) i++;
          
          // Ara insertem
          L.insert(i, k);     
        }

      Una cosa *important*:

      - L'expressió "``*i > k && i != L.end()``" (al revés que en la
        solució) no funciona correctament ja que si ``i`` es troba al
        final (a ``L.end()``), llavors farem ``*i`` i resulta que el
        sentinella dels contenidors (``end()``) no és cap element i el
        programa segurament donarà un error d'execució (abortarà
        abruptament). L'expressió ha d'estar en l'ordre que es mostra a
        dalt, en què primer es comprova si ``i`` està al final, i si no
        és així es mira l'element al que apunta (sense perill).
   

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

   .. solucio::

      Aquí farem servir ``erase`` amb la idea de no incrementar
      l'iterador quan esborrem ja que s'incrementa implícitament si
      el col·loquem al valor que retorna ``erase``.
      ::

        void esborra_fora_cercle(list<Punt2D>& L) {
          list<Punt2D>::iterator i = L.begin();
          while (i != L.end()) {
            if (i->dist() > 1.0) {
              i = L.erase(i);
            }
            else i++;
          }
        }
   

Eficiència de les operacions sobre llistes
------------------------------------------

Les operacions sobre llistes tenen les següents eficiències,
comparades amb el vector:

=============================== ============ ============
Operació                        ``vector``   ``list``  
=============================== ============ ============
Accedir al primer element       :math:`O(1)` :math:`O(1)`
Accedir a l'últim element       :math:`O(1)` :math:`O(1)`
Accedir a un element intermig   :math:`O(1)` :math:`O(n)`
Inserir/Esborrar al principi    :math:`O(n)` :math:`O(1)`
Inserir/Esborrar al final       :math:`O(1)` :math:`O(1)`
Inserir/Esborrar al mig         :math:`O(n)` :math:`O(1)`
=============================== ============ ============

El punt fort de les llistes, doncs, és la inserció i esborrat, en les
que el vector és molt més ineficient, ja que per mantenir l'estructura
ordenada en memòria, el vector ha de moure els elements quan
insertem. Per contrapartida, accedir a elements intermitjos en una
llista és ineficient, ja que s'ha de resseguir tota la cadena
d'elements per arribar a un cert element, quan amb el vector és tan
senzill com fer servir un índex.

Problemes
=========

En els següents problemes es demana fer funcions i accions i en cap
cas es diu explícitament els paràmetres ni la capçalera d'aquestes
funcions. Forma part dels problemes pensar les conseqüències de
retornar vectors o passar-los per referència, etc.

.. problema::
   
   Fes una funció que concatena 2 vectors. Per exemple, si els vectors
   són [1, 2, 3] i [4, 5, 6], el resultat és un vector 
   [1, 2, 3, 4, 5, 6].

   .. solucio::

      En aquest exercici, es rebràn 2 paràmetres d'entrada (els dos
      vectors a concatenar) i s'ha de retornar un vector, però en comptes
      de fer una funció, farem una acció, per tal de no haver de copiar
      el vector resultat (que és el que passaria si el retornem tal
      qual).
      ::

  	void concatena(const vector<int>& a, const vector<int>& b,
	     	       vector<int>& res) {
	  res.resize(a.size() + b.size());
	  vector<int>::const_iterator i = a.begin(), ir = res.begin();
	  while (i != a.end()) {
	    *ir = *i;
	    ++ir; ++i;
	  }
	  i = b.begin();
	  while (i != b.end()) {
	    *ir = *i;
	    ++ir; ++i;
	  }
        }
      

.. problema::

   Fes una funció que sumi dos vectors de reals casella a casella. Per
   exemple, si els vectors són [1, 2, 3] i [4, 5, 6], el
   resultat és [5, 7, 9]. La funció no ha de fer res si els
   vectors no tenen el mateix tamany.

   .. solucio::
      En aquest exercici ens passa com l'anterior respecte al tema dels
      paràmetres.
      ::

	void suma(const vector<float>& a, const vector<float>& b,
	          vector<float>& res) {
	  if (a.size() != b.size()) return;
  	  res.resize(a.size());
	  vector<float>::const_iterator i = a.begin(), j = b.begin();
	  vector<float>::iterator k = res.begin();
	  while (i != a.end()) {
	    *k = *i + *j;
  	    ++k; ++i; ++j;
	  }
	}

      Dos comentaris:
   
      - En una acció, per abandonar l'execució en qualsevol moment, es
        pot fer servir ``return`` sense posar cap valor al costat (o
        sigui, directament posant un '``;``\' al costat). Això es fa
        servir al principi per abandonar la acció si ``a`` i ``b`` no
        tenen el mateix tamany.

      - Al principi, la instrucció ``res.resize(a.size())`` redimensiona
        el vector al tamany final (que és igual que ``b.size()``, perquè
        si no hauriem abandonat l'acció abans.


.. problema::

   Fes una funció que faci el producte escalar de 2 vectors de
   reals. Per exemple, si els vectors són [1, 2, 3] i [4, 5, 6], el
   resultat és 1*4 + 2*5 + 3*6 = 18.

   .. solucio::

      Aquest exercici és molt semblant a l'anterior, però com que s'ha de
      retornar un valor, es pot fer una funció::

        float pescalar(const vector<float>& a, const vector<float>& b) {
          float suma = 0.0;
          if (a.size() == b.size()) {
            vector<float>::const_iterator i = a.begin(), j = b.begin();
            while (i != a.end()) {
              suma += (*i) * (*j);
              ++i; ++j;
            }
          }
          return suma;
        }

      En aquest problema, es fa servir un ``if`` que engloba tot el
      càlcul per evitar fer-lo si el tamany dels vectors no és el
      mateix. Una expressió una mica difícil és ``(*i) * (*j)``, ja que
      l'asterisc es fa servir de dues maneres diferents (com a
      multiplicació i per accedir a caselles dels vectors). Per això
      porta parèntesi, per aclarir una mica.

      
.. problema::

   Fes un programa que emmagatzema un text (una seqüència de paraules
   acabada amb ``"."``) i el torna a mostrar per pantalla en el mateix
   ordre.

   .. solucio::

      Per fer aquest programa, farem servir el mètode ``push_back``, ja
      que no sabem com de llarga serà la seqüència. No fem servir
      ``push_front`` perquè és més ineficient (ha de copiar-ho tot cap
      amunt).
      ::

         int main() {
           string p;
           vector<string> seq;

           cin >> p;
           while (p != ".") {
             seq.push_back(p);
             cin >> p;
           }

           vector<string>::iterator i;
           int llarg = 0;
           for (i = seq.begin(); i != seq.end(); i++) {
             cout << *i << ' ';
             llarg += (*i).size() + 1;
             if (llarg > 80) {
               cout << endl;
               llarg = 0;
             }
           }
           cout << endl;
         }

      El programa no té res molt especial, però a la part final, a on es
      mostren les paraules, per tal que surtin per pantalla amb bon
      format, es fa servir una variable ``llarg`` que conté un enter amb
      la longitud de la línia actual. Quan mostrem una paraula ``*i`` (i
      un espai), afegim a ``llarg`` el tamany de la paraula (+ 1 per
      l'espai), i quan ens passem de 80 caracters per línia, posem un
      ``endl`` (i alhora posem ``llarg`` a 0). Així queda el text més ben
      presentat.


.. problema::

   Fes un programa que llegeix una seqüència de matrícules de cotxe
   d'un fitxer ``matricules.txt`` i mostri la seqüència al revés. Les
   matrícules tenen un enter i 3 lletres, com per exemple ``3451
   JKK``.

   .. solucio::

      Esciurem un tipus ``tMatricula`` per agrupar les dades d'una
      matrícula en un sol objecte amb una tupla. Implementarem també els
      operadors d'entrada/sortida (això no és estrictament necessari).
      ::
     
        struct tMatricula {
          int num;
          string lletres;
        };

        ostream& operator<<(ostream& o, const tMatricula& m) {
          o << m.num << ' ' << m.lletres;
          return o;
        }

        istream& operator>>(istream& i, tMatricula& m) {
          i >> m.num >> m.lletres;
          return i;
        }

        int main() {
          ifstream in("matricules.txt");
          tMatricula m;
          list<tMatricula> L;
   
          in >> m;
          while (!in.eof()) {
            L.push_front(m);
            in >> m;
          }
       
          list<tMatricula>::iterator i;
          for (i = L.begin(); i != L.end(); i++) 
            cout << *i << endl;
        }
 
      Comentaris:

      - Fem servir l'operador d'entrada en la instrucció "``in >> m``" i
        el de sortida a la instrucció "``cout << *i``". En aquest últim
        cal veure que ``*i`` és una matrícula, ja que l'iterador apunta a
        objectes de tipus ``tMatricula``.

      - Fem servir ``push_front`` perquè així la llista ja té
        emmagatzemades les matrícules al revés.


.. problema::

   *[De l'exàmen del 16/1/2009]* En una cursa d'atletisme, es disposa
   dels temps de pas dels atletes per la línia d'arribada a cada volta
   de la cursa (les curses poden tenir un número variable de voltes a
   la pista). Es diposa d'aquestes dades en el següent format::

     6 55.6
     3 56.7
     1 58.9
     10 65.2
     ...
     1 95.7
     10 95.8
     3 96.0
     ...

   Es tracta d'una seqüència per ordre cronològic de parelles, a on el
   primer element és un enter (el dorsal de l'atleta corresponent) i
   el segon és el temps de pas (expressat en un número de segons des
   de l'inici de la cursa). L'últim temps de pas de cada dorsal és, de
   fet, la marca de l'atleta (el temps de pas per la meta). El número
   d'atletes d'una cursa és sempre 25, i els dorsals són consecutius,
   començant per l'1.

   Fes un programa que llegeixi aquestes dades d'un fitxer anomenat
   ``cursa.txt`` i doni com a sortida el dorsal del guanyador de la
   cursa i la volta més ràpida que ha fet aquest atleta.

   .. solucio::

      **Solució 1**
   
      .. literalinclude:: ../src/07_Vectors_i_Llistes/atletisme.cpp

      **Solució 2**
   
      .. literalinclude:: ../src/07_Vectors_i_Llistes/atletisme2.cpp
      

.. 
  problema: Josephus problem, "suicidios en un círculo de gente"...

.. 
  problema: Resolver un crucigrama a fuerza bruta...
