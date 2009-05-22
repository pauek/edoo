
=================================
Piles, Cues i Taules Associatives
=================================

.. -------------------------------------------------------------------
.. Piles i Cues
.. -------------------------------------------------------------------

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

.. -------------------------------------------------------------------
.. Maps
.. -------------------------------------------------------------------

.. exercici::
   ::

      pair<float,bool> p;
      pair<int,int> p2(-1, 13);
      
.. exercici::
   ::

      vector< pair<int,char> > v(3);

      v[0].first = 'a'; // una manera d'omplir cada parell
      v[0].second = 1; 

      v[1] = make_pair('b', 2); // una altra manera
      v[2] = make_pair('c', 3);

   És important recordar que va un espai entre els ``'>'`` de
   ``vector`` i ``pair``.

.. exercici::
   ::
   
      void esborra_negatius(const list< pair<string,int> >& L) {
        list< pair<string,int> >::iterator i = L.begin();
	while (i != L.end()) {
	  if (i->second < 0) {
	    i = L.erase(i);
	  }
	  else i++;
	}
      }

.. exercici::
   ::
   
      resultat_partit(make_pair("Matalascanyas", 5),
                      make_pair("Zurrianico", 1));


.. exercici::
   
   11 vegades, ja que 2048 és 2 elevat a 11.

.. exercici::

   Degut a què 512 és 2 elevat a 9, unes 9 vegades (aproximat).

.. exercici::

   log2(n) vegades, o equivalentment, O(log n) vegades.

.. exercici::
   ::

     map<string,double> M;
     M["pi"] = 3.14159;
     M["e"] = 2.71828;
     M["arrel2"] = 1.41421;

   També es pot fer::

     map<string,double> M;
     M.insert(make_pair("pi", 3.14159));
     M.insert(make_pair("e", 2.71828));
     M.insert(make_pair("arrel2", 1.41421));

.. exercici::

   Per fer aquest problema, haurem de fer servir un ``map`` que ens
   emmagatzemi l'histograma. Les claus seran els enters que han sortit
   a la seqüència, i els valors associats a cada clau els comptadors
   que ens diuen quantes vegades ha sortit cada element.
   ::
    
      #include <fstream>                                        
      #include <iostream>				    
      #include <map>					    
      using namespace std;				    
      						    
      int main() {					    
        map<int,int> H;				    
        ifstream fin("enters.txt");			    
        int n;					    
      						    
        // Llegeix les dades				    
        fin >> n;					    
        while (!fin.eof()) {				    
          H[n]++;					    
          fin >> n;					    
        }						    
      						    
        // Mostra l'histograma			    
        map<int,int>::iterator i;			    
        for (i = H.begin(); i != H.end(); i++)	    
          cout << i->first << ' ' << i->second << endl;   
      }

   La instrucció més important del programa és ``H[n]++`` que té, de
   fet, una doble funció. Quan un enter surt per primera vegada, el
   fet d'accedir a ``H[n]`` crea un ``pair`` buit amb l'enter i un
   comptador a 0, i tot seguit s'incrementa. Quan l'enter ja existia,
   ``H[n]`` retorna el comptador en sí i s'incrementa normalment. La
   mateixa instrucció ens serveix per crear nous elements i per
   incrementar els que ja teníem.

.. exercici::

   Aquest exercici es resol de forma molt semblant a l'anterior. Ara
   les fruites seran la clau i el valor que acompanya cada clau és un
   comptador de les unitats de fruita.
   ::

     #include <fstream>
     #include <iostream>
     #include <map>
     using namespace std;

     int main() {
       map<string,int> F; // per comptar fruites
       ifstream fin("fruites.txt");
       string fruita;
       int quantitat;
  
       // Llegim les dades
       fin >> fruita >> quantitat;
       while (!fin.eof()) {
         F[fruita] += quantitat;
         fin >> fruita >> quantitat;
       }
  
       // Mostrem els resultats
       int total = 0;
       map<string,int>::iterator i;
       for (i = F.begin(); i != F.end(); i++) {
         total += i->second;
         cout << i->first << ' ' << i->second << endl;
       }
       cout << "Total: " << total << endl;
     }

   En aquest programa es compleix un cop més que la instrucció
   ``F[fruita] += quantitat`` fa dos funcions: inicialitzar les noves
   fruites a la quantitat que s'observa per primera vegada i sumar una
   quantitat si ja hi són. El codi és, de fet, equivalent a::

      map<string,int>::iterator i = F.find(fruita);
      if (i != F.end())
        i->second += quantitat;
      else 
        F.insert(make_pair(fruita, quantitat));

   En aquesta versió la inserció dels elements que no existeixen es fa
   explícitament.


.. -------------------------------------------------------------------
.. Problemes
.. -------------------------------------------------------------------


.. problema::

   .. literalinclude:: src/08_Piles_Cues_i_Maps/word_frequency.cpp


.. problema::

   .. literalinclude:: src/08_Piles_Cues_i_Maps/telephone.cpp

.. problema::

   .. literalinclude:: src/08_Piles_Cues_i_Maps/metro.cpp

.. problema::

   .. literalinclude:: src/08_Piles_Cues_i_Maps/port_mapping.cpp
