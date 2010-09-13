
.. tema:: ops

========================
Operadors i Sobrecàrrega
========================

.. exercici::

   ======================= ====== =================================================
   Crida                   Funció Comentaris
   ----------------------- ------ -------------------------------------------------
   ``manipula(a, true)``   6
   ``manipula(r, s)``      2
   ``manipula(4, q)``      2
   ``manipula(a, 5)``      1
   ``manipula(68)``        3      Es converteix el caracter a enter implícitament
   ``manipula(3, 4, p)``   5
   ``manipula(a, 5.7)``    2      ``a`` es converteix a double implícitament     
   ``manipula(r, "Fiji")`` X      No hi ha cap funció compatible
   ``manipula(char(98))``  3
   ``manipula(17, q)``     6
   ======================= ====== =================================================

.. exercici::

   L'operador multiplicació es declararia com::

     Complex operator*(const Complex& c1, const Complex& c2);
   
   L'operador de "menor o igual" seria::
   
     bool operator<=(const Complex& c1, const Complex& c2);

.. exercici::

   La declaració de l'operador d'assignació, degut a que modifica l'operand de l'
   esquerra (la variable la que assignem) té la següent declaració::

     Complex operator=(Complex& var, const Complex& valor);

   A part, per poder fer assignacions en cadena, tal com::
 
     a = b = c;

   l'operador ha de retornar un ``Complex``, ja que la assignació en cadena es 
   pot veure com::

     a = (b = c);


.. exercici::
   
   ========================== =======================================================
   Expressió                  Traducció
   -------------------------- -------------------------------------------------------
   ``-x``		      ``operator-(x)``
   ``x - y``		      ``operator-(x, y)``
   ``x / y / z``	      ``operator/(operator/(x, y), z)``
   ``p || q && r``	      ``operator||(p, operator&&(q, r))``
   ``!q``     	  	      ``operator!(q)``
   ``cout << f << endl``      ``operator<<(operator<<(cout, f), endl)``
   ``x + 1 < y - 2``	      ``operator<(operator+(x, 1), operator-(y, 2))``
   ``cout << z + 3 << endl``  ``operator<<(operator<<(cout, operator+(z, 3)), endl)``
   ========================== =======================================================

.. exercici::

   L'operador hauria de dir-se ``operator/``, ja que realitza la "divisió" d'un vector de 
   dues dimensions per un real.

.. exercici::

   El codi transformat serà::

     int a, b;
     operator>>( operator>>(cin, a), b );
     operator<<( operator<<( operator<<(cout, " a + b = "), a + b ), endl );

.. exercici::

   Per poder accedir als membres d'``Assignatura``, farem l'operador una funció ``friend``. 
   La declaració serà, doncs::

     class Assignatura {
       // ...
     public:
       // ...
       friend ostream& operator<<(ostream& o, const Assignatura& A);
     };

   La implementació pot ser::

     ostream& operator<<(ostream& o, const Assignatura& A) {
       o << A.nom << ' ' << A.codi << ' ';
       if (A.fase_selectiva) o << "[fase_selectiva] ";
       if (A.lliure_eleccio) o << "[lliure_eleccio]";
       return o;
     }

.. exercici::

   L'operador per sumar dies a una data serà senzill perquè la classe fa servir un enter
   que representa el número de dies directament i per tant no hem de tenir en compte el
   mes de l'any ni quants dies té, etc. L'operador és la suma amb un enter, i si el fem
   com a mètode, es declararia aixi::

     class Data {
       // ...
     public:
       Data operator+(int num_dies);
     };

   La implementació ha de crear una data nova (perquè la que se suma no canvia) i a la nova 
   data posar-li la suma dels dies de la data sumada + el número que ens passen::
 
     Data Data::operator+(int num_dies) {
       Data d;
       d._epoch = _epoch + num_dies;
       return d;
     }

.. exercici::

   ========================== ==========================================
   Expressió                  Traducció
   -------------------------- ------------------------------------------
   ``1.5 + p``		      [Error: no hi ha cap operador disponible]
   ``p + 2.0``                ``operator+(p, 2.0)``
   ``cin >> p``		      [Error: no hi ha cap operador disponible]
   ``p / 3``  		      ``p.operator/(3)``
   ``cout && p``	      ``operator&&(cout, p)``
   ``p * 7``		      ``p.operator*(7)``
   ``7.5 << p << pp``	      ``operator<<(operator<<(7.5, p), pp)``
   ========================== ==========================================


.. problema::
   
   Primer declarem l'operador dins de la classe (ja que és intern)::
     
     class Vector10 {
       // ...
     public:
       double operator*(const Vector10& v) const;
     };

   Tot seguit l'implementem::

     void Vector10::operator*(const Vector10& v) const {
       double acum = 0.0;
       for (int k = 0; k < 10; k++) {
         acum += comp[k] * v.comp[k];
       }
       return acum;
     }

.. problema::

   Primer fem el fitxer :download:`hora.h <../src/03_Operadors/hora.h>`
   que contingui la declaració de la classe ``Hora``:
 
   .. literalinclude:: ../src/03_Operadors/hora.h

   Tot seguit creem el fitxer :download:`hora.cpp <../src/03_Operadors/hora.cpp>`
   que contingui la implementació de la classe ``Hora`` (incloent el fitxer ``hora.h``):

   .. literalinclude:: ../src/03_Operadors/hora.cpp

.. problema::

   El programa seria el següent (:download:`hora_main.cpp <../src/03_Operadors/hora_main.cpp>`)

   .. literalinclude:: ../src/03_Operadors/hora_main.cpp

   Confeccionar un :download:`fitxer de prova <../src/03_Operadors/intervals.txt>` amb 
   uns intervals temporals pot anar bé per provar el programa.
