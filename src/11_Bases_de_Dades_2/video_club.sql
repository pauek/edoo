DROP TABLE IF EXISTS clients;
DROP TABLE IF EXISTS pelicules;
DROP TABLE IF EXISTS lloguers;

-- 1+
CREATE TABLE clients (
 dni INTEGER PRIMARY KEY,
 nom TEXT NOT NULL, 
 cognoms TEXT NOT NULL,
 adreça TEXT NOT NULL,
 codi_postal INTEGER NOT NULL,
 avisos INTEGER
);

CREATE TABLE pelicules (
 codi INTEGER PRIMARY KEY AUTOINCREMENT,
 titol TEXT NOT NULL,
 director TEXT NOT NULL,
 any INTEGER NOT NULL,
 actor TEXT,
 actriu TEXT,
 gènere TEXT,
 preu REAL
);
-- 1-

-- 2+
CREATE TABLE lloguers (
 dni INTEGER NOT NULL,
 codi INTEGER UNIQUE NOT NULL,
 data DATE NOT NULL
);
-- 2-

-- 3+
INSERT INTO pelicules (titol, director, any, actor, actriu, gènere, preu)
  VALUES ("Star Wars IV: A New Hope", "George Lucas", 1977,	 
          "Mark Hamill", "Carrie Fisher", "starwars", 1.5);
                                           
INSERT INTO pelicules (titol, director, any, preu)		 
  VALUES ("The Incredibles", "Brad Bird", 2004, 2.5);
              
INSERT INTO pelicules (titol, director, any, actor, gènere, preu)	 
  VALUES ("The Godfather", "Francis Ford Coppola", 1972, "Marlon Brando", "Mafia", 0.5);

INSERT INTO pelicules (titol, director, any, gènere, preu)	 
  VALUES ("The Nightmare Before Christmas", "Tim Burton", 1993, "Fantasía", 4.5);
									 
INSERT INTO clients VALUES (					 
  10102030, "Pep", "Guardiola", "Rosselló, 131", 08025, 0		 
);								 
                                                                   
INSERT INTO clients VALUES (					 
  40403020, "Britney", "Spears", "Mallorca, 195", 08032, 0	 
);								 
                                                                   
INSERT INTO clients VALUES (					 
  31132002, "Pablo", "Picasso", "Pintor Fortuny, 13", 08004, 1	 
);
-- 3-

-- 4+
INSERT INTO lloguers VALUES (10102030, 3, date('now'));
-- 4-

-- 5+
INSERT INTO lloguers VALUES (40403020, 1, date('now', '-2 days'));
-- 5-

-- 6+
INSERT INTO lloguers VALUES (40403020, 4, date('now', '-5 days'));
INSERT INTO lloguers VALUES (31132002, 2, date('now', '+1 day'));
-- 6-

-- 7+
INSERT INTO lloguers VALUES (31132002, 1, date('now')); -- error...
-- 7-

-- 8+
SELECT * FROM clients WHERE codi_postal = 08004;
-- 8-

-- 9+
SELECT titol, any FROM pelicules WHERE gènere = "Mafia";
-- 9-

-- 10+
SELECT p.titol, p.any FROM lloguers as l, pelicules as p 
  WHERE l.codi = p.codi; 
-- 10-

-- 11+
SELECT c.* FROM clients as c, pelicules as p, lloguers as l
  WHERE p.titol == "The Incredibles" AND l.codi == p.codi AND c.dni == l.dni;
-- 11-

-- 12+
SELECT sum(p.preu) FROM clients as c, pelicules as p, lloguers as l
  WHERE c.dni == 40403020 AND c.dni == l.dni AND p.codi == l.codi;
-- 12-

-- 13+
SELECT p.titol, c.nom, c.cognoms, c.adreça FROM clients as c, lloguers as l, pelicules as p
  WHERE c.dni == l.dni AND p.codi == l.codi AND l.data < date('now', '-2 days');
-- 13-
