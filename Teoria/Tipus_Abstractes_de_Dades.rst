
.. tema:: tad

=========================
Tipus Abstractes de Dades
=========================

.. rubric:: Objectius

- Descriure els avantatges d'una barrera d'abstracció en un programa.
- Utilitzar correctament les operacions d'un tipus abstracte de dades donat.
- Implementar les operacions d'un tipus abstracte de dades a partir de
  la seva especificació.
- Especificar de forma aproximada un conjunt d'operacions per a un
  tipus abstracte de dades.

.. contents:: Contingut 
   :depth: 2
   :local:

Dificultats en la construcció de programes
------------------------------------------

Complexitat
"""""""""""

Quan el tamany del projecte creix, la creació de programes es fa molt
complexa. Una de les habilitats més importants en informàtica té a veure,
precisament, amb controlar la complexitat dels sistemes que es
construeixen. Per fer-ho, la majoria de tècniques tenen a veure amb
modularitzar el problema i així fer-ne una "partició" que ens permeti
treballar sobre cada una de les parts (els mòduls) sense por de fer malbé el
sistema sencer. 

La creació de mòduls té com a conseqüència el fet de poder atribuir
errors en el funcionament d'un programa a parts concretes del seu codi
de forma ràpida i eficaç. Si l'estructura del programa és poc modular,
certs errors poden ser molt difícils de trobar i corregir
(principalment perquè no se sap a quina part del sistema s'han
produit).

Reaprofitament
""""""""""""""

Per altra banda, la creació de mòduls ben aïllats té l'avantatge de
permetre crear nova funcionalitat en molt menys temps. Els mòduls
existents combinats ens donen accés a funcions molt més complexes amb
poc esforç de programació. L'absència de modularitat fa que quan un
programa necessita una modificació, aquesta sigui molt més difícil
d'integrar (o fins i tot infactible).

Tipus Abstractes de Dades
-------------------------

Un Tipus Abstracte de Dades (TAD) es defineix amb un conjunt
d'operacions (en programació, doncs, un conjunt d'accions i funcions)
que ens permeten manipular un cert objecte, *sense necessitat de saber
quin és el format intern de l'objecte*. L'especificació del TAD
menciona les operacions d'aquest tipus però en cap moment es diu com
estan implementades exactament. Malgrat aquesta mancança, l'usuari
d'un TAD disposa de la informació suficient per a utilitzar el TAD en
tots els supòsits possibles.

Un exemple de TAD pot ser un fitxer. Amb aquest objecte volem fer
almenys 4 operacions: obrir-lo, tancar-lo, llegir dades i escriure
dades. Opcionalment, es poden considerar també altres operacions com
anar a una posició concreta del fitxer, i esborrar-ne el
contingut. Suposem, doncs, que disposem d'un ``struct`` que es diu
``FILE``, declarat com::

   struct FILE {
     // ...
   };

però del qual no en sabem res (no sabem com està implementat, per tant
no sabem els camps de l'estructura). Les operacions sobre el fitxer
esmentades serien, doncs::

   void obre(FILE& f, string nom_fitxer, string mode);
   void tanca(FILE& f);
   void escriu(FILE& f, string dades);
   void llegeix(FILE& f, string& dades);
   void rebobina(FILE& f, int pos);
   void esborra(FILE& f);

Totes aquestes operacions reben una variable de tipus ``FILE`` com a
paràmetre, i hem de suposar que realitzen modificacions a les dades
que conté, però és important veure que amb aquestes funcions manipulem
fitxers de forma *abstracta* sense saber exactament quins són els
detalls de la implementació. Això no suposa un problema, però, ja que
amb aquestes operacions podem fer programes que manipulin fitxers amb
tota comoditat.

.. exercici::

   Fent servir el TAD ``FILE`` (fes la suposició que disposes del TAD
   implementat), fes un programa (bàsicament, la funció ``main``) que
   escrigui "Hola, món!" en el fitxer ``hola.txt``. Quan obris el
   fitxer, fes-ho amb el *mode* ``"w"`` d'escriptura. Esborra el
   contingut del fitxer per si ja existia.

   .. solucio::

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

Barreres d'abstracció
"""""""""""""""""""""

Aquesta ocultació explícita dels detalls de la implementació és molt
important. Per començar, ens permet treballar sense distracció. Si no
coneixem els detalls, no ens hem de preocupar més que per entendre com
fer servir les funcions que manipulen fitxers segons la lògica
subjacent i això és tot. Tenir menys coses al cap facilita la nostra
tasca a l'hora de programar. 

Per altra banda, el fet de fer abstracció i seleccionar les operacions
més representatives d'un objecte crea un aïllament entre les dues
parts del codi. Aquest aïllament té un nom: una *barrera
d'abstracció*.

Aquest nom té a veure amb la separació implícita que es produeix entre
les dues bandes de la barrera: el codi que **utilitza** les accions i
funcions del TAD ``FILE``, i el codi que **implementa** les operacions
de la barrera. El poder d'aïllament de la barrera es pot veure en el
moment en què volem introduir canvis en un programa.

Avalantxes de canvis
''''''''''''''''''''

Quan en un programa ens plantegem algun canvi de funcionalitat, aquest
canvi en principi afectarà una part petita del programa. Però moltes
vegades, aquests canvis ens obliguen a realitzar canvis a altres parts
del programa, i aquest nous canvis en generen de nous de forma que es
produeix una avalantxa de modificacions que acaben afectant a tot el
programa. El cost de modificar un programa pot créixer molt ràpidament
quan el programa té certa envergadura.

El fet que hi hagi una avalantxa és per l'existència de
dependències. Certes parts d'un programa depenen molt estretament
d'altres parts i si fem canvis en unes, les altres també han de
canviar. Si ens imaginem les modificacions inicials d'un programa com
un petit foc, es podria dir que el foc es propagarà pel programa quan hi
ha una relació molt estreta entre les diferents parts del programa.

Exemple: intervals
''''''''''''''''''

Un exemple pot ajudar a aclarir-ho. Suposem que tenim el següent
tipus::

   struct Interval1 {
     double ini, fin; // inici i final
   };

i en un cert programa, tenim les següents funcions::
  
   void mostra_interval_1(const Interval1& I) {
     cout << '(' << I.ini << ", " << I.fin << ')';
   }

   bool contingut_1(const Interval1& I, double x) {
     return x > I.ini && x < I.fin;
   }
   
Per raons que ara no venen al cas, imaginem que volem canviar la
implementació de l'interval de forma que s'emmagatzemi la informació
de la següent forma::

  struct Interval2 {
    double ini, llarg; // inici i llargària
  };

Ara el camp ``fin`` del nou interval serà implícit, perquè es pot
calcular com al suma de ``ini`` i ``llarg``. En l'interval anterior la
longitud era implícita, i s'havia de calcular com la resta entre el
``fin`` i l'``ini``.

La pregunta és, doncs, quins canvis s'han d'introduir en les funcions
``mostra_interval_1`` i ``contingut_1`` per tal que el programa
segueixi funcionant correctament? La resposta és que s'han de
transformar en les següents::

   void mostra_interval_2(const Interval2& I) {
     cout << '(' << I.ini << ", " << I.ini + I.llarg << ')';
   }

   bool contingut_2(const Interval2& I, double x) {
     return x - I.ini < I.llarg;
   }

Clarament, les dues funcions han hagut de canviar. Per tant, les
funcions ``mostra_interval_1`` i ``contingut_1`` tenen una dependència
amb l'estructura interna de l'objecte ``Interval1``, i els canvis que
voliem fer a ``Interval1`` s'han propagat fins a elles. De fet, també
tenen aquesta dependència les funcions ``mostra_interval_2`` i
``contingut_2`` amb la nova estructura ``Interval2``; si volem tornar
a la implementació original hem de tornar a canviar la implementació
d'aquestes funcions.

Com hauriem de fer-ho perquè els canvis al tipus ``Interval`` no
afectin la implementació de ``mostra_intveral`` i ``contingut``??

La resposta és: afegint un conjunt de funcions *intermitges*, que creen
una barrera d'abstracció. Aquestes funcions seràn les següents::

  double inici(const Interval& I);
  double final(const Interval& I);

La implementació d'aquestes funcions és irrellevant, l'important és
que hem fet abstracció del que és essencial d'un interval (l'inici i
el final). És important que el codi que utilitza intervals (típicament
en moltes parts del programa) faci servir aquestes funcions.

La nova implementació de ``mostra_interval`` i ``contingut`` és, doncs::

   void mostra_interval(const Interval& I) {
     cout << '(' << inici(I) << ", " << final(I) << ')';
   }

   bool contingut(const Interval& I) {
     return x > inici(I) && x < final(I);
   }

Com es veu afectat el programa, ara, quan volem fer canvis a la
representació interna de l'interval? 

Doncs només es veuen afectades les implementacions de les funcions de
la barrera, en aquest cas ``inici`` i ``final``. Si tot el programa
utilitza aquestes dues funcions, els canvis a la implementació de
``Interval`` queden acotats, el "foc" no es propaga més que fins a la
pròpia barrera.

Les barreres d'abstracció són, doncs, com **tallafocs**. Les barreres
protegeixen la implementació d'un cert TAD de forma que si la seva
implementació canvia, aquests canvis no es propaguen per tot el
programa. 

Cost d'implementar TADs
^^^^^^^^^^^^^^^^^^^^^^^

És veritat que això afegeix un nivell més d'indirecció. En comptes
d'accedir directament a l'inici o al final d'un interval, cridem a
unes funcions que ens els proporcionen indirectament. Les funcions
intermitges tenen un petit cost, ja que hem de fer una mica més de
codi. Però aquesta estructura ens permet créixer de forma sòlida, i
ens surt a compte quan tot un programa necessita manipular
intervals. Aquest cost se sol assumir fins i tot quan estem al
principi de la construcció del programa, en què gairebé no hi ha codi
que faci servir intervals, per exemple, però anticipem la possibilitat
que finalment es facin servir molt. Aquesta precaució ens permetrà
després poder fer créixer el programa sense obstacles.

.. exercici::

   Implementa les funcions ``inici`` i ``final`` per als tipus
   ``Interval1`` i ``Interval2``.

   .. solucio::
   
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
    
   Implementa una nova funció del TAD ``longitud`` per a ``Interval1``
   i ``Interval2``.

   .. solucio::

      ::
   
        // per al tipus Interval1
        double longitud(const Interval1& I) {
          return I.fin - I.ini;
        }
   
        double longitud(const Interval2& I) {
          return I.llarg;
        }

.. exercici::

   Considera les següents declaracions incomplertes::

     struct tVector2D {
       // ...
     };
     
     double  longitud(const tVector2D& v);
     double  coord_x(const tVector2D& v);
     double  coord_y(const tVector2D& v);
     double  angle(const tVector2D& v);
     double  posa_x(double x, tVector2D& v);
     double  posa_y(double y, tVector2D& v);

   La declaració de l'estructura ``tVector2D`` i les declaracions de
   les funcions defineixen un TAD per a un vector 2D. Completa, doncs,
   la implementació d'aquest TAD.
  
   *Nota: La implementació correcta de la funció ``angle`` és
   notablement més llarga que la de les altres funcions.*

   .. solucio::

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

   Considera les declaracions següents::

    struct Rectangle2D {
      // ...
    };
    
    double amplada(const Rectangle2D& r);
    double alsada(const Rectangle2D& r);
    void   desplasa(Rectangle2D& r, double x, double y);
    bool   a_dins(const Rectangle2D& r, double x, double y);
    // ...   

   La funció ``a_dins`` ha de retornar ``true`` si el punt
   ``x``, ``y`` donat es troba dins del rectangle.

   Implementa aquest TAD escollint primer una representació (els camps
   de l'estructura ``Rectangle2D``) i implementant les funcions
   donades.  Pensa altres funcions útils per a aquest TAD i
   implementa-les.

   .. solucio::

      Aquest exercici es pot resoldre bàsicament de dues maneres (i
      potser alguna més).

      La primera és fer servir un punt per a una cantonada i l'amplada
      i alçada del rectangle::
   
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
         
         void desplasa(tRectangle2D& r, double x, double y) {
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
         
         void desplasa(tRectangle2D& r, double x, double y) {
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

   Pensa el conjunt d'operacions que són necessàries per manipular
   dades temporals (hores, minuts i segons) i escriu les capçaleres de
   les funcions que implementarien aquestes operacions. Anomena el TAD
   ``Hora``.
  
   Fes un programa que utilitzi el TAD i que faci servir totes les
   operacions disponibles.

   .. solucio::

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
  
   En un programa desenvolupat per a un banc, es necessiten manipular
   les dades de comptes bancaris. Els comptes bancaris tenen un número
   d'identificació, un titular (el seu DNI), i permeten dipositar
   diners i també fer reintegraments.  Dissenya un TAD
   ``CompteBancari`` per poder-lo utilitzar en aquest programa.

   Implementa també un programa principal (la funció ``main``) que
   creï un compte i faci manipulacions amb ell per tal de posar a
   prova el TAD.

   .. solucio::

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


Funcions membre
---------------

C++ és un llenguatge orientat a objectes. Això significa que en C++ hi
ha molts mecanismes que recolzen el treball amb TADs directament. Un
d'aquests mecanismes són les *funcions membre*. Fins ara, hem vist que
un ``struct`` defineix una tupla, un tipus que consisteix en agrupar
diferents dades. Així com els camps d'una estructura són els membres
de dades, podem tenir membres que siguin funcions::

   struct Interval {
     double ini, fin;
   
     double inici() const;
     double final() const;
     double longitud() const;
   };

En aquesta declaració, hem afegit a la declaració dels camps de la
tupla les 3 funcions que formen part de la barrera d'abstracció del
TAD ``Interval`` (hem afegit al TAD, també, la funció
``contingut``). El fet de declarar aquestes funcions **a dins** de la
tupla té conseqüències importants:

- El primer paràmetre d'aquestes funcions ha desaparegut. Pel fet de
  posar les funcions com a membres de l'estructura, se suposarà que
  *sempre* manipulen un ``Interval``, que serà implícit.

- El ``const`` que acompanyava al primer paràmetre ara està després
  dels parèntesis dels paràmetres (això és una conseqüència del punt
  anterior).

- La forma de cridar les funcions esdevé la forma típica d'accés a
  tuples, fent servir un punt "``.``".

- La *definició* d'aquestes funcions serà diferent. S'ha d'utilitzar
  un operador especial "``::``" per indicar que les funcions pertanyen
  a ``Interval``.

Vegem, primer, la implementació de les funcions membre::

  double Interval::inici() const {
    return ini;
  }

  double Interval::final() const {
    return fin;
  }

  double Interval::longitud() const {
    return fin - ini;
  }

Hi ha vàries novetats:

- Les definicions porten el prefix "``Interval::``". Això indica la
  pertanyença a la tupla ``Interval``.

- L'accés als camps de la tupla (``ini`` i ``fin``) es fa **sense**
  cap prefix, amb el nom directament (no hi ha cap punt davant).

- Apareix el ``const`` de la declaració un altre cop darrere els
  paràmetres i abans del cos de la funció en els tres cassos.

Totes aquestes novetats s'expliquen per la mateixa raó, que es detecta
quan veiem com es fan servir les funcions membre. Vegem la
implementació de ``mostra_interval`` amb les funcions membre::

  void mostra_interval(const Interval& I) {
    cout << '(' << I.inici() << ", " << I.final() << ')';
  }

La novetat són les crides ``I.inici()`` i ``I.final()``. Aquesta
notació és la que coneixem per a tuples aplicada a
funcions. L'interessant és:

.. important:: 

   Les funcions membre d'una tupla sempre es criden obligatòriament
   sobre un objecte i és aquest l'objecte que esdevé implícit en la
   seva definició

Per tant, donat que quan cridem una funció membre ho hem de fer sobre
un objecte, aquest és un *paràmetre implícit* de la funció membre (el
que semblava desaparegut) i quan accedim als camps ``fin`` en una
funció membre directament ja sabem a quins camps ens estem referint:
als del paràmetre implícit.

.. exercici::

   Implementa la funció ``mostra_interval`` com a funció membre de
   ``Interval`` (ara formarà part del TAD, doncs). Canvia-li el nom a
   simplement ``mostra`` (donat que sempre es cridarà a sobre un
   interval).

   .. solucio::

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

   Implementa la funció ``contingut`` també com a funció membre de
   ``Interval``, tal com en l'exercici anterior. Fes especial atenció
   als paràmetres que ha de rebre.

   .. solucio::

      Tal com l'exercici anterior, hem de declarar primer la funció::
   
        struct Interval {
          // ...
          bool contingut(double x) const;
        };
   
      És important veure que el paràmetre ``x`` es rebrà igualment (el
      que desapareix és l'interval), ja que per saber si un valor està en
      un interval, necessitem l'interval (implícit) i el punt (``x``). El
      ``const`` passa a la funció membre. La implementació és::
   
        bool Interval::contingut(double x) const {
          return x > ini && x < fin;
        }
   
      Cal recordar el const al final (perquè sigui *igual* que la
      declaració).
   
.. exercici::

   Transforma el codi següent de tal manera que faci servir la mateixa
   estructura però les operacions del TAD siguin *funcions membre*::

     struct Image {
       int pixels[100][100];
     };
 
     void fill(Image& I, int val) {
       for (int i = 0; i < 100; i++) 
         for (int j = 0; j < 100; j++)
           I.pixels[i][j] = val;
     }
 
     void set_pixel(Image& I, int x, int y, int val) {
       I.pixels[x][y] = val;
     }
 
     int get_pixel(const tImage& I, int x, int y) {
       return I.pixels[x][y];
     }
 
     void bitblt(Image& Dest, int ini_x, ini_y,
                 const Image& Orig, int ample, int alt)
     {
       for (int i = 0; i < ample; i++)
         for (int j = 0; j < alt; j++)
           Dest.pixels[ini_x + i][ini_y + j] = Orig.pixels[i][j];
     }

   [dummy]

   .. solucio::
      
      El TAD imatge s'implementa així::
         
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

      La funció ``bitblt`` no porta ``const`` darrere perquè el
      paràmetre original ``Dest`` no era constant, ja que ``bitblt``
      és una acció que modifica la imatge destí ``Dest``, i aquest
      primer paràmetre s'ha convertit en "el paràmetre implícit". 

.. exercici::

   Fes una funció ``escriu_imatge`` que escrigui en un fitxer PGM una
   imatge del tipus ``Image`` de l'exercici anterior, fent servir
   únicament les seves funcions membre. La funció ha de rebre com a
   paràmetres la imatge i el nom del fitxer a on s'ha de guardar la
   informació.

   .. solucio::
   
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
   
   Consulta la documentació a Internet (per exemple
   `http://www.cplusplus.com/reference/
   <http://www.cplusplus.com/reference/>`_) i busca les funcions
   membre de ``iostream`` (semblants a les esmentades en l'exemple de
   ``FILE``). En particular, busca ``eof()``, ``getline()`` i
   ``get()``, i mira si hi ha alguna funció per canviar el número de
   decimals que apareixen quan es mostra un nombre real.

   .. solucio::

      Aquest exercicio no té una solució concreta...

.. exercici::

   Consulta al documentació de ``string`` (en particular la funció
   ``find``). Fes un programa que demani una paraula i el nom d'un
   fitxer i després mostri totes les línies del fitxer a on apareix la
   paraula (fes servir ``getline`` per llegir el fitxer línia a
   línia). Aquest programa, en UNIX (i Linux) té per nom ``grep``.

   .. solucio::

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
   
   
Problemes
---------

.. problema::
   
   Un grup de biòlegs que es dedica a estudiar poblacions d'animals
   disposa d'un programa per facilitar la seva tasca. El programa rep
   una seqüència de les dades de certs ocells i al final mostra el que
   té el pes més gran. El ocells tenen 3 dades: el codi de l'anella,
   l'espècie i el pes. La seqüència acaba amb un sentinella que té les
   dades: ``FI FI 0``. El programa és el següent::

     #include <iostream>
     using namespace std;

     struct Ocell {
       string codi, especie;
       float pes;
     };

     int main() {
       Ocell o, max;

       cin >> o.codi >> o.especie >> o.pes;
       max.codi = o.codi;
       max.especie = o.especie;
       max.pes = o.pes;
       while (o.codi != "FI" || o.especie != "FI" || o.pes > 0.0) {
         if (o.pes > max.pes) {
	   max.codi = o.codi;
	   max.especie = o.especie;
           max.pes = o.pes;
	 }
         cin >> o.codi >> o.especie >> o.pes;
       }
       
       cout << "Codi: " << max.codi << ' '
            << "Especie: " << max.especie << ' ' 
	    << "Pes: " << max.pes << endl;
     }

   El programa, però, ha quedat obsolet, ja que durant la pròxima
   temporada no s'estudiaràn poblacions d'ocells sinó els membres
   d'una colònia de formigues, i la dada d'interès són els minuts en
   què estan actives (fent alguna tasca) durant un dia. No només això
   sinó que en un futur, es plantegen seguir les poblacions de peixos,
   i estudiar l'evolució del seu tamany. En tots els cassos, però, es
   tracta de, donada una seqüència de dades d'un organisme, mirar quin
   d'ells té la màxima mesura (ja sigui pes en ocells, activitat en
   formigues o tamany en peixos). Es demana:

   - Modificar el programa anterior sense canviar la seva funcionalitat,
     però introduint-hi un TAD ``Organisme``, que implementi les
     operacions que es realitzen ara mateix en el programa, de forma
     que s'estableixi una barrera d'abstracció que aïlli la funció
     principal ``main`` dels detalls de l'organisme. 

   - Implementar el TAD ``Organisme`` per poder treballar amb
     formigues. Les dades de les formigues són: un enter que indica la
     formiga de la colònia, un text amb la "casta" de la formiga (en
     un formiguer hi ha vàries castes o tipus de formigues diferents),
     i un enter amb el número de minuts per dia que està activa. El
     sentinella és ``0 FI 0``. El programa ha de mostrar quina formiga
     és la més activa. La funció principal no s'ha de modificar.


   .. solucio::

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
   
        bool Organisme::menor_que(const Organisme& o) const {
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
   
.. rubric:: Bibliografia

- `Capítol 4. Abstracción de datos <http://arco.esi.uclm.es/~david.villa/pensar_en_C++/vol1/C04.html>`_, de "Pensar en C++", de Bruce
  Eckel (traducció de David Villa *et al.*).

- `Tipo de Dato Abstracto <http://es.wikipedia.org/wiki/Tipo_de_dato_abstracto>`_ a Wikipedia.
