
======================
STL, Vectors i Llistes
======================

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
  accedir a les caselles tal com s'ha fet fins ara amb les taules. El
  vector està declarat en el fitxer de capçalera del mateix nom. Per
  utilitzar la classe ``vector`` hem d'incloure el fitxer així::

    #include <vector>

Declaració de vectors
---------------------

Per declarar un ``vector``, hem d'esciure el següent (el tipus ``T``
pot ser qualsevol)::
  
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

.. cfunction:: vector<T>()
     
   Constructor per defecte, crea el vector buit.


.. cfunction:: vector<T>(int size)
 
   Constructor amb un tamany (``size``), crea el vector amb un tamany
   concret que especifiquem nosaltres. És necessari que el tipus ``T``
   *tingui constructor per defecte*. Per exemple, si volem crear un
   vector de 20 enters farem::
 
     vector<int> v1(20);
    

.. cfunction:: vector<T>(int size, const T& t)
 
   Constructor que rep un paràmetre de tamany i un element amb què omplir
   el vector. Si volem un vector de 50 caràcters amb una ``'z'`` a cada casella,
   farem::

     vector<char> lletres(50, 'z');


.. cfunction:: vector<T>(const vector<T>& v)

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
   
   Declara un vector de 500 enters i omple'l, per ordre, amb els
   nombres 500, 499, 498, 497, ..., 2 i 1.

Mètodes consultors
------------------

Els mètodes consultors disponibles per a ``vector`` són:

.. cfunction:: int vector<T>::size() const

   Retorna el tamany del vector.


.. cfunction:: bool vector<T>::empty() const 

   Retorna ``true`` si el vector està buit.


.. cfunction:: const T& vector<T>::front() const

   Retorna una referència al primer element del vector.


.. cfunction:: const T& vector<T>::back() const
  
   Retorna una referència a l'últim element del vector.


.. exercici::
 
   Fes una funció que rebi un vector d'enters per referència i calculi
   la suma dels seus elements. Si el vector està buit, s'ha de
   retornar -1.

.. exercici::

   Fes una funció que rebi un vector de reals i retorni la mitjana
   entre el primer i l'últim element. Si el vector està buit s'ha de
   retornar -1.0.


Mètodes modificadors
--------------------

.. cfunction:: void vector<T>::resize(int n)

   Redimensiona el vector perquè tingui tamany ``n``.

.. cfunction:: void vector<T>::resize(int n, const T& t)

   Redimensiona el vector perquè tingui tamany ``n`` i si és necessari
   fer-lo més gran, omple les noves caselles amb ``t``.

.. cfunction:: void vector<T>::push_back(const T& t)

   Afegeix l'element ``t`` al final del vector (i per tant allarga
   el vector en 1 unitat).

.. cfunction:: void vector<T>::pop_back()

   Esborra l'últim element del vector (no el retorna), i per tant
   escurça el vector en 1 unitat).

.. cfunction:: void vector<T>::clear()

   Esborra tots els elements del vector.


.. exercici::

   Declara un vector de caràcters buit i omple'l amb les lletres
   minúscules fent servir ``push_back``.

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

.. exercici::

   Quin algorisme omple el vector més ràpidament, l'exercici 2 o el 6?


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

Donat un iterador, per tal que apunti a una posició del vector
concreta, tenim els següents mètodes:

.. cfunction:: vector<T>::iterator begin()
  
   Retorna un iterador a la primera posició del vector.

.. cfunction:: vector<T>::iterator end()

   Retorna un iterador a la posició *immediatament posterior a la última*
   del vector.

El final d'un vector (el valor de ``end()``) és una posició especial
del vector ja que no conté cap valor (està fora del vector), però
serveix per marcar el final (tal com un sentinella).

.. exercici::

   Per a un vector d'enters ``vi``, declara un iterador ``i`` i
   inicialitza'l perquè apunti al principi i un altre ``iend`` perquè
   apunti al final.

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

.. exercici::
  
   Fes una funció que cerqui un valor ``true`` en un vector de
   ``bool``\s, i retorni cert si l'ha trobat i fals si no.


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

.. cfunction::  list<T>()

   Constructor per defecte, crea la llista buida.

.. cfunction:: list<T>(int size)

   Crea una llista amb un tamany ``size`` i cada element de la llista
   serà el resultat de cridar el constructor per defecte de la classe
   ``T`` (ha d'existir, per tant). Per exemple, per crear una llista
   de 40 ``bool``\s, farem::

     list<bool> l1(40);


.. cfunction:: list<T>(int size, const T& t)

   Crea una llista amb un tamany ``size`` i omple tots els elements
   fent servir ``t`` com a model (farà servir el constructor de còpia
   de la classe ``T``, per tant aquest ha d'existir). Per crear una
   llista de 5 paraules en què totes tinguin el valor ``"SFDK"``,
   farem::
         
     list<string> paraules(5, "SFDK");

.. cfunction:: list<T>(const list<T>& L)

   Constructor de còpia, crea una llista a partir d'una altra, copiant
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
""""""""""""""""""

Les llistes també tenen els mètodes consultors estàndar de contenidors
d'STL:

.. cfunction:: int list<T>::size() const
   
   Per obtenir el tamany. Suposant que :math:`n` és el tamany de la
   llista, aquesta funció té un cost :math:`O(n)`, és a dir, linial.


.. cfunction:: bool list<T>::empty() const
   
   Retorna ``true`` si la llista està buida. Aquesta funció té cost
   O(1), i és molt més eficient que escriure ``size() == 0``.


.. cfunction:: const T& list<T>::front() const

   Retorna una referència l'últim element.


.. cfunction:: const T& list<T>::back() const

   Retorna una referència al primer element.

Mètodes modificadors
""""""""""""""""""""

Com també els següents mètodes modificadors estàndar:


.. cfunction:: void list<T>::clear()
   
   Esborra tots els elements de la llista.


.. cfunction:: void list<T>::resize(int n)
   
   Redimensiona la llista.


.. cfunction:: void list<T>::resize(int, const T& t)
   
   Redimensiona la llista, omplint els elements nous amb el valor
   ``t`` (si és necessari).


.. cfunction:: void list<T>::push_back(const T& t)
   
   Afegeix al final.


.. cfunction:: void list<T>::push_front(const T& t)
   
   Inserta al principi.


.. cfunction:: void list<T>::pop_back()
   
   Esborra un element del final.

.. exercici::
   
   Fes una acció que rebi una llista d'enters per referència,
   n'esborri tots els elements i l'ompli amb els nombres 500, 499,
   498, ..., 2 i 1 fent servir ``push_front``. 


Mètodes especials de ``list``
"""""""""""""""""""""""""""""

.. cfunction:: void list<T>::pop_front()
   
   Esborra un element del principi, opera igual que ``pop_back`` però
   al principi de la llista (no existeix en vectors).

.. cfunction:: void list<T>::remove(const T& val)
   
   Esborra els elements de la llista que tinguin el valor ``val`` (fa
   servir el ``operator==``). Per exemple, si una llista ``L`` conté
   els elements 1, 2, 3, 4, i 5 en aquest ordre, si fem::

     L.remove(3);

   llavors la llista tindrà els elements 1, 2, 4 i 5.


.. cfunction:: void list<T>::reverse()
   
   Canvia d'ordre els elements d'una llista (eficiència :math:`O(n)`). És
   a dir, si una llista conté (1, 2, 3), després d'haver cridat
   ``reverse`` contindrà (3, 2, 1).


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
"""""""""""""""""""""""""""""""""""""

Les llistes permeten insertar elements al mig a través de mètodes
especials. Vegem aquests mètodes:

.. cfunction:: void list<T>::insert(iterator pos, const T& t)
   
   Inserta el valor ``t`` *abans* de l'element apuntat per l'iterador
   ``pos``.

.. cfunction:: void list<T>::insert(iterator pos, int n, const T& t)
   
   Inserta ``n`` vegades el valor ``t`` *abans* de l'element apuntat
   per l'iterador ``pos``.

.. cfunction:: iterator list<T>::erase(iterator pos)
   
   Esborra l'element apuntat per ``pos`` i retorna un iterador a
   l'element següent (ja que si s'esborra l'element al que apuntava
   l'iterador aquest ja no serà vàlid).

.. cfunction:: iterator list<T>::erase(iterator first, iterator last)
   
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

.. problema::

   Fes una funció que sumi dos vectors de reals casella a casella. Per
   exemple, si els vectors són [1, 2, 3] i [4, 5, 6], el
   resultat és [5, 7, 9]. La funció no ha de fer res si els
   vectors no tenen el mateix tamany.

.. problema::

   Fes una funció que faci el producte escalar de 2 vectors de
   reals. Per exemple, si els vectors són [1, 2, 3] i [4, 5, 6], el
   resultat és 1*4 + 2*5 + 3*6 = 18.
      
.. problema::

   Fes un programa que emmagatzema un text (una seqüència de paraules
   acabada amb ``"."``) i el torna a mostrar per pantalla en el mateix
   ordre.

.. problema::

   Fes un programa que llegeix una seqüència de matrícules de cotxe
   d'un fitxer ``matricules.txt`` i mostri la seqüència al revés. Les
   matrícules tenen un enter i 3 lletres, com per exemple ``3451 JKK``.

.. problema::

   Es necessita un programa per organitzar la informació interna de
   les trucades de telèfon d'una empresa. El format de les dades és un
   fitxer amb una seqüència de trucades com::

     + 2008/20/11 00:00:26 44 admin
     + 2008/20/11 00:00:44 55 montse
     - 2008/20/11 00:52:58 44 admin
     - 2008/20/11 01:17:28 55 montse
     + 2008/20/11 02:12:47 69 montse
     - 2008/20/11 02:19:36 69 montse
     + 2008/20/11 02:28:20 83 montse
     - 2008/20/11 02:32:02 83 montse
     + 2008/20/11 12:28:16 56 montse
     - 2008/20/11 12:29:29 56 montse
     + 2008/20/11 18:36:18 69 admin
     - 2008/20/11 18:58:24 69 admin

   El primer caràcter indica quan comença ("``+``") o acaba ("``-``") la
   trucada (com que les dades estan ordenades per l'hora, una trucada
   sencera són 2 línies possiblement separades). El segon camp indica
   la data ("``any/dia/mes``"), el tercer l'hora i el quart i cinquè són
   l'extensió que s'ha marcat i l'usuari que ha fet la trucada.

   Es vol obtenir un resum d'aquestes dades en el format següent::

     Ext 44:
         admin 2008/20/11[00:00:26--00:52:58]
     Ext 55:
         montse 2008/20/11[00:00:44--01:17:28]
     Ext 56:
         montse 2008/20/11[12:28:16--12:29:29]
     Ext 69:
         admin 2008/20/11[18:36:18--18:58:24]
         montse 2008/20/11[02:12:47--02:19:36]
     Ext 83:
         montse 2008/20/11[02:28:20--02:32:02]

   El format indica cada extensió que ha rebut trucades, i una llista
   d'usuaris que les han fet. Seguit de cada usuari hi ha una llista de
   les trucades amb la data i la hora inicial i final entre corxets.

   S'ha de seguir el format exactament tal com surt, respectant
   l'espai a l'esquerra, la puntuació ("``:``" i "``--``", etc). En
   particular, les 12 de la nit en punt hauria de sortir com
   "``00:00:00``". Feu servir fitxers de prova per provar el programa (
   :download:`tel1.txt <src/07_Vectors_i_Llistes/tel1.txt>` i
   :download:`tel2.txt <src/07_Vectors_i_Llistes/tel2.txt>`).
