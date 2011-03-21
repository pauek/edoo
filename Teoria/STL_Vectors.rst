
.. tema:: vc

======================
Vectors
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
