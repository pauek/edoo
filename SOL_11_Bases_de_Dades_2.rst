
.. highlightlang:: sql

================
Bases de dades 2
================

.. exercici::
   ::

      SELECT * FROM empleats WHERE nom == "Groucho";

      SELECT dni FROM empleats WHERE lletra_dni == "X";

      SELECT nom FROM empleats 
        WHERE cognom == "Garcia" AND antiguitat > 10;

.. exercici::
   ::
   
      SELECT avg(preu) FROM compra;

      SELECT sum(quantitat) FROM compra;

      SELECT sum(preu*quantitat) FROM compra;

.. exercici::
   
   Les comandes de creació de les taules de la base de dades per a la
   biblioteca són::
	
      CREATE TABLE llibres (
        titol TEXT,
	autor INTEGER,
	descripcio TEXT,
	isbn INTEGER,
	prestatge TEXT
      );

      CREATE TABLE autors (
        id INTEGER PRIMARY KEY,
	nom TEXT,
	cognoms TEXT,
	nacionalitat TEXT
      );

   S'ha posat un camp ``id`` en la taula d'autors perquè faci de clau
   primària, ja que en la informació dels autors no hi ha cap camp que
   sigui únic, realment (hi pot haver autors amb el mateix nom i
   nacionalitat i ser persones diferents). El camp ``autor`` de la
   taula de llibres referenciarà el camp ``id`` en la base de dades
   dels autors.

   Ara fem les consultes::

     SELECT llibres.titol FROM llibres, autors 
       WHERE llibres.autor = autors.id 
         AND autors.nom = "Juan" 
	 AND autors.cognoms = "Marsé";

     SELECT count() FROM llibres, autors
       WHERE llibres.autor = autors.id
         AND autors.nom = "Ken"
	 AND autors.cognoms = "Follet";

     SELECT l.isbn, l.titol, a.nom, a.cognoms
       FROM llibres as l, autors as a
       WHERE l.autor = a.id
         AND a.nacionalitat = "Colombia";

.. exercici::
   ::
 
     SELECT b.nom, b.quantitat, a.nom, a.web
       FROM beques as b, agencies as a
       WHERE b.durada = 3 and b.agencia = a.id;
     
     SELECT t.hora_sortida, t.num_vagons, e.nom, e.adreça
       FROM trens as t, estacions as e
       WHERE t.hora_sortida = "10:00" AND t.estacio = e.id;

.. problema::

   Creació de la base de dades, amb dues taules::

     CREATE TABLE nens (
       nom TEXT NOT NULL,
       cognoms TEXT NOT NULL,
       edat INTEGER CHECK (edat > 0) NOT NULL,
       adreça TEXT,
       codi_postal INTEGER NOT NULL,
       preferida INTEGER
     );

     CREATE TABLE joguines (
       id INTEGER NOT NULL PRIMARY KEY,
       descripció TEXT NOT NULL,
       edat_minima INTEGER NOT NULL,
       telefon INTEGER NOT NULL,
       volum REAL,
       pes REAL
     );

   Inserció de registres::

     INSERT INTO joguines VALUES (1, "Pilota", 8, 934556677, 0.004, 0.3);

     INSERT INTO nens VALUES ('Marx', 'Groucho', 12, "Gran Via 72, 3è 1a", 08008, 1);

   Consultes::

     SELECT n.nom, n.cognoms, j.descripció
       FROM nens AS n, joguines AS j
       WHERE n.preferida = j.id;
       
     SELECT n.nom, n.cognoms 
       FROM nens AS n, joguines AS j
       WHERE n.preferida = j.id AND j.descripció = "Scalextric";

     SELECT n.nom, n.cognoms
       FROM nens AS n, joguines AS j
       WHERE n.preferida = j.id AND n.edat < j.edat_minima;

     SELECT sum(j.volum), sum(j.pes) 
       FROM nens AS n, joguines AS j
       WHERE n.preferida = j.id;
