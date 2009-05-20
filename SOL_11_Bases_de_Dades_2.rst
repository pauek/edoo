
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

   :math:`D = \{ (0, a, red), (0, a, green), (0, a, blue), \\ (0, b, red), (0, b, green), (0, b, blue), \\ (1, a, red), (1, a, green), (1, a, blue), \\ (1, b, red), (1, b, green), (1, b, blue) \}` 

.. exercici::
   ::

     nom         nom
     ----------  -----------
     Nick	 Geri
     Nick 	 Michele
     Nick	 Victoria
     Nick	 Emma
     Howie	 Geri
     Howie 	 Michele
     Howie	 Victoria
     Howie	 Emma
     A.J.	 Geri
     A.J. 	 Michele
     A.J.	 Victoria
     A.J.	 Emma
     Kevin	 Geri
     Kevin 	 Michele
     Kevin	 Victoria
     Kevin	 Emma
     

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

.. problema::

   Primer de tot crearem les bases de dades. Per identificar cada
   client farem servir el DNI directament, però per identificar les
   pel·lícules, farem servir un codi que introduïm nosaltres (serà la
   clau primària). Hi haurà una taula de clients, una de pel·lícules i
   una de lloguers:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 1+
      :end-before: 1-

   La taula de lloguers ha de relacionar quins clients tenen quines
   pel·lícules i en quina data es va fer el lloguer. Per aconseguir
   que només 1 client tingui una pel·lícula, en la taula de lloguers
   el codi de la película serà únic:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 2+
      :end-before: 2-

   Un cop creades les taules, insertem alguns registres:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 3+
      :end-before: 3-

   Per registrar que Pep Guardiola acaba de llogar "El Padrino", farem:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 4+
      :end-before: 4-

   Per registrar que Britney Spears té llogada "Star Wars" desde fa 2
   dies (mireu la documentació de la funció ``date`` per això):
   
   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 5+
      :end-before: 5-

   Insertem alguns lloguers més:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 6+
      :end-before: 6-

   Si intentem llogar una pel·lícula que ja està llogada donarà
   error:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 7+
      :end-before: 7-

   Finalment, tenim les consultes:

   * Els clients en un cert codi postal:
   
   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 8+
      :end-before: 8-

   * Pel·lícules de cert gènere:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 9+
      :end-before: 9-

   * Pel·lícules llogades:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 10+
      :end-before: 10-

   * Dades del client que la té llogada "The Incredibles":

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 11+
      :end-before: 11-
 
   * Preu total per a un client:

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 12+
      :end-before: 12-
       
   * Llistat de "morosos":

   .. literalinclude:: src/11_Bases_de_Dades_2/video_club.sql
      :start-after: 13+
      :end-before: 13-
   
   Podeu descarregar la :download:`base de dades SQLite
   <src/11_Bases_de_Dades_2/videoclub.db>` i les :download:`comandes
   SQL <src/11_Bases_de_Dades_2/video_club.sql>` d'aquest problema.
