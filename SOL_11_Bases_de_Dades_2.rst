
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
