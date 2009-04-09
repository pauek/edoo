
================
Bases de dades 1
================

Conceptes sobre bases de dades
------------------------------

Base de dades
  Conjunt gran de dades organitzat en forma de taules i interrelacions
  entre taules. Una base de dades pot emmagatzemar tota la informació
  d'una empresa.

Registre 
  Tupla amb dades diferents que descriuen una entrada en la
  taula. També se sol anomenar una *fila*. Cada ítem d'informació
  separada és un *camp* (o una *columna*). En el cas d'una taula per
  emmagatzemar les dades dels empleats d'una empresa, cada empleat pot
  tenir els següents camps: nom, cognoms, DNI, data de naixement, data
  de contractació, etc.

Taula
  Llista de registres sobre cert concepte. Per exemple, es pot tenir
  una taula dels empleats d'una empresa, a on cada registre és un
  empleat diferent, amb totes les dades.

Motor de bases de dades
  Software que implementa la persistència (l'emmagatzemament a disc)
  d'una base de dades i un llenguatge que permet manipular les dades
  (insertar registres, crear taules, crear relacions, esborrar
  registres, fer consultes, etc.). El llenguatge per a aquesta
  manipulació sol ser SQL. Existeixen molt motors de bases de dades
  comercials (Oracle, MS SQL Server, Informix, IBM DB2) i també de
  programari lliure (MySQL, PostgreSQL, SQLite).

Servidor de bases de dades 
  Ordinador que gestiona els fitxers de la base de dades i admet
  connexions a través de la xarxa per fer manipulacions i
  consultes. Aquest tipus de servidors centralitzen la informació i
  permeten que moltes altres aplicacions puguin accedir a les dades
  alhora.

SQL 
  *Structured Query Language*: un llenguatge especial per facilitar la
  interacció amb la base de dades. El llenguatge defineix una sèrie de
  comandes com ``CREATE``, ``INSERT``, ``SELECT``, etc. que permeten
  fer les manipulacions de la base de dades. És un llenguatge estàndar
  que fan servir pràcticament tots el motors.

SQLite 
  Motor de bases de dades molt simple i de programari lliure que no
  requereix cap instal·lació d'un servidor i que té usos en molts
  programes que fan servir bases de dades de forma local i per
  agilitzar la creació de taules relativament petites (per exemple,
  Firefox fa servir SQLite per mantenir una base de dades dels llocs
  visitats). SQLite es fa servir molt també a Google, Apple, Adobe i
  moltes altres grans empreses, tant internament com en part del seu
  *software*. La documentació de SQLite es troba a
  `http://www.sqlite.org/docs.html <http://www.sqlite.org/docs.html>`_


Creació de bases de dades
"""""""""""""""""""""""""

Cada motor de bases de dades té comandes diferents per crear una base
de dades (inclús es poden tenir vàries bases de dades gestionades pel
mateix motor). En el cas de SQLite, la creació d'una base de dades és
tan senzilla com invocar la comanda ``sqlite`` desde la línia de
comandes (en el cas de Windows, una finstra de MS-DOS) així::
 
   sqlite empresa.dat

El fitxer que contindrà la base de dades es diu "``empresa.dat``" i un
cop entrada aquesta comanda, el programa ``sqlite`` ens mostrarà un
símbol que ens permet entrar comandes SQL. Per finalitzar una
sessió SQLite s'ha d'escriure "``.quit``".


Treball amb taules
------------------

Creació de taules
"""""""""""""""""

Per crear una nova taula en una base de dades farem servir la comanda
``CREATE TABLE``, que té la sintaxi següent::

   CREATE TABLE <nom-taula> (
     <camp1> <tipus1>,
     <camp2> <tipus2>,
     ...
     <campN> <tipusN>,
   );

Aquelles parts de la comanda marcades amb ``<`` i ``>`` són les parts
variables de la comanda. Al final de les comandes SQL és necessari
posar un punt i coma en SQLite (que és el motor que farem servir). Un
exemple de creació d'una taula pot ser::

   CREATE TABLE empleats (
     nom TEXT,
     cognom1 TEXT,
     cognom2 TEXT,
     dni INTEGER,
     lletra_dni TEXT,
     antiguitat INTEGER
   );

En SQLite, els tipus de dades disponibles són ``INTEGER``, ``REAL``,
``TEXT`` i ``BLOB`` (les dates s'emmagatzemen com a ``INTEGER``). El
tipus ``TEXT`` és com una cadena de caracters (fins i tot un de sol) i
el tipus ``BLOB`` és genèric, i pot emmagatzemar qualsevol cosa (fins
i tot una imatge). Els noms dels camps els posem nosaltres i han de
seguir les convencions típiques de noms de C++. Els tipus disponibles
en una base de dades depenen del motor concret que fem servir. Alguns
motors implementen molts tipus diferents per tal de poder optimitzar
algunes operacions (SQLite és molt més senzill en aquest aspecte).

.. exercici::
   
   Escriu una comanda SQL per crear una taula ``cotxes`` que
   emmagatzemi les dades de cotxes, amb els següents camps: marca,
   model, número de portes, cilindrada (un real), llargada, amplada, i
   preu.

.. exercici::

   Escriu una comanda SQL per crear una taula ``equips`` amb els
   següents camps: nom, divisió en què juga, numero de jugadors,
   punts, gols a favor i gols en contra.

Inserció de registres
"""""""""""""""""""""

Per insertar registres en una base de dades, hem de fer servir la
comanda ``INSERT``. Aquesta comanda té la següent sintaxi::

   INSERT INTO <taula> VALUES (<valor1>, <valor2>, ..., <valorN>);

Els valors que van entre parèntesis i comes corresponen als valors de
cada camp de la taula, per l'ordre en què els hem definit en la
comanda ``CREATE TABLE``, exactament. Seguint l'exemple sobre empleats
d'una empresa, la següent comanda insertaria un registre amb la
informació d'un empleat anomenat Groucho::

   INSERT INTO empleats VALUES ("Groucho", "Marx", "Marx", 
     12345678, "X", 10);

Quan volem deixar una dada en blanc, es fa servir el valor ``NULL``
per indicar que en aquell camp no volem posar res. Per exemple, si no
volem omplir el valor del segon cognom, podem posar el següent::

   INSERT INTO empleats VALUES ("Groucho", "Marx", NULL, 
     12345678, "X", 10);


.. exercici:: 

   Escriu una comanda ``INSERT`` per insertar un cotxe en la taula
   ``cotxes`` creada en un exercici anterior. Utilitza dades
   inventades per omplir els camps.

.. exercici::

   Escriu una comanda ``INSERT`` per insertar un equip en la taula
   creada en un exercici anterior. Utilitza dades inventades.


Inserció de camps escollits
'''''''''''''''''''''''''''

Una altra manera d'insertar valors sense haver d'especificar els
valors que no volem omplir és fer servir una sintaxi alternativa, a on
es diu, abans de la clàusula ``VALUES`` quins camps s'ompliran. La
sintaxi és::

   INSERT INTO <taula> (<camp1>, ..., <campN>) 
     VALUES (<val1>, ..., <valN>)

i un exemple pot ser::

   INSERT INTO empleats (nom, cognom1) VALUES ("Groucho", "Marx")

En aquest cas posant (després del nom de la taula) la llista ``(nom,
cognom1)`` estem indicant que els valors que proporcionarem per omplir
el nou registre seran els anomenats per aquest ordre.

.. exercici::

   Inserta un equip a la taula de equips només omplint el nom de
   l'equip i el nombre de jugadors.


Esborrat de registres
"""""""""""""""""""""

Per esborrar un registre es fa servir la comanda ``DELETE``. Aquesta
comanda té la sintaxi::

   DELETE FROM <taula> WHERE <condició>

La condició és una expressió Booleana senzilla que determina quins
registres s'esborraran (aquells per als quals l'expressió sigui
certa). Per exemple, en el cas del empleats, si volem esborrar tots
aquells amb una antiguitat major que 10::

   DELETE FROM empleats WHERE antiguitat > 10;

O si volem esborrar tots el empleats amb cognom Marx podem fer::

  DELETE FROM empleats WHERE cognom1 == "Marx";

Els operadors de l'expressió són com en C++ excepte per les operacions
d'*and* lògic i *or* lògic, que es denoten amb ``AND`` i ``OR``,
respectivament. Els parèntesis també funcionen de la mateixa
manera. Així, si volem esborrar de la taula els empleats que tinguin
alhora el primer cognom García i segon López, farem::
 
  DELETE FROM empleats WHERE cognom1 == "Garcia" AND cognom2 == "López";


.. exercici::

   Seguint amb l'exercici sobre la taula de ``cotxes``, i suposant que
   la taula inclou dades que s'han entrat en un altre moment, escriu 
   comandes SQL per esborrar de la base de dades:

   - Els cotxes de la marca "Audi".
   - Els cotxes més amples que 2.5 metres.
   - Els cotxes de la marca "Volkswagen" que tinguin menys de 4 portes.

Esborrar una taula
""""""""""""""""""

Sovint és necessari esborrar tota una taula sencera. Per fer-ho es fa
servir la comanda ``DROP TABLE``, que té la sintaxi::

  DROP TABLE <taula>;

Per esborrar la taula d'empleats creada en un exemple anterior,
faríem::

  DROP TABLE empleats;

De vegades volem esborrar una taula tant si existeix com si no (perquè
volem començar de zero), però la comanda ``DROP TABLE`` tal com surt
més amunt dóna error si la taula que hem indicat no exiteix. Per
evitar aquest problema podem invocar la comanda amb ``IF EXISTS``
intercalat, així::

  DROP TABLE IF EXISTS empleats;


Alteració de les dades
""""""""""""""""""""""

Per modificar les dades d'una taula, es fa servir la comanda
``UPDATE``, que fa un recorregut per tots els registres i actualitza
aquells per als quals es compleix una condició. La sintaxi és::

  UPDATE <taula> SET <camp> = <valor> WHERE <condició>

La comanda passa per tots els registres posant el valor indicat en el
camp indicat quan es compleix la condició. Si en la taula d'empleats
volem canviar la lletra del DNI d'un empleat amb DNI número 34235817
farem::

  UPDATE empleats SET lletra_dni = 'A' WHERE dni = 34235817;

És típic canviar un sol registre d'una taula (perquè la condició només
la compleix un registre), però la clàusula ``WHERE`` de la comanda es
pot ometre, i se sobreentén que es vol actualitzar tots els registres
de la base de dades. Si volem posar l'antiguitat de tots els empleats
a 1 any, farem::
 
  UPDATE empleats SET antiguitat = 10;

Si volem actualitzar més d'un camp ho podem fer posant les
assignacions després de ``SET`` entre comes. Per exemple, per canviar
el nom i també el cognom d'un empleat amb DNI 12344321 farem::

  UPDATE empleats SET nom = "Chico", cognom1 = "Marx" 
    WHERE dni = 12344321;
  

.. exercici::

   Suposant la taula ``cotxes`` creada anteriorment (i que està plena
   amb valors), canvia la marca dels cotxes "Audi" a "AUDI".

.. exercici::

   Suposant la taula d'equips de futbol d'un exercici anterior, posa
   el nombre de gols a favor i en contra a 0 per a tots els equips de
   primera divisió.

Restriccions per als camps d'una taula
""""""""""""""""""""""""""""""""""""""

Per poder assegurar la integritat de les dades i que no hi ha errors,
els motors de bases de dades solen fer comprobacions a les dades que
s'intenten introduir o modificar, de manera que no pugui passar que hi
hagi dos files d'una mateixa taula que tinguin el mateix DNI si
s'estan referint a persones. Aquestes restriccions s'han d'especificar
quan es crea la taula amb la comanda ``CREATE TABLE`` i es posen
després de la descripció de cada camp. 

Hi ha 3 tipus de restriccions:

- ``NOT NULL``: que un camp no sigui buit.

- ``UNIQUE``: que cada valor del camp sigui únic.

- ``CHECK(<condició>)``: el camp ha de complir una condició concreta
  (per exemple, si és un enter, que sigui positiu).

La següent taula ``tt`` es crea amb tres camps ``a``, ``b``, i ``c``
que tenen cada un una restricció d'aquests tipus::

  CREATE TABLE tt (
    a TEXT UNIQUE,
    b INTEGER NOT NULL,
    c CHECK(c > 0)
  );

Suposant que hem fet la inserció següent::

  INSERT INTO tt VALUES ("bla", 0, 5);

Si intentem fer alguna de les insercions següents, el motor de bases
de dades no ens deixarà fer la inserció perquè alguna restricció no es
compleix::

  INSERT INTO tt VALUES ("bla", 1, 4);    // "bla" ja existeix (UNIQUE)
  INSERT INTO tt VALUES ("ble", NULL, 3); // camp 'b' és NULL
  INSERT INTO tt VALUES ("bli", 2, -5);   // camp 'c' no és positiu

Les restriccions es poden acumular, una mateixa columna en pot tenir
vàries. Per posar-les, s'han d'escriure seguides::

  CREATE TABLE zz (
    a TEXT UNIQUE NOT NULL,
    b INTEGER CHECK(b > 0) NOT NULL
  );

En aquesta taula es creen dos camps que mai poden ser ``NULL`` i en
què el primer ha de ser únic i el segon positiu.

.. exercici::
   
   Escriu una comanda SQL per crear una base de dades de components
   electrònics amb els camps:

   - codi (un enter) ha de ser únic i no buit,
   - descripció, no buit,
   - proveïdor, i
   - preu per unitat, major que zero.

.. Ejercicio: decir qué comandos insert no funcionarán
