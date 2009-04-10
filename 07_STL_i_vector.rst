
=============
STL i vectors
=============

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
-------

vector (classe ``vector``)
  Un vector és una versió millorada de les taules ordinàries de
  C++. En particular, és una classe que implementa una *taula de
  tamany variable*, i que sobrecarrega l'``operator[]``, per poder
  accedir a les caselles tal com s'ha fet fins ara amb les taules. El
  vector està declarat en el fitxer de capçalera del mateix nom. Per
  utilitzar la classe ``vector`` hem d'incloure el fitxer així::

    #include <vector>

Declaració de vectors
"""""""""""""""""""""

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
''''''''''''''''''''''''''''''''

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
""""""""""""""""""

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
""""""""""""""""""""

.. cfunction:: void vector<T>::resize(int n)

   Redimensiona el vector perquè tingui tamany ``n``.

.. cfunction:: void vector<T>::resize(int n, const T& t)

   Redimensiona el vector perquè tingui tamany ``n`` i si és necessari
   fer-lo més gran, omple les noves caselles amb ``t``.

.. cfunction:: void vector<T>::push_back(const T& t)

   Afegeix l'element ``t`` al final del vector (i per tant allarga
   el vector en 1 unitat).

.. cfunction:: void vector<T>::push_front(const T& t)

   Posa l'element ``t`` al principi del vector (i per tant mou tots els
   elements 1 posició amunt i allarga el vector en 1 unitat).

.. cfunction:: void vector<T>::pop_back()

   Esborra l'últim element del vector (no el retorna), i per tant
   escurça el vector en 1 unitat).

.. cfunction:: void vector<T>::clear()

   Esborra tots els elements del vector.


.. exercici::

   Declara un vector de caràcters buit i omple'l amb les lletres
   minúscules fent servir ``push_back``.

.. exercici::
   
   Fes una acció que rebi un vector d'enters per referència,
   n'esborri tots els elements i l'ompli amb els nombres 500, 499,
   498, ..., 2 i 1 fent servir ``push_front``. 

Eficiència de les operacions sobre ``vector``
'''''''''''''''''''''''''''''''''''''''''''''

Els vectors es caracteritzen per tenir un temps d'accés ràpid
(independent del tamany), però els temps d'inserció és gran. Suposant
que el tamany d'un vector és "n", el cost de les operacions sobre un
vector és:

.. csv-table:: 
   :header: "Operació", "``vector``"
   :widths: 30, 5
   
   "Accedir al primer element", "O(1)"
   "Accedir a l'últim element", "O(1)"
   "Accedir a un element intermig", "O(1)"
   "Inserir/Esborrar al principi", "O(n)"
   "Inserir/Esborrar al final", "O(1)"
   "Inserir/Esborrar al mig", "O(n)"


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


Problemes
---------

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

