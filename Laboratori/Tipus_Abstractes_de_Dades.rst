
=========================
Tipus Abstractes de Dades
=========================

.. tema:: lab.tad

Objectius
=========

- Utilitzar correctament les funcions membre.

- Declarar correctament tuples amb funcions membre.

- Detectar tipus abstractes de dades en un programa donat.

- Fer les modificacions oportunes en un programa per tal de crear una
  barrera d'abstracció.


Inversió d'una imatge
=====================

Primer :download:`descarrega el codi font<src/inverteix_imatge/inverteix0.cpp>` 
del següent programa, que inverteix una imatge en blanc i negre:

.. literalinclude:: src/inverteix_imatge/inverteix0.cpp
	:lines: 1-67
   
Aquest programa llegeix una imatge en format PGM (una imatge en blanc
i negre), inverteix el valor de cada píxel (és a dir, subsitueix negre
per blanc) i finalment guarda la imatge en un altre fitxer (per si no
es vol sobreescriure el fitxer incial). Si vols documentació sobre el
format d'imatges PGM, consulta l'adreça 
`http://netpbm.sourceforge.net/doc/pgm.html <http://netpbm.sourceforge.net/doc/pgm.html>`_.

La variable ``nmax`` conté un enter que surt a la tercera línia
del fitxer de la imatge i que indica el valor màxim que pendrà cada un
dels píxels tal com estan representats en el fitxer. El programa
tradueix aquest valor enter a un real entre 0 i 1 fent la divisió::

  float(px) / float(nmax)

La imatge final, en blanc i negre, té la informació del valor de gris
a cada pixel com un número entre 0 i 1, doncs.

*L'objectiu de la pràctica és fer les modificacions oportunes a aquest
programa per tal que pugui fer la mateixa operació amb imatges en
color.*

Per fer les modificacions amb comoditat, però, primer buscarem la
manera de crear barreres d'abstracció que ens separin el programa en
unitats independents. Els passos a seguir són:

- Modificar el programa per posar-hi TADs i per tant fer-lo robust a
  canvis, però *sense canviar la seva funcionalitat*.

- Un cop tenim els TADs en marxa, fer els canvis que teniem
  pensats. Si hem plantejat bé els TADs, aquests canvis seràn fàcils
  d'introduir.

L'abstracció ``Pixel``
----------------------

Una primera abstracció que podem veure en el programa és el valor d'un
píxel (o *picture cell*). Aquesta ens serà molt útil de cara a poder
canviar el fet que els píxels en blanc i negre només emmagatzemen un
valor, i en canvi en color, cada píxel té 3 valors. 

.. exercici::

   Busca els punts del programa a on es facin servir els valors de les
   caselles de la imatge.

Un cop identificats els punts del codi a on es fan servir els píxels,
cal determinar què s'està fent a cada un d'aquests, i posar un nom a
aquestes operacions. Per exemple, el primer lloc a on es modifiquen
les caselles de la imatge és en la lectura. El parell de línies de codi::

   fin >> px;
   I.pixels[i][j] = float(px) / float(nmax);

el que fan realment és "llegir un píxel", donat un canal d'entrada (el
``fin``, de tipus ``istream``) i el valor màxim del PGM (``nmax``). Si
volem aïllar aquesta operació, podem crear una funció membre de
``Pixel`` que es digui ``llegeix(istream& in, int nmax)`` que rep el
píxel que s'ha de llegir (per referència per poder-lo omplir), un
objecte de tipus ``istream`` (tal com el propi ``cin`` o un fitxer
d'entrada, com és el cas d'aquest programa) i el valor màxim
enter. Si creem el tipus ``Pixel`` fent servir funcions membre tenim
(només surt la funció ``llegeix``)::

  struct Pixel {
    float valor;
    
    void llegeix(istream& i, int nmax);
    // ...
  };

  void Pixel::llegeix(istream& i, int nmax) {
    int px;
    i >> px;
    valor = float(px) / float(nmax);
  }

.. exercici::

   Afegeix el TAD ``Pixel`` en el programa, declara'l a sobre de
   ``Imatge``. Copia també la implementació de ``llegeix`` tal com
   està.

El TAD s'ha de fer servir en els píxels de la imatge (cada casella de
la matriu), i per tant hem de canviar ``float`` per ``Pixel`` en
l'estructura ``Imatge`` així::

  struct Imatge {
    int tamx, tamy;
    Pixel pixel[XMAX][YMAX];
  };

.. exercici::

   Modifica el TAD imatge perquè faci servir ``Pixel`` en cada
   casella, tal com s'indica més amunt.

Ara, amb aquesta operació podem canviar la part de la lectura de
píxels de la següent manera (s'han afegit els ``for``\s per a més
claredat)::

  for (int i = 0; i < XMAX; i++) {
    for (int j = 0; j < YMAX; j++) {
      I.pixel[i][j].llegeix(fin, nmax); 
    }  
  }

La idea és que ara, cada casella de la taula bidimensional és un
``Pixel`` i per tant té la funció membre ``llegeix`` que es pot cridar
amb la notació de tuples. 

.. exercici::

   Determina les altres operacions (anomena-les ``escriu`` i
   ``inverteix``) que hem d'afegir al TAD ``Pixel``, i
   implementa-les. Això té dues fases:
   
   - Declara i implementa les funcions membre.

   - Modifica el codi d'inversió de la imatge i escriptura per tal que
     es facin servir les noves funcions membre.


El tipus abstracte ``Imatge``
-----------------------------

Un cop fets aquests canvis, realment ja podriem fer la modificació que
havíem plantejat, en què es manipulen imatges en color. Abans de
fer-ho, però, podem aprofitar per seguir dividint el programa en
trossos independents un cop més, així el programa quedarà ben
modularitzat. La nova barrera d'abstracció que introduirem ara mateix
no ens facilita la vida especialment en el cas del pas a color, però
fer TADs sempre ajuda a tenir *oportunitats* de modificar el programa
fàcilment, i inclús a vegades suggereix modificacions interessants que
es podrien fer.

La idea, ara, és que resulta que es pot veure l'estructura ``Imatge``
com un altre TAD (que utilitza el TAD ``Pixel`` sense conèixe'n els
detalls). Si convertim ``Imatge`` a un TAD, el ``main`` manipularà la
imatge sense saber-ne els detalls.

.. exercici::

   Determina les tres operacions que el ``main`` realitza amb la
   imatge. Determina'n els paràmetres i el nom que els
   posaries. Fixa't que aquestes operacions s'estan realitzant en el
   ``main`` es tracta d'"extirpar-les". 

.. exercici::

   Afegeix les operacions com a funcions membre de la tupla ``Imatge``
   i implementa-les, fent "corta i pega" del codi que hi ha al
   ``main`` i després corregint-lo perquè funcioni en el nou context.

.. exercici::

   Corregeix el ``main`` per tal que faci servir el TAD
   ``Imatge``. Compila el programa i comprova que funciona
   correctament.

Un cop fets aquests canvis, és curiós que els noms de les funcions que
hagis posat en el TAD ``Imatge`` expliquen tan bé el que està succeïnt
en el ``main`` que els comentaris inicials que hi havia al codi són
superflus.

Imatges en color
----------------

Ara, doncs, es pot fer la modificació que havíem plantejat al
principi. La idea és, simplement, modificar la lectura/escriptura de
la imatge perquè utilitzi la capçalera "P3" en comptes de "P2" (inclús
es podria fer una constant a dalt de tot de tipus ``string``), i
canviar la lectura i escriptura del píxel (ha de llegir i escriure
tripletes en comptes d'un sol valor). Invertir un pixel amb els 3
canals R G i B es fa invertint cadascun per separat.

.. exercici::

   Modifica, doncs, el programa perquè pugui manipular fitxers amb
   colors. Fes servir els fitxers que trobaràs a Atenea per tal de
   provar el programa.
