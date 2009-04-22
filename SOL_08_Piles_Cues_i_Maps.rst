
=================================
Piles, Cues i Taules Associatives
=================================

.. exercici::

   Aquest exercici requerirà l'ús d'un iterador ``const``.
   ::

       float suma_vector(const vector<float>& v) {
         float suma = 0.0;
         vector<float>::const_iterator i = v.begin();	 
	 for (i = v.begin(); i != v.end(); i++) {
	   suma += *i;
	 }
	 return suma;
       }

   Només cal recordar de fer servir iteradors ``const`` amb paràmetres
   d'entrada (que portin ``const`` i ``&``).


.. exercici::

   Declaracions de llistes::

      list<float> l(40);
      list<Punt2D> lpunts;
      list<char> lch(100, 'X');
      list< vector<int> > lv;

   En la última declaració, és important deixar un espai entre l'últim
   '``>``\' i el penúltim, ja que si no, el compilador pensa que fem
   servir l'operador '``>>``\'[6~.

.. exercici::

   La llista conté {-3, 3, 5, 4}.

.. exercici::

   ::

     list<int> l;
     for (int k = 1; k <= 10; k++) {
       if (k % 2 == 0)
         l.push_back(k);
       else
         l.push_front(k);
     }


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


.. exercici::

   ::

     void afegeix(list<int>& L, int k) {
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

.. exercici::
  
   El codi mostrarà per pantalla::
  
     Azrael


.. exercici::
   
   L'acció seria::

     void opera(stack<int>& s, char op) {
       int b = s.top(); s.pop();
       int a = s.top(); s.pop();
       int res;
       switch (op) {
         case '+': res = a + b; break;
         case '-': res = a - b; break;
         case '*': res = a * b; break;
         case '/': res = a / b; break;
       }      
       s.push(res);
     }

.. exercici::
   ::

     (3 * (3 + 3))
     (3 - (4 + (5 * 1)))
     ((1 + 2) - 3)
     (((5 * 4) + 100) - ((2 * 3) * 10))

.. exercici::
   
   El programa sencer quedarà així::

      #include <stack>
      #include <sstream>
      #include <iostream>
      using namespace std;
      
      bool es_enter(string s, int& val) {
        // ...
      }
      
      void opera(stack<int>& s, char op) {
        // ...
      }
      
      int main() {
        stack<int> P;
        string s;
        cin >> s;
        while (s != ".") {
          int x;
          if (es_enter(s, x)) {
	    P.push(x);
	  }
          else {
	    opera(P, s[0]);
	  }
          cin >> s;
        }
        if (!P.empty())
          cout << P.top() << endl;
      }

.. exercici::

   La sortida serà::

      5 4 5 6 7 11

.. problema::

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

