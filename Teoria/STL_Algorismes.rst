
.. tema:: alg

====================
Algorismes de la STL
====================

.. contents:: Contingut 
   :depth: 2
   :local:

La STL proporciona un conjunt d'algorismes genèrics que treballen amb
iteradors, i que per tant es poden fer servir en la majoria de
contenidors. De tots els algorismes existents, estudiarem només una
part. Aquests algorismes realitzen operacions típiques que normalment
requeririen que féssim alguna iteració i per tant queden reduïts a una
simple crida a funció. Gairebé tots els algorismes operen en un rang
especificat amb 2 iteradors: l'inicial, i un altre, que fa de
sentinella per indicar el final (però que no es processa, en analogia
a ``end()``).

Per fer servir els algorismes de la STL, s'ha de fer el següent
include::

  #include <algorithm>

Algorismes STL
==============

Objectes Funció
---------------

En les funcions de la STL comentades en aquest capítol, a vegades és
necessari fer servir un "objecte funció". Un objecte funció és un
objecte d'una classe que té definit un operador molt especial:
l'``operator()`` ("operador de crida"). Aquest operador és especial:

- Els paràmetres poden ser de qualsevol tipus.
- El tipus de retorn també pot ser qualsevol.

La decisió sobre quins tipus posar resta a les nostres
mans. L'operador permet cridar l'objecte com si fos una funció, d'aquí
el nom "objecte funció" (en anglès *functor*). Vegem-ne un exemple::

   struct Acumulador {
     double suma;
     Acumulador() { suma = 0.0; }
     void operator()(float x) { suma += x; }
   };

Hem definit, doncs, una classe ``Acumulador`` i li hem posat
constructor (que inicialitza el valor del camp ``suma`` a 0), i el
mencionat ``operator()`` que en aquest cas rep un real i no retorna
res (és ``void``). Ambdós mètodes són *inline*, és a dir que estan
definits a la declaració de la classe. Un cop tenim la classe podem
crear objectes de tipus ``Acumulador``::

   Acumulador A1, A2;

i podem cridar-los com una funció. Quan ho fem, s'invoca el mètode
``operator()``, que tal com es veu més amunt, rep un real com
paràmetre. Així doncs::

   A1(1.0);
   A1(2.0);
   A2(0.1);
   A2(-0.1);

Donat que el mètode ``operator()`` el que fa és acumular el valor que
es passa, l'acumulador ``A1`` haurà sumat 1 i 2, i l'acumulador ``A2``
haurà sumat 0.1 i -0.1. Per mirar el valor de la suma, podem accedir
directament al camp ``suma``, ja que tots dos objectes són un
``struct``. Així doncs::

   cout << A1.suma << ' ' << A2.suma << endl;

mostraria per pantalla 3.0 i 0.0.


Recorreguts
-----------

Omplir un contenidor: ``fill`` i ``fill_n``
"""""""""""""""""""""""""""""""""""""""""""

Si tenim un contenidor seqüencial (que **no** sigui una taula
associativa) amb certs valors i volem omplir-lo tot o una part amb un
cert valor, podem fer servir ``fill``:

.. cpp:function:: void fill(iterator first, iterator last, const T& val)

   L'acció ``fill`` rep dos iteradors que indiquen el principi
   (``first``) i el final (``last``) de la iteració i també un valor,
   que és el que s'ha d'utilitzar per omplir cada element del
   contenidor. Per exemple, suposant que tenim un vector ``C``
   d'enters, el següent codi l'omple amb el valor ``5``::

      fill(C.begin(), C.end(), 5);

   És important veure que la crida seria *exactament* igual en el cas
   que ``C`` fós una llista. Aquest fet és un dels punts forts de la
   STL.

.. exercici::

   Fes una acció que ompli una llista de caràcters amb espais.

   .. solucio::
      ::
 
        void omple_amb_espais(list<char>& L) {
          fill(L.begin(), L.end(), ' ');   
        }
      


Si només volem omplir un cert número d'elements a partir d'un cert
iterador, podem fer servir ``fill_n``:

.. cpp:function:: void fill_n(iterator first, int n, const T& val)

   Aquesta acció omple amb el valor ``val`` els ``n`` valors a partir
   de l'iterador ``first``. Si volem, per exemple, omplir els 5
   primers valors d'un vector ``C`` (més llarg de 5, es clar) amb
   zeros, podem fer::

     fill_n(C.begin(), 5, 0);


.. exercici::

   Fes una acció que ompli la primera meitat d'un vector d'enters amb
   zeros (si el vector té un número senar N d'elements, s'ha d'omplir
   des de l'1 fins al (N-1)/2 inclòs).

   .. solucio::

      L'aclariment sobre el tamany permet aplicar la divisió entera simplement::

        void omple_meitat_0(vector<int>& V) {
          fill_n(V.begin(), V.size() / 2, 0);
        }
   


Comptar elements: ``count`` i ``count_if``
""""""""""""""""""""""""""""""""""""""""""

Si volem comptar els elements d'un contenidor qualsevol que tenen cert
valor, farem servir ``count``::

   int count(iterator first, iterator last, const T& val);

Aquesta funció itera desde ``first`` fins a ``last`` (sense incloure
``last``) i compta tots els elements del contenidor que tenen el valor
``val``. Per exemple, el següent programa mostra per pantalla el valor
``3``::

    vector<int> v;
    v.push_back(2);
    v.push_back(5);
    v.push_back(7);
    v.push_back(-1);
    v.push_back(-1);
    v[0] = -1;

    cout << count(v.begin(), v.end(), -1) << endl;


.. exercici::

   Fes una funció que rebi un vector de caràcters i compti quantes
   ``'a'``\s hi ha.

   .. solucio::
      ::
        
         int comptar_a(vector<char>& V) {
           return count(V.begin(), V.end(), 'a');
         }
   

Si volem comptar elements d'un contenidor que tenen valors diferents
però compleixen una condició, podem fer servir ``count_if``, que rep
un predicat:

.. cpp:function:: void count_if(iterator first, iterator last, Predicate func)

   El predicat (``func``) és una funció que retorna un valor
   ``bool``. La funció ``count_if`` fa una iteració pel contenidor i
   crida a ``pred`` per a cada element, i llavors compta per a quants
   valors el predicat és cert. Per exemple, si tenim el predicat::

     bool paraula_curta(string s) {
       return s.size() < 4;
     }

   llavors, podem comptar quantes paraules curtes (de menys de 4 lletres)
   hi ha en un contenidor ``C`` de la forma següent::

     count_if(C.begin(), C.end(), paraula_curta);

   Aquí és molt important veure com ``paraula_curta`` *no s'està
   cridant*, de fet estem passant una funció com a paràmetre d'una
   altra funció. És ``count_if`` que farà la crida a ``paraula_curta``
   per a cada element del contenidor.

   Com a predicat també es pot passar un objecte funció. Per exemple,
   per comptar quants elements d'una llista de reals es troben dins de
   cert interval farem el següent::

     struct DinsInterval {
       float min, max;
       Interval(float _min, _max) { min = _min; max = _max; }
       bool operator()(float x) {
         return x >= min && x <= max;
       }
     };

   Aquest objecte funció es pot cridar com un predicat (retorna
   ``bool``), i rep com a paràmetre un objecte del tipus que hi ha a
   la llista. Així, doncs::

     list<float> L;
     L.push_back(-1.0);
     L.push_back(1.0);
     L.push_back(2.0);
     L.push_back(3.0);
     L.push_back(10.0);

     DinsInterval di(0.0, 5.0);
     cout << count_if(L.begin(), L.end(), di) << endl;

   mostrarà per pantalla un 3 (tant 1 com 2 com 3 són a dins de
   l'interval 0.0-5.0).

.. exercici::
   
   Fes una funció que compti quantes vocals hi ha en una llista de
   caràcters.

   .. solucio::

      Primer ens fem un predicat que mira si una lletra és una vocal::
   
        bool es_vocal(char c) {
          return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
        }

      Seguidament fem servir aquest predicat amb l'algorisme
      ``count_if``::
      
        int compta_vocals(llista<char>& L) {
          return count_if(L.begin(), L.end(), es_vocal);
        }

.. ------------------------------------
.. Aquí falta min_element i max_element
.. ------------------------------------


Recorregut genèric: ``for_each``
""""""""""""""""""""""""""""""""

Si el que volem fer amb cada element és una operació més complicada,
que no és comptar, ni omplir, ni cap de les operacions anteriors,
sempre podem fer un recorregut genèric amb ``for_each``:

.. cpp:function:: void for_each(iterator first, iterator last, UnaryFunction func)

   El tercer paràmetre és una acció, anàlogament al cas de ``count``, que
   no ha de retornar res i rebrà un element del contenidor (per
   referència), amb el qual pot fer qualsevol càlcul. Per exemple, si
   volem duplicar tots els elements d'un vector d'enters, podem crear
   primer la funció duplica::

     void duplica(int& n) {
       n = n * 2;
     }
 
   i en un lloc del programa a on tinguem un contenidor ``C`` amb
   valors de tipus ``int``, podem duplicar tots els elements amb::

     for_each(C.begin(), C.end(), duplica);

   Això recorrerà tots els elements i cridarà la funció ``duplica`` passant
   per referència cada element del contenidor. 


.. exercici::

   Assumint la declaració següent::

     struct tPunt {
       float x, y;
     };

   Fes una acció que rebi una llista de punts i desplaçi tots els punts
   de la llista 5 unitats en l'eix de les x.

   .. solucio::

      Primer ens fem una acció que rebi com a paràmetre un punt i el
      desplaci::
 
        void mou_punt(tPunt& P) {
          P.x += 5;
        }

      Seguidament podem fer servir ``for_each`` per recórrer la llista de
      punts::

        void mou_llista_punts(list<tPunt>& LP) {
          for_each(L.begin(), L.end(), mou_punt);
        }


Cerques: ``find`` i ``find_if``
-------------------------------

Si volem buscar un element dins d'un contenidor seqüencial (ja que les
taules associatives ja tenen un mètode ``find()``), podem fer servir
``find``:

.. cpp:function:: iterator find(iterator first, iterator last, const T& val)

   Aquesta funció fa una cerca i para quan troba un element a dins del
   vector que tingui el valor ``val``, retornant un iterador a aquest
   element::

     vector<float> v(10, 0.5);
     v[5] = 1.0;

     vector<float>::iterator i;
     i = find(v.begin(), v.end(), 1.0);
     i++;
     *i = 0.0;  // posa la casella 6 a 0.0

   En aquest exemple, a l'inici, el vector està ple amb el valor 0.5,
   i tot seguit es canvia la casella 5 (6è element) a 1.0. Després
   s'invoca ``find`` que pararà a la 5a casella, s'incrementa
   l'iterador a aquesta casella (ara apuntarà a la 6a), i llavors es
   canvia el valor a 0.0, que canviarà la 6a casella.

   Quan ``find`` no troba cap element que tingui el valor buscat,
   retornarà un iterador que és igual que el valor ``last`` que li hem
   passat (el que nosaltres hem considerat com el sentinella).

.. exercici::

   Fes una funció que retorni cert si un vector de Booleans conté
   algun valor ``false``.

   .. solucio::
      ::

        bool algun_false(const vector<bool>& V) {
          return find(V.begin(), V.end(), false) != V.end();
        }
   

.. exercici::

   Fes una funció que retorni ``true`` si un vector d'enters conté
   algun 0.

   .. solucio::
      ::
    
        bool algun_0(const vector<int>& V) {
          return find(V.begin(), V.end(), 0) != V.end();
        }



Quan el que busquem en un contenidor no és un valor concret sinó que
ha de complir una condició, podem fer servir un predicat, i podem
utilitzar ``find_if``:

.. cpp:function:: iterator find_if(iterator first, iterator last, Predicate pred)

   Aquesta funció realitza una cerca i para quan el predicat que li hem
   passat retorna ``true`` per a cert element. D'aquest element es retorna
   un iterador. Per exemple, suposant la declaració següent::

     struct tPunt { float x, y; };

   i si disposem d'un predicat com::

     bool fora_cercle_unitat(const tPunt& P) {
       return sqrt(P.x*P.x + P.y*P.y) > 1.0;
     }

   podem cercar el primer punt d'una llista ``LP`` de punts que estigui
   fora del cercle unitat amb::

     list<tPunt>::iterator i;
     i = find_if(LP.begin(), LP.end(), fora_cercle_unitat);
     if (i != LP.end()) {
       cout << "No hi ha cap punt fora del cercle unitat" << endl;
     }
  
   Tal com ``find``, quan ``find_if`` no troba cap element per al qual
   el predicat és ``true``, retornarà l'iterador ``last``, que en el
   nostre cas és ``LP.end()``. Això permet veure si no hi ha cap punt
   que estigui fora del cercle unitat.


.. exercici::

   Fes una funció que retorni ``true`` si en una frase (una llista de
   ``string``\s, cap paraula conté una ``'e'``.

   .. solucio::

      Primer fem un predicat que ens digui si una paraula conté una
      ``'e'``::
   
        bool conte_e(string s) {	
          for (int k = 0; k < s.size(); k++) {
            if (s[k] == 'e') return true;
          }
          return false;
        }

      De fet aquest predicat també es pot implementar així (ja que els
      ``string``\s es poden veure com a contenidors, és a dir, vectors de
      caracters, i tenen ``begin()`` i ``end()``)::

        bool conte_e(string s) {
          return find(s.begin(), s.end(), 'e') != s.end();
        }
   
   

Ordenació
---------

Per ordenar contenidors seqüencials (les taules associatives ja estan
ordenades per la clau), podem fer servir ``sort``:

.. cpp:function:: void sort(iterator first, iterator last)

   Aquesta acció reposiciona els elements per tal que estiguin en ordre,
   fent servir el operador ``<`` apropiat per als elements del contenidor
   (si són tipus bàsics, l'operador normal, si són classes, es crida
   l'``operator<`` que hi hagi definit). Per exemple, si tenim la
   classe::

     class Persona {
       string nom, cognoms;
       int edat;
     public:
       //...
       bool operator<(const Persona& P) const;
     };

     bool Persona::operator<(const Persona& P) const {
       return cognoms < P.cognoms;
     }

   Llavors podem invocar, sobre un contenidor ``C`` amb elements de tipus
   ``Persona`` l'algorisme d'ordenació::

     sort(C.begin(), C.end());

   i es farà servir l'``operator<`` de la classe ``Persona``. 


.. exercici::

   Donada la declaració (incompleta) de la classe següent::

     class Fruita {
       string nom;
       float sucre, acidesa, amargor;
     public:
       // ...
     };

   Defineix un operador ``<`` per comparar fruites en què es miri
   només el grau de sucre (el camp ``sucre``). Llavors defineix una
   acció que ordeni un vector de fruites.


   .. solucio::

      Primer fem l'operador per a les fruites. Hem d'afegir a la
      declaració de la classe el següent::

        bool operator<(const Fruita& f) const;

      i fer la implementació a fora::

        bool Fruita::operator<(const Fruita& f) const {
          return sucre < f.sucre;
        }

      Un cop tenim això podem definir l'acció que ens ordeni les
      fruites::

        void ordena_fruites(vector<Fruita>& v) {
          sort(v.begin(), v.end());
        }

Si volem ordenar certs valors i no està definit l'operador
corresponent, o bé volem ordenar les mateixes dades per diferents
criteris, podem fer servir una versió de ``sort`` que ens permet
aportar un predicat (binari, que compararà elements) amb el qual
``sort`` podrà determinar quins elements van abans de quins. Per
exemple, si disposem d'una estructura::

   struct Llibre {
     string titol, autor;
     int pagines;
   };

i tenim el predicat següent (binari, és a dir que rep 2
arguments per comparar)::

   bool compara_titol(const Llibre& l1, const Llibre& l2) {
     return l1.titol < l2.titol;
   }

llavors podem, donada una llista de llibres ``L``, ordenar els llibres
pel títol així::

   sort(L.begin(), L.end(), compara_titol);

Quan l'acció ``sort`` necessiti determinar si un llibre va abans que
un altre, cridarà ``compara_titol``. Si volem ordenar els llibres pel
número de pàgines, podem definir un nou predicat::

   bool compara_pagines(const Llibre& l1, const Llibre& l2) {
     return l1.pagines < l2.pagines;
   }

i llavors cridem l'acció ``sort`` així::

  sort(L.begin(), L.end(), compara_pagines);


.. exercici::

   Sense redefinir l'operador ``<``, fes una funció que ordeni una
   llista d'elements de la classe ``Fruita`` de l'exercici anterior
   per acidesa.

   .. solucio::
   
      Primer fem un predicat ``compara_acidesa`` que compari dues fruites
      per acidesa (sense tocar l'``operator<``). Per poder implementar
      aquesta funció, necessitem poder accedir al camp ``acidesa`` que és
      privat. Tenim dues opcions: fer la funció ``compara_acidesa`` amiga
      (``friend``) de la classe ``Fruita`` o bé crear un mètode
      ``get_acidesa()`` que retorni l'acidesa d'una fruita. Aquí optarem
      per la segona opció. El mètode ``get_acidesa`` el podem afegir a la
      declaració i fer-lo *inline* (l'implementem a la declaració
      mateix)::

        double get_acidesa() const { return acidesa; }

      Ara podem implementar ``compara_acidesa`` en condicions::

        bool compara_acidesa(const Fruita& f1, const Fruita& f2) {
          return f1.get_acidesa() < f2.get_acidesa();
        }
    
      Un cop fet això podem implementar la ordenació per acidesa, que es
      limita a cridar a ``sort`` de la forma correcta::

        void ordena_fruites_acidesa(vector<Fruita>& v) {
          sort(v.begin(), v.end(), compara_acidesa); 
        }
   

Problemes
=========

.. problema::

   Fent servir la STL, fes un programa que llegeixi una seqüència
   d'enters acabada en -1 i mostri per pantalla l'element més petit
   (el mínim).

   .. solucio::
    
      En la primera versió fem servir un objecte funció, que conté el
      mínim valor fins al moment.

      .. literalinclude:: ../src/09_Algorismes/minim1.cpp

      La llibrería STL també ens proporciona una funció ``min_element``,
      que simplifica força el programa (no hauriem de fer servir
      l'objecte funció).

      .. literalinclude:: ../src/09_Algorismes/minim2.cpp


   
