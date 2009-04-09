
=======
Vectors
=======

.. exercici::
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

.. exercici::
   ::

     vector<int> v(500);
     for (int k = 0; k < 500; k++) v[k] = 500 - k;


.. exercici::
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
   ::

      float mitjana_1_n(const vector<float>& v) {	
        return (v.front() + v.back()) / 2.0;
      }
   
.. exercici::
   ::

      vector<char> v;
      for (k = 0; k < 26; k++) {
        v.push_back(char(97 + k));
      }


.. exercici::
   ::

      void omple_vector(vector<int>& v) {
        v.clear();
	for (int k = 0; k < 500; k++) {
	  v.push_front(k);
	}
      }


.. exercici::

   L'algorisme que omple el vector més ràpidament és el de l'exercici
   2, ja que primer reserva espai per a tot el vector i després hi
   accedeix. L'exercici 6 ha d'anar redimensionant el vector mica en
   mica.

.. exercici::
   ::

      vector<double>::iterator i;
      vector<Data>::iterator j;

.. exercici::
   ::

      vector<int>::iterator i, iend;
      i = vi.begin();
      iend = vi.end();

.. exercici::
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

.. exercici::

   En aquest exercici, es rebràn 2 paràmetres d'entrada (els dos
   vectors a concatenar) i s'ha de retornar un vector, però en comptes
   de fer una funció, farem una acció, per tal de no haver de copiar
   el vector resultat (que és el que passaria si el retornem tal
   qual).
   ::

	void concatena(const vector<int>& a, const vector<int>& b,
	     	       vector<int>& res) {
	  res.resize(a.size() + b.size());
	  vector<int>::iterator i = a.begin(), ir = res.begin();
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

.. exercici::

   En aquest exercici ens passa com l'anterior respecte al tema dels
   paràmetres.
   ::

	void suma(const vector<float>& a, const vector<float>& b,
	          vector<float>& res) {
	  if (a.size() != b.size()) return;
  	  res.resize(a.size());
	  vector<float>::iterator i = a.begin(), j = b.begin();
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


.. exercici::

   Aquest exercici és molt semblant a l'anterior, però com que s'ha de
   retornar un valor, es pot fer una funció::

     float pescalar(const vector<float>& a, const vector<float>& b) {
       float suma = 0.0;
       if (a.size() == b.size()) {
         vector<float>::iterator i = a.begin(), j = b.begin();
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

.. exercici::

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
