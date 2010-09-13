
.. tema:: cl

=======
Classes
=======

.. exercici::

   L'error el dóna en l'accés i diu, exactament::

      acces.cpp: In function ‘int main()’:
      acces.cpp:3: error: ‘int Prova::x’ is private
      acces.cpp:8: error: within this context

   Primer senyala el camp ``x`` al que intentem accedir (a la línia 3
   del programa ``acces.cpp``) i després diu en quin context l'accés
   és privat (la línia 8 de ``acces.cpp``, el punt exacte a on hem
   intentat accedir).

.. exercici::
   ::

     a.x = 1; // ok  
     b.y = 2; // error: y és privat a B
     c.x = 3; // ok
     d.y = 4; // error: y és privat a D
     a.y = 5; // ok
     b.x = 6; // error: x és privat a B
     c.y = 7; // error: y és privat a C
     d.z = 8; // ok
   
.. exercici::
   ::

     e.a = 1;        // error: 'a' és privat
     e.posa_a(5);    // ok
     posa_a(e,7);    // error: 'posa_a' s'ha de cridar sobre
                     //   algun objecte
     mostra_s(e);    // error: 'mostra_s' s'ha de cridar sobre
                     //   algun objecte i no té paràmetres
     e.mostra_s(7);  // error: 'mostra_s' no té paràmetres
     e.mostra_s = 7; // error: 'mostra_s' és un mètode, no un atribut
     e.c = 'a';      // error: 'c' és privat
     e.s = "hola";   // ok
     e.c = 5;        // error: 'c' és privat i de tipus 'char'
     e.s = 'y';      // error: 's' és de tipus 'string', no 'char'.
     
.. exercici::
   ::
   
      class tVector3D {
        double comp[3];
      public:
        tVector3D();
      
        double get_x() const;
        double get_y() const;
        double get_z() const;
      
        void   suma_vectors(const tVector3D& v2);
        void   resta_vectors(const tVector3D& v2);
        double norma() const;
      };
      
      tVector3D::tVector3D() {
        comp[0] = comp[1] = comp[2] = 0.0;
      }
      
      double tVector3D::get_x() const { return comp[0]; }
      double tVector3D::get_y() const { return comp[1]; }
      double tVector3D::get_z() const { return comp[2]; }
      
      void tVector3D::suma_vectors(const tVector3D& v2) {
        for (int i = 0; i < 3; i++) 
          comp[i] += v2.comp[i];
      }
      
      void tVector3D::resta_vectors(const tVector3D& v2) {
        comp[0] -= v2.comp[0];
        comp[1] -= v2.comp[1];
        comp[2] -= v2.comp[2];
      }
      
      double tVector3D::norma() const {
        double acum = 0.0;
        for (int i = 0; i < 3; i++) acum += comp[i]*comp[i];
        return sqrt(acum);
      }

.. exercici::

   La declaració serà::

     class Punt2D {
       double _x, _y;
     public:	 
       Punt2D();                // per defecte
       Punt2D(const Punt2D& p); // de còpia
       Punt2D(double x, double y);
     };

   La implementació, doncs, és::

     Punt2D::Punt2D() {
       _x = 0.0;
       _y = 0.0;
     }

     Punt2D::Punt2D(const Punt2D& p) {
       _x = p.x;
       _y = p.y;
     }

     Punt2D::Punt2D(double x, double y) {
       _x = x;
       _y = y;
     }

.. exercici::

   La declaració del constructor per a ``ofstream`` ha de ser::
  
     class ofstream {
       // ...
     public:
       // ...
       ofstream(string nom_fitxer);
     };

   Es tracta d'un constructor normal, no és de còpia ni per
   defecte. A part de la declaració d'aquest constructor no sabem res
   més, però la declaració del constructor aniria dins de la de la
   classe ``ofstream``.

.. exercici::
   ::
     
      Cotxe::Cotxe(string marca_motor, double cilindrada)
        : _motor(marca_motor, cilindrada)
      {        
      }

.. problema::
   
   Primer fem la funció principal. Es tracta de fer servir un objecte
   concret ``Histograma`` per anar emmagatzemant els valors que anem
   llegint::
 
     int main() {
       Histograma H;
       double nota;
       
       // Llegim les dades
       cin >> nota;
       while (nota != -1.0) {
       	 H.afegeix(nota);
         cin >> nota;
       }            

       // Mostrem els resultats
       for (int k = 0; k < 11; k++) {
         cout << "Entre " << k << " i "<< k+1 
	      << "  " << H.quantitat(k) << endl;
       }
     }

   A l'hora de mostrar els resultats es posa també la columna 10 (que
   conté les Matrícules d'Honor), per això l'índex ``k`` arriba fins
   al 10.

   Un cop implementada la funció principal, implementem la classe
   ``Histograma``. Farem la implementació fent servir una taula de
   comptadors, a cada casella hi haurà el nombre de valors que hem
   vist en aquell rang (a la casella 2 el número de valors entre 2 i
   3). La declaració amb els atributs posats és::

      class Histograma {
        int _columnes[11]; // 11 per poder posar MH de nota.
      public:
        Histograma();
	void afegeix(double valor); // afegeix un valor
	int  quantitat(int index);
      };

   La implementació del constructor ha d'inicialitzar la taula de
   comptadors, posant cada casella a 0::

      Histograma::Histograma() {
        for (int k = 0; k < 11; k++) 
	  _columnes[k] = 0;
      }

   La implementació d'``afegeix`` converteix el valor a enter (trunca
   el valor, traient els decimals). Per assegurar el tret, abans de
   fer la conversió, truncarem el valor real amb la funció
   ``floor``. Amb el valor enter, podem anar a la casella amb aquest
   índex i incrementar-ne el contingut, primer comprovant que no se
   surt de la taula::

      void Histograma::afegeix(double valor) {
        int i = int(floor(valor));
	if (i >= 0 && i < 11)
	  _columnes[i]++;
	else
	  cout << "Advertència: fora de rang" << endl;
      }

   Finalment, quan s'ha de retornar el valor de l'``Histograma`` per a
   certa columna (el mètode ``quantitat``), es pot retornar
   directament el valor d'aquesta casella, primer comprovant que
   l'índex no se surt del rang::

      int Histograma::quantitat(int index) {
        if (index >= 0 && index < 11)
	  return _columnes[index];
	else 
	  return 0; // no comptem fora d'aquest rang
      }

.. problema::
    
   .. Utilizar "literalinclude" con :lines: 10-20 para incluir
   .. porciones!

   Primer declarem la classe, decidint els paràmetres i els noms del
   mètodes (i si són ``const`` o no). Un cop fet això decidim quina
   implementació farem::
   
      class Conjunt {
        // ...
      public:
        Conjunt(); // c. per defecte
	Conjunt(const Conjunt& C); // c. de còpia
	void afegeix(int n);
	void elimina(int n);
	bool pertany(int n) const;
	int  tamany() const;
	void afegeix_tots(const Conjunt& C);
	void elimina_tots(const Conjunt& C);
	bool igual(const Conjunt& C) const;
      };

   Un cop feta la declaració podem implementar el ``Conjunt`` de dues
   maneres:
    
    - Com una taula d'enters, de màxim 1000 elements, a on
      emmagatzemem els valors de cada enter per separat. La taula es
      mantindrà ordenada, per facilitar la cerca d'elements i la
      comparació de conjunts.

    - Com una taula de ``bool``\s, a on cada casella representa un
      dels enters, i conté ``true`` si l'enter pertany al conjunt i
      ``false`` si no.

   Farem les dues implementacions. 

   **Versió amb taula d'enters**

   Hem de declarar els atributs de la classe (els membres de dades)::

       class Conjunt {
         int _elem[1000];
	 int _nelem;
       public:
         // igual que més amunt
       };

   Amb aquest implementació, el constructor ha de "buidar" el
   conjunt::

       Conjunt::Conjunt() {
         _nelem = 0;
       }

   i el constructor de còpia s'ha de copiar la taula parcialment
   plena (només a on interessa)::

       Conjunt::Conjunt(const Conjunt& C) {
         for (int i = 0; i < C._nelem; i++) {
	   _elem[i] = C._elem[i];
	 }
	 _nelem = C._nelem;
       }

   Llavors venen les operacions d'afegir i esborrar. Per poder-les
   implementar fàcilment, necessitarem poder insertar elements a
   certa posició, esborrar elements a certa posició i cercar
   elements. Aquestes operacions són necessàries per al implementació
   però no són mètodes que vulguem cridar desde fora (no formen part
   del TAD), per tant les farem privades (i posarem un subratllat
   "``_``" a davant per cridar l'atenció sobre aquest fet). Cal
   afegir a la declaració::

       class Conjunt {
         // ...
	 
       private:
	 void _inserta(int n, int pos);
	 void _esborra(int pos);
	 int  _cerca(int n) const;
       
       public:
         // ...
       };

   Si posem aquestes tres declaracions immediatament després dels
   atributs ``_elem`` i ``_nelem``, llavors no caldria posar
   "``private:``" abans. Implementem les 3::
     
       void Conjunt::_inserta(int n, int pos) {
         for (int k = _nelem; k > pos; k--) {
	   _elem[k+1] = _elem[k];
	 }
	 _elem[pos] = n;
	 _nelem++;
       }

       void Conjunt::_esborra(int pos) {
         for (int k = pos; k < _nelem - 1; k++) {
	   _elem[k] = _elem[k+1];
	 }
	 _nelem--;
       }

       // Retornem la posició de l'element major o igual que 'n'
       // [Cerca linial, potser podria ser binària]
       int Conjunt::_cerca(int n) const {
         int k = 0;
	 while (k < _nelem && _elem[k] < n) {
	   k++;
	 }
	 return k;
       }

   La inserció i l'esborrat fan tot el moviment dels valors amunt i
   avall de la taula, copiant en l'ordre correcte entre caselles
   adjacents per anar desplaçant tots els elements que s'han de moure.

   La cerca aprofita el fet que la taula ``_elem`` està ordenada i si
   veu que l'element pel que passa és més gran, ja hauriem d'haver
   vist el número que busquem i per tant surt del bucle. De fet surt
   quan l'element és major o igual, de manera que si el trobem, al
   sortir del bucle la ``k`` ha parat a la posició exacta. Desde fora
   podem comprovar si la posició que es retorna correspon a l'element
   buscat o no. Això serà util a l'hora d'insertar (per veure si
   l'element ja hi pertanyia al conjunt).

   Amb aquestes 3 funcions podem implementar més fàcilment la
   inserció i l'esborrat (en aquesta implementació)::

      void Conjunt::afegeix(int n) {
        int pos = _cerca(n);
	if (_elem[pos] != n) {
	  _inserta(n, pos);
	}
      }

      void Conjunt::elimina(int n) {
        int pos = _cerca(n);
	if (_elem[pos] == n) {
	  _esborra(pos);
	}
      }

   Fent servir ``_cerca`` podem implementar també el mètode
   ``pertany``::

      bool Conjunt::pertany(int n) const {
        int pos = _cerca(n);
	return _elem[pos] == n;
      }

   Per obtenir el número d'elements retornem simplement ``_nelem``::

      int Conjunt::tamany() const {
        return _nelem;
      }

   Per afegir tots els elements d'un altre conjunt, que hem anomenat
   ``afegeix_tots``, farem un bucle i cridarem a ``afegeix`` amb cada un, i
   el mateix per ``elimina_tots``::
    
      void Conjunt::afegeix_tots(const Conjunt& C) {
        for (int i = 0; i < C._nelem; i++)
	  afegeix(C._elem[i]);
      }
      
      void Conjunt::elimina_tots(const Conjunt& C) {
        for (int i = 0; i < C._nelem; i++)
	  elimina(C._elem[i]);
      }

   Per saber si dos conjunts són iguals, ja que les taules que
   contenen els elements estan ordenades, es pot mirar si són iguals
   (quan vegi una sola diferència puc dir que no són iguals)::

      bool Conjunt::igual(const Conjunt& C) const {
        bool iguals = true;
	int k = 0;
	while (k < _nelem && k < C._nelem && iguals) {	
 	  if (_elem[k] != C._elem[k]) {	 
	    iguals = false;
	  }
	  else k++;
	}
	return iguals;
      }

   Aquí finalitza la implementació d'aquesta versió de
   l'exercici. Pots :download:`descarregar el codi d'aquest exercici<../src/02_Classes/conjunt_v1.cpp>`.


   **Versió amb taula de Booleans**

   L'altra versió seria implementar la classe amb un vector que
   indica si un element pertany o no al conjunt amb un valor ``bool``.

   .. literalinclude:: ../src/02_Classes/conjunt_v2.cpp   
   
   Pots :download:`descarregar aquest codi<../src/02_Classes/conjunt_v2.cpp>`.
        
.. problema::

   El problema de la frase té un fitxer de capçalera
   (:download:`frase.h <../src/02_Classes/frase.h>`) com el següent

   .. literalinclude:: ../src/02_Classes/frase.h

   La implementació es faria a :download:`frase.cpp
   <../src/02_Classes/frase.cpp>` i seria així

   .. literalinclude:: ../src/02_Classes/frase.cpp
