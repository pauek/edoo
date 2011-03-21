
.. tema:: lst

=====================
Llistes
=====================

.. contents:: Contingut 
   :depth: 2
   :local:

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
===================

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

Llistes
====================

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
