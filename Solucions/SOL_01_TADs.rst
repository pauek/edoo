
=========================
Tipus Abstractes de Dades
=========================

.. exercici::

   ::
    
     #include <iostream>
     using namespace std;
     // Suposem que tenim disponible el TAD FILE

     int main() {
       FILE f;
       obre(f, "hola.txt", "w");
       esborra(f);
       escriu(f, "Hola, món!");
       tanca(f);
     }

.. exercici::
   ::

     // per al tipus Interval1
     double inici(const Interval1& I) {
       return I.ini;
     }

     double final(const Interval2& I) {
       return I.fin;
     }

     // per al tipus Interval2
     double inici(const Interval2& I) {
       return I.ini;
     }      

     double final(const Interval2& I) {
       return I.ini + I.llarg;
     }

.. exercici::
   ::

     // per al tipus Interval1
     double longitud(const Interval1& I) {
       return I.fin - I.ini;
     }

     double longitud(const Interval2& I) {
       return I.llarg;
     }

.. exercici::
   ::
    
      struct tVector2D {
        double x, y;
      };
      
      double coord_x(const tVector2D& v) {
        return v.x;
      }
      
      double coord_y(const tVector2D& v) {
        return v.y;
      }
      
      void posa_x(double x, tVector& v) {
        v.x = x;
      }
      
      void posa_x(double y, tVector& v) {
        v.y = y;
      }

      double longitud(const tVector2D& v) {
        return sqrt( v.x*v.x + v.y*v.y );
      }
      
      double angle(const tVector2D& v) {
        double ang = 0.0;
        if ( v.x == 0.0 ) {
          if ( v.y > 0.0 ) ang = M_PI_2;
          if ( v.y < 0.0 ) ang = 3. * M_PI_2;
        }
        else {
          ang = atan( v.y / v.x );
      
          if ( v.x < 0.0 ) 
            ang += M_PI;
          else if ( v.y < 0.0 ) 
            ang += M_TWO_PI;
        }
        return ang;
      }
     
.. exercici::

   Aquest exercici es pot resoldre bàsicament de dues maneres (i
   potser alguna més). La primera és fer servir un punt per a una
   cantonada i l'amplada i alçada del rectangle::

      struct tRectangle2D {
        double x, y; // Cantonada a baix a l'esquerra 
        double ample, alt;
      };
      
      double amplada(const tRectangle2D& r) {
        return r.ample;
      }
      
      double alsada(const tRectangle& r) {
        return r.alt;
      }
      
      double desplaça(tRectangle2D& r, double x, double y) {
        r.x += x;
        r.y += y;
      }
      
      bool a_dins(tRectangle2D& r, double x, double y) {
        double dx = x - r.x, dy = y - r.y;
        return dx > 0.0 && dx < r.ample && dy > 0.0 && dy < r.alt;
      }
      
      // altres funcions
      double area(const tRectangle2D& r) {
        return r.ample * r.alt;
      }

  L'altra manera seria emmagatzemar els dos punts amb coordenades (y
  fent servir cantonades oposades per no repetir coordenades, que de
  fet són 4)::

      struct tRectangle2D {
        double x1, y1; // Cantonada baix-esquerra 
        double x2, y2; // Cantonada dalt-dreta
      };
      
      double amplada(const tRectangle2D& r) {
        return r.x2 - r.x1;
      }
      
      double alsada(const tRectangle& r) {
        return r.y2 - r.y1;
      }
      
      double desplaça(tRectangle2D& r, double x, double y) {
        r.x1 += x; r.y1 += y;
        r.x2 += x; r.y2 += y;
      }
      
      bool a_dins(tRectangle2D& r, double x, double y) {
        return dx > r.x1 && dx < r.x2 && 
	       dy > r.y1 && dy < r.y2;
      }
      
      // altre funcions
      double area(tRectangle2D& r) {
        return amplada(r) * alsada(r);
      }
        
.. exercici::

   Les operacions del TAD serien::

     void inicialitza(Hora& h, int hora, int minuts, int segons);
     int hores(const Hora& h);
     int minuts(const Hora& h);
     int segons(const Hora& h);
     void suma_segons(Hora& h, int n);
     bool anterior(const Hora& h1, const Hora& h2);

   Ara fem un programa que faci servir aquestes operacions::

     #include <iostream>
     using namespace std;

     int main() {
       Hora h1, h2;
       int a, b, c;

       // Llegim dues hores
       cin >> a >> b >> c; 
       initialitza(h1, a, b, c);
       cin >> a >> b >> c;
       inicialitza(h2, a, b, c);

       // Les comparem
       if (anterior(h1, h2)) {
         cout << "La primera és anterior" << endl;
       }

       // Li sumem 1000 segons a la primera i la mostrem
       suma_segons(h, 1000);
       cout << hores(h) << ':' 
            << minuts(h) << ':' 
	    << segons(h) << endl;
     }

.. exercici::

   Tal com en l'exercici anterior, pensem unes operacions sobre una
   estructura ``CompteBancari``::

     inicialitza(CompteBancari& C, 
     		 int num_ident, string DNI, float diners);
     numero_identificacio(const CompteBancari& C);
     double balans(const CompteBancari& C);
     string titular(const CompteBancari& C);
     void ingressa(CompteBancari& C);
     bool retira(CompteBancari& C); // retorna true si s'ha pogut
     void mostra(CompteBancari& C); // mostra per pantalla

   Ara implementem un programa que el faci servir::

      string comanda() {
        string cmd;
        cout << "Comanda [surt, ingressa, retira, mostra]: ";
        cin >> cmd;
        return cmd;
      }
      
      double llegeix_quant(string verb) {
        double q;
        cout << "Entra la quantitat a " << verb << ": ";
        cin >> q;
        return q;
      }
      
      int main() {
        tCompteBancari compte;
        inicialitza(compte, 12345, "44332255K", 100.0);
      
        string cmd;
        cmd = comanda();
        while (cmd != "surt") 
        {
          if (cmd == "ingressa") {
            double q = llegeix_quant("ingressar");
            ingressa(compte,q);
          } 
          else if (cmd == "retira") {
            double q = llegeix_quant("retirar");
            if (retira(compte, q)) {
              mostra(compte);
            }
            else {
      	      cout << "No hi ha prous diners!" << endl;
            }
          }
          else if (cmd == "mostra") {
            mostra(compte);
          }
          cmd = comanda();
        }
        cout << "Adéu!" << endl;
      }

.. exercici::

   Per implementar la funció ``mostra`` hem de fer dues coses:
   declarar-la a l'estructura (afegim només aquesta línia a
   l'estructura que ja hi havia)::

     struct Interval {
       // ...
       void mostra() const;
     };

   i després implementar-la (al costat de les altres)::
    
     void Interval::mostra() const {
       cout << '(' << ini << ", " << fin << ')' << endl;
     }

.. exercici::

   Tal com l'exercici anterior, hem de declarar primer la funció::

     struct Interval {
       // ...
       bool contingut(double x) const;
     };

   És important veure que el paràmetre ``x`` es rebrà igualment (el
   que desapareix és l'interval), ja que per saber si un valor està en
   un interval, necessitem l'interval (implícit) i el punt (``x``). El
   ``const`` passa a la funció membre. La implementació és::

     bool Interval::contingut() const {
       return x > ini && x < fin;
     }

   Cal recordar el const al final (perquè sigui *igual* que la
   declaració).

.. exercici::
   ::
  
     struct Image {
       int pixels[100][100];
       
       void fill(int val);
       void set_pixel(int x, int y, int val);
       int  get_pixel(int x, int y) const;
       void bitblt(int ini_x, int ini_y, const Image& Orig,
                   int ample, int alt);
     };

     void Image::fill(int val) {
       for (int i = 0; i < 100; i++) 
         for (int j = 0; j < 100; j++)
           pixels[i][j] = val;
     }

     void Image::set_pixel(int x, int y, int val) {
       pixels[x][y] = val;
     }
 
     int Image::get_pixel(int x, int y) const {
       return pixels[x][y];
     }
 
     void Image::bitblt(int ini_x, ini_y, const Image& Orig, 
                        int ample, int alt)
     {
       for (int i = 0; i < ample; i++)
         for (int j = 0; j < alt; j++)
            pixels[ini_x + i][ini_y + j] = Orig.pixels[i][j];
     }

.. exercici::

   Com que la imatge té un tamany fixe de 100 per 100, haurem de posar
   això al programa directament. Suposem que el valor de cada píxel
   està entre 0 i 255 (per simplificar)::

     void escriu_imatge(const Imatge& I, string fitxer) {
       ofstream fout(fitxer.c_str());
       // Capçalera
       fout << "P2" << endl << "100 100" << endl << 255 << endl;
       // Cos de la imatge
       for (int i = 0; i < 100; i++) {
         for (int j = 0; j < 100; j++) {
	   fout << I.get_pixel(i, j) << ' ';
	 }
	 fout << endl;
       }
     }

   L'important d'aquesta funció és la crida "``I.get_pixel(i, j)``",
   que s'ha de fer amb la notació de tuples.

.. exercici::

   Aquest exercici no té una solució concreta...

.. exercici::
   
   (Nota, la funció  ``getline`` rep un punter i potser aquest tema
   encara no està explicat, perdoneu l'inconvenient...)
   ::

      #include <iostream>
      #include <string>
      #include <fstream>
      using namespace std;
      
      int main() {
        string paraula, fitxer, linia;
        cout << "Paraula? ";
        cin >> paraula;
        cout << "Fitxer? ";
        cin >> fitxer;
        cout << endl;
        
        ifstream fin(fitxer.c_str());
        int nlin = 0;
        while (!fin.eof()) {
          char L[1000];
          fin.getline(L, 1000);
          string linia(L);
          if (linia.find(paraula) != string::npos) {
            cout << nlin << ": " << linia << endl;
          }
          nlin++;
        }
      }

.. problema::

   El TAD ``Organisme`` tindrà les següents operacions:

   - Llegir un organisme fent servir un ``istream``.

   - Copiar les dades d'un organisme a un altre.

   - Mirar si la mesura d'un organisme és major que la d'un altre.

   - Determinar si un organisme és l'últim.

   - Escriure les dades d'un organisme a un ``ostream``.

   La implementació del TAD ``Organisme`` mantenint el fet que és un
   ocell en el programa inicial seria::

     struct Organisme {
       string codi, especie;
       float pes;

       void llegir(istream& i);
       void copiar(const Organisme& o);
       bool menor_que(const Organisme& o) const;
       bool ultim() const;
       void escriure(ostream& o) const;
     };

     void Organisme::llegeix(istream& i) {
       i >> codi >> especie >> pes;
     }     

     void Organisme::copia(const Organisme& o) {
       codi = o.codi;
       especie = o.especie;
       pes = o.pes;
     }

     void Organisme::menor_que(const Organisme& o) const {
       return pes < o.pes;
     }

     bool Organisme::ultim() const {
       return codi == "FI" && especie == "FI" && pes == 0.0;
     }

     void Organisme::escriu(ostream& o) const {
       o << "Codi: " << codi << ' '
         << "Especie: " << especie << ' '
	 << "Pes: " << pes << endl;
     }
       
   En aquesta implementació hi ha molts detallets que s'han de quadrar
   correctament. En concret, l'ús del ``const`` és important. Quan
   llegim un ``Organisme``, per exemple, l'hem de modificar, però quan
   l'escrivim no. Quan en fem una còpia, l'orígen no canvia però el
   destí si, etc.

   Amb aquesta implementació de ``Organisme`` la funció ``main`` (que
   aniria a continuació) queda així::
   
      int main() {
        Organisme o, max;

	o.llegeix(cin);
	max.copia(o);
	while (!o.ultim()) {
	  if (max.menor_que(o)) {
	    max.copia(o);
	  }
	  o.llegeix(cin);
	}
	max.escriu(cout);
      }

   Molt més escueta però encara fa el càlcul d'abans. Fins aquí tenim
   el programa original de l'enunciat però fet d'una altra manera. 

   Ara implementem les modificacions que permeten treballar amb les
   formigues. Bàsicament es tracta de refer els detalls del TAD
   organisme, i veure la funció ``main`` no canviarà (això és el que
   volíem, aïllar la funció ``main``)::

     struct Organisme {
       int num, minuts;
       string casta;

       // les mateixes declaracions que abans, ja
       // que el TAD és constant, el que canvia és la 
       // implementació
     };

     void Organisme::llegeix(istream& i) {
       i >> num >> casta >> minuts;
     }     

     void Organisme::copia(const Organisme& o) {
       num = o.num;
       casta = o.casta;
       minuts = o.minuts;
     }

     void Organisme::menor_que(const Organisme& o) const {
       return minuts < o.minuts;
     }

     bool Organisme::ultim() const {
       return num == 0 && casta == "FI" && minuts == 0;
     }

     void Organisme::escriu(ostream& o) const {
       o << "Formiga: " << num << ' '
         << "Casta: " << casta << ' '
	 << "Activitat: " << minuts << endl;
     }
