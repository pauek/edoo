
===========================
Bases de dades 1: Solucions
===========================

.. exercici::
   ::

      CREATE TABLE cotxes (
        marca text,
	model text,
	nportes integer,
	cilindrada real,
	llarg real,
	ample real,
	preu real
      );

.. exercici::
   ::

      CREATE TABLE equips (
        nom text,
	divisio integer,
	njugadors integer,
	punts integer,
	gols_a_favor integer,
	gols_en_contra integer
      );

.. exercici::
   ::

      INSERT INTO cotxes 
        VALUES ("Audi", "A3", 3, 2500, 4.6, 2.2, 45000);

.. exercici::
   ::
     
      INSERT INTO equips
        VALUES ("Terrassa", 3, 17, 13, 10, 5);

.. exercici::
   ::
   
      INSERT INTO equips (nom, njugadors) 
        VALUES ("Sabadell", 18);

.. exercici::
   ::
     
       DELETE FROM cotxes WHERE marca == "Audi";

       DELETE FROM cotxes WHERE ample > 2.5;

       DELETE FROM cotxes 
         WHERE marca == "Volkswagen" AND nportes < 4;

.. exercici::
   ::

      UPDATE cotxes SET marca = "AUDI" 
        WHERE marca == "Audi";

.. exercici::
   ::
    
      UPDATE equips SET gols_a_favor = 0, gols_en_contra = 0
        WHERE divisio = 1;

.. exercici::
   ::

      CREATE TABLE components (
        codi INTEGER UNIQUE NOT NULL,
	descripcio TEXT NOT NULL,
	proveïdor TEXT,
	preu INTEGER CHECK(preu > 0)
      );
