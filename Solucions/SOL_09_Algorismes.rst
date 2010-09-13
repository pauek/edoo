
.. tema:: alg

====================
Algorismes de la STL
====================

.. Omplir una llista de caràcters amb espais

.. exercici::
   ::
 
     void omple_amb_espais(list<char>& L) {
       fill(L.begin(), L.end(), ' ');   
     }

.. exercici::

   L'aclariment sobre el tamany permet aplicar la divisió entera simplement::

     void omple_meitat_0(vector<int>& V) {
       fill_n(V.begin(), V.size() / 2, 0);
     }
   
.. exercici::
   ::
     
      int comptar_a(vector<char>& V) {
        return count(V.begin(), V.end(), 'a');
      }

.. exercici::

   Primer ens fem un predicat que mira si una lletra és una vocal::

     bool es_vocal(char c) {
       return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
     }

   Seguidament fem servir aquest predicat amb l'algorisme
   ``count_if``::
   
     int compta_vocals(llista<char>& L) {
       return count_if(L.begin(), L.end(), es_vocal);
     }
     
.. exercici::

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

.. exercici::
   ::

     bool algun_false(const vector<bool>& V) {
       return find(V.begin(), V.end(), false) != V.end();
     }

.. exercici::
   ::
    
     bool algun_0(const vector<int>& V) {
       return find(V.begin(), V.end(), 0) != V.end();
     }

.. exercici::

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

.. exercici::

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

.. exercici::
   
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

.. problema::
   
   En la primera versió fem servir un objecte funció, que conté el
   mínim valor fins al moment.

   .. literalinclude:: ../src/09_Algorismes/minim1.cpp

   La llibrería STL també ens proporciona una funció ``min_element``,
   que simplifica força el programa (no hauriem de fer servir
   l'objecte funció).

   .. literalinclude:: ../src/09_Algorismes/minim2.cpp
