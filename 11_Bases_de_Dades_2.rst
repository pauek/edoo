
.. highlightlang:: sql

================
Bases de dades 2
================

La veritable utilitat de les bases de dades té a veure amb les
relacions entre taules. Quan tenim, per exemple, una taula amb
productes i una altra amb proveïdors, podem relacionar una taula amb
l'altra per poder saber quins productes són distribuïts per quins
proveïdors (sense haver de repetir la informació dels proveïdors a
cada producte). Per aconseguir això cal fer servir camps especials de
les taules anomenats *claus primàries*. Abans d'establir relacions és
important estudiar la forma de fer consultes a la base de dades amb la
comanda ``SELECT``.

La comanda ``SELECT``
---------------------

La comanda ``SELECT`` és una de les més importants en SQL, ja que ens
permet fer consultes a la base de dades. Quan fem un ``SELECT``, el
resultat és un llistat dels registres que compleixen les condicions
que nosaltres hem especificat. La forma més senzilla de ``SELECT`` és::

   SELECT <camps> from <taula>;

Amb aquesta forma demanem un llistat complet de certes columnes d'una
taula. Si hem create una taula amb::
  
  CREATE TABLE cites_famoses (
    autor TEXT,
    frase TEXT
  );

llavors, amb la comanda::

  SELECT autor, frase FROM cites_famoses;

Veurem un llistat de *totes* les cites que hi ha a la taula. En el
llistat es mostren els camps en l'ordre demanat. A més, si ens
interessa veure totes les columnes (cosa freqüent) es pot fer servir un
asterisc per indicar tots els camps::
 
  SELECT * FROM cites_famoses;

Aquesta comanda és igual que l'anterior (ja que els camps de la taula
estan en l'ordre ``autor``, ``frase``, també).

Filtrat de registres amb ``SELECT``
"""""""""""""""""""""""""""""""""""

La comanda ``SELECT`` també admet una opció ``WHERE`` que permet
indicar una expressió que sigui certa per aquells registres que volem
mostrar en el llistat. Si fem::

  SELECT frase FROM cites_famoses WHERE autor == "Shakespeare";

Veurem totes les cites de Shakespeare (només demanem la columna
``frase`` perquè l'autor sempre serà el mateix). La clàusula ``WHERE``
funciona com en les altres comandes, amb una condició.

.. exercici::

   Suposa que disposes d'una base de dades amb una taula definida per
   la comanda::
    
      CREATE TABLE empleats (
        nom TEXT,
   	cognom1 TEXT,
    	cognom2 TEXT,
 	dni INTEGER,
	lletra_dni TEXT,
	antiguitat INTEGER
      );

   Escriu comandes ``select`` per consultar el següent:

   - Totes les dades dels empleats que tenen nom "Groucho".
   - El número del DNI dels empleats amb la lletra del DNI 'X'.
   - El nom dels empleats amb antiguitat major de 10 anys i amb cognom
     'García'.

Expressions i Funcions
""""""""""""""""""""""

En les columnes que ``SELECT`` retorna com a resultat, es poden fer
servir expressions i funcions. Això significa que no cal posar només
el nom d'una columna, es pot posar una expressió que sigui un càlcul
que cal fer amb els valors de cada registre. Vegem-ne un
exemple. Crearem primer una taula per emmagatzemar una compra en una
botiga::

  CREATE TABLE compra (
    article TEXT,
    preu REAL,
    quantitat INTEGER 
  );

Ara podem insertar un parell de registres::

  INSERT INTO compra VALUES ("pomes", 1.70, 2);
  INSERT INTO compra VALUES ("peres", 2.10, 3);

La taula, doncs, conté dos articles de fruita, a on hem posat el preu
unitari, i per altra banda quantes unitats del producte hem
comprat. Per visualitzar el preu total de cada article que hem
comprat, hauríem de multiplicar el preu unitari pel nombre d'unitats,
i mostrar només la columna amb el resultat. Amb un ``SELECT`` això es
fa així::

  SELECT article, preu * quantitat FROM compra;

Que en SQLite mostrarà::

  pomes|3.4
  peres|6.3

Per altra banda, si volem mostrar un llistat amb les cites (en
l'exemple anterior) de tal manera que el nom de l'autor surti en
majúscules, podem posar::

  SELECT upper(autor), frase FROM cites_famoses;

La funció ``upper`` fa la conversió del camp ``autor`` a majúscules. 
Existeixen les següents funcions:

- ``abs(x)`` que fa el valor absolut del camp ``x``.
- ``length(x)`` que calcula la longitud del camp ``x`` si és un
  text.
- ``min(x, y, ...)`` que calcula el mínim dels camps ``x, y, ...``.
- ``max(x, y, ...)`` que calcula el màxim dels camps ``x, y, ...``.
- ``random()`` que retorna un número a l'atzar.
- ``lower(x)`` que retorna el text ``x`` en minúscules.
- ``upper(x)`` que retorna el text ``x`` en majúscules.


Funcions per fer recorreguts
""""""""""""""""""""""""""""

A part de poder fer comandes que mostrin un llistat de registres, la
comanda ``SELECT`` també permet fer recorreguts per les dades. Els
recorreguts els fan funcions especials que calculen alguna dada amb la
seqüència de registres. Per exemple, si volem saber la màxima
antiguitat d'un empleat (en la taula d'empleats de l'exercici
anterior), farem::

  SELECT max(antiguitat) FROM empleats;

I si volem saber el número de registres de la taula d'empleats (és a
dir, quants empleats hi ha), farem::

  SELECT count() FROM empleats;

Hi ha un seguit de funcions aplicables a les columnes que fan un
recorregut pels registres i realitzen algun càlcul. Les funcions
disponibles són:

- ``avg(x)`` realitza la mitjana del camp ``x``.
- ``count(x)`` compta els registres amb el camp ``x`` no buit (no
  ``NULL``). Les formes ``count(*)`` o ``count()`` retornen el número
  de registres.
- ``max(x)`` calcula el màxim valor del camp ``x``.
- ``min(x)`` calcula el mínim valor del camp ``x``.
- ``sum(x)`` calcula la suma del camp ``x`` (d'aquells registres que
  no són ``NULL``).

.. exercici::

   Partint de la taula ``compra`` d'un exemple anterior (i suposant que
   conté dades reals), calcula:
   - la mitjana dels preus dels productes comprats.
   - el número total d'unitats comprades.
   - el preu total de la compra.


Claus primàries
---------------

clau primària
  La clau primària d'una taula en una base de dades identifica
  únicament cada registre. Pot ser o bé un camp que és únic per
  definició (com el DNI o el número de la seguretat social en el cas
  de persones) o una combinació de camps que són únics en
  conjunt. Moltes vegades la clau és generada expressament pel motor
  de bases de dades. A vegades, també, es creen camps especials per
  poder fer servir com a claus primàries (un camp ``id``, per exemple).

La clau primària es, d'alguna manera, un identificador que ens permet
referenciar un registre d'una taula desde una altra. Si tenim una base
de dades de productes i proveïdors, podem posar com a clau primària de
la taula de proveïdors el NIF del proveïdor i després fer servir
aquest valor en cada producte per identificar quin proveïdor
distribueix el producte.


Restricció de clau primària
"""""""""""""""""""""""""""

En SQLite es pot afegir una restricció ``PRIMARY KEY`` a un camp d'una
base de dades perquè sigui clau primària. Aquesta restricció implica
també la restricció d'unicitat (``UNIQUE``). L'ús de la restricció
s'observa en el següent exemple::
   
  CREATE TABLE alumne (
    dni INTEGER PRIMARY KEY,
    lletra_dni TEXT,
    nom TEXT,
    cognoms TEXT
  );

Una altra forma d'expressar que un camp d'una taula és la clau
primària és posar, al final de la llista de camps, ``primary key
(<camp>)`` identificant el camp en concret. L'exemple anterior es
traduiria, doncs, així::

  CREATE TABLE alumne (
    dni INTEGER,
    lletra_dni TEXT,
    nom TEXT,
    cognoms TEXT,
    PRIMARY KEY (dni)
  );

Les claus primàries poden portar, també la opció ``AUTOINCREMENT`` que
permet no haver d'especificar el valor de la clau i que aquesta es
generi automàticament. Si creem la taula següent, per exemple::

  CREATE TABLE cites_famoses (
   id INTEGER PRIMARY KEY AUTOINCREMENT,
   autor TEXT,
   frase TEXT
  );

Quan afegim registres en aquesta taula, no és necessari especificar el
valor del camp ``id`` perquè es buscarà un valor únic i es posarà
automàticament (s'agafa el valor més petit que no aparegui a la
taula). Això ens permet fer un ``INSERT`` com aquest::

  INSERT INTO cites_famoses (autor, frase) 
    VALUES ("Shakespeare", "Ser o no ser");

Relacions entre taules
----------------------

El producte cartesià
""""""""""""""""""""

En matemàtiques, si tenim dos conjunts :math:`A = \{ 1, 2, 3 \}` i
:math:`B = \{ a, b, c \}`, es defineix el producte cartesià com el
conjunt de totes les combinacions d'elements de :math:`A` i
:math:`B`. El producte es denota amb :math:`C = A \times B` i conté
els següents elements:
 
  :math:`C = \{ (1, a), (1, b), (1, c), (2, a), (2, b), (2, c), (3, a), (3, b), (3, c) \}`

Així, doncs, el conjunt :math:`C` conté totes les possibles parelles
d'elements d':math:`A` i de :math:`B`.

.. exercici:: 
   
   Quin seria el producte Cartesià :math:`D = A \times B \times C`
   dels conjunts:

     :math:`A = \{ 0, 1 \}`

     :math:`B = \{ a, b \}`

     :math:`C = \{ red, green, blue \}`


La comanda ``SELECT`` fa el producte cartesià si tenim dues taules
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Suposem, doncs que hem entrat les següents comandes a una base de dades::

  CREATE TABLE a (val INTEGER);
  CREATE TABLE b (val TEXT);
  INSERT INTO a VALUES (1);
  INSERT INTO a VALUES (2);
  INSERT INTO a VALUES (3);
  INSERT INTO b VALUES ('a');
  INSERT INTO b VALUES ('b');
  INSERT INTO c VALUES ('c');

Això, bàsicament, està reproduïnt els conjunts explicats en la secció
anterior, com si fóssin dues taules ``a`` i ``b`` en la nostra base de
dades. Què succeeix, doncs, si fem la comanda ``SELECT`` següent?
::
  
  SELECT a.val, b.val FROM a, b;

Cal veure que hem hagut de posar ``a.val`` i ``b.val`` per distingir
entre les columnes (els camps) ``val`` de cada taula. La notació és
familiar de C++ per a tuples. També, la part ``FROM`` de la comanda
``SELECT`` té ``a`` i ``b`` separats per comes, indicant que
``SELECT`` obtindrà dades de les dues taules. Però quins valors
mostrarà la consulta?

La resposta és que ``SELECT``, si no indiquem res més, aplica el
producte escalar, i per pantalla veurem::

  val  val
  ---  ---
  1    a  
  1    b  
  1    c  
  2    a  
  2    b  
  2    c  
  3    a  
  3    b  
  3    c  

En absència de cap restricció, ``SELECT`` mostra totes les parelles
possibles de registres de la taula ``A`` i la taula ``B``.

.. exercici::

   Suposant les següents comandes SQL sobre una base de dades::

     CREATE TABLE boys (nom TEXT);
     CREATE TABLE girls (nom TEXT);
     INSERT INTO boys ("Nick");
     INSERT INTO boys ("Howie");
     INSERT INTO boys ("A.J.");
     INSERT INTO boys ("Kevin");
     INSERT INTO girls("Geri");
     INSERT INTO girls("Michele");
     INSERT INTO girls("Victoria");
     INSERT INTO girls("Emma");

   Quina serà la sortida de la següent comanda?
   ::

     SELECT boys.nom, girls.nom FROM boys, girls;


Relacions mitjançant ``SELECT``
"""""""""""""""""""""""""""""""

Suposem, doncs, que tenim dues taules de productes i proveïdors que
hem creat amb les següents comandes::

  CREATE TABLE prod (
    nom TEXT,
    descripció TEXT,
    codi INTEGER,
    preu REAL,
    nif_prov TEXT,
  );

  CREATE TABLE prov (
    nom TEXT,
    adresa TEXT,
    telefon INTEGER,
    nif TEXT PRIMARY KEY
  );

En la taula de productes, tenim apuntat en el camp ``nif_prov`` el NIF
del proveïdor per a cada producte i això indirectament ens permet
accedir a totes les seves dades, que estan a la taula de
proveïdors. La relació de les taules es fa íntegrament durant la
consulta amb la comanda ``SELECT`` (en particular, en la clàusula
``WHERE``). La consulta que volem fer és mostrar el nom i la
descripció de cada producte i al costat el nom i número de telèfon del
proveïdor d'aquest producte. La consulta és::

  SELECT prod.nom, prod.descripció, prov.nom, prov.telefon 
    FROM prod, prov 
    WHERE prod.nif_prov = prov.nif;

De nou veiem com per fer servir dues taules en una comanda ``SELECT``,
farem servir ``FROM prod, prov`` en la part del mig, i com és
necessari indicar de quina taula prové cada columna amb la notació
``prod.nom``. Aquesta consulta ha de mostrar certs registres d'una
taula correlacionats amb els de l'altra.

En absència de restriccions, la consulta mostraria el producte
cartesià de tots els productes amb tots el proveïdors (o sigui totes
les combinacions), però com que sabem que els productes estan
relacionats amb els proveïdors, *filtrem* el producte cartesià amb la
condició "``WHERE prod.nif_prov = prov.nif``", a on estem dient que
s'ha de complir que el nif apuntat al registre del producte ha de
coincidir amb el NIF que hi ha apuntat al registre del proveïdor. 

.. exercici::

   Escriu comandes per crear una base de dades per a una
   biblioteca. La base de dades ha de tenir una taula de llibres
   (autor, títol, descripció, ISBN, i prestatge de la biblioteca), i
   per altra banda, els autors es tenen en una taula a part (nom,
   cognoms, nacionalitat). El camp ``autor`` de la taula de llibres 

   Tot seguit suposa que tens les taules plenes de dades i escriu
   comandes en SQL per consultar:
   
   - Tots els llibres de l'autor "Juan Marsé".
   - El número de llibres de l'autor "Ken Follet".
   - El llibres a on l'autor té nacionalitat Colombiana.

Àlies en comandes ``SELECT``
''''''''''''''''''''''''''''

Si la consulta utilitza més d'una taula, la comanda ``SELECT`` pot ser
llarga perquè a cada camp hem d'especificar la base de dades de la que
prové el camp. Per evitar-ho podem fer servir una forma d'abreviar que
consisteix en donar un àlies per a cada taula en la clàusula
``FROM``. Vegem-ne un exemple::

  SELECT d.nom, d.descripció, v.nom, v.telefon FROM prod as d, prov as v
    WHERE d.codi = 1234 AND d.nif_prov = v.nif;

En aquesta comanda (equivalent a un exemple anterior), la part "``FROM
prod as d, prov as v``" ens diu que les taules ``prov`` (de
proveïdors) i ``prod`` (de productes) es diran ``v`` i ``d`` en tota
la comanda, per tant es pot escriure ``d.nom``. Això escurça
substancialment la comanda ``SELECT`` i la fa menys feixuga
d'escriure.

.. exercici::

   Escurça les següents comandes fent servir àlies::

     SELECT beques.nom, beques.quantitat, agencies.nom, agencies.web
       FROM beques, agencies 
       WHERE beques.durada = 3 and beques.agencia = agencies.id;
     
     SELECT trens.hora_sortida, trens.num_vagons, 
            estacions.nom, estacions.adreça
       FROM trens, estacions
       WHERE trens.hora_sortida = "10:00" 
         AND trens.estacio = estacions.id;

També es poden posar àlies en les columnes de la consulta per tal
d'amagar el nom intern dels camps d'una base de dades::

  SELECT d.nom as nom, d.descripció as descripció, 
         v.nom as proveidor, v.telefon as telefon 
    FROM prod as d, prov as v
    WHERE d.codi = 1234 AND d.nif_prov = v.nif;

Posant la columna "``v.nom as proveïdor``", estem demanant que el camp
de la columna sigui ``v.nom`` però surti en el llistat final la
paraula ``proveïdor`` que és molt més entenedora.

Problemes
---------

.. problema::

   *[De l'exàmen del 16/1/2009]* Els Reis d'Orient necessiten una base
   de dades per emmagatzemar quina és la joguina preferida de cada nen
   (només una per nen). És altament probable que molts nens tinguin la
   mateixa joguina com a preferida. La informació dels nens inclou el
   seu nom, cognoms, l'edat, la seva adreça, i el codi postal (per
   ajudar els Reis a situar la zona). De les joguines es vol saber la
   descripció, l'edat mínima per jugar am aquesta joguina, el telèfon
   del distribuidor principal, el volum (en metres cúbics) i el pes
   (en kilograms).

   Escriu comandes SQL per:
  
   * Crear la base de dades.

   * Insertar un nen i una joguina a la base de dades. El nen ha de
     tenir com a preferida aquesta joguina.

   * Fer les següents consultes:

     - Un llistat amb els noms i cognoms dels nens i la descripció de
       la seva joguina preferida.

     - Donada la descripció d'una joguina, un llistat dels nens que la
       tenen com a preferida.

     - Un llistat dels nens que tenen una joguina preferida per a la
       qual no superen l'edat mínima.

     - La suma del pes i el volum de les joguines preferides de tots
       els nens (per saber quants camions necessiten els Reis).
   
.. problema::

   Un videoclub necessita una base de dades dels seus clients i de les
   pel·lícules que tenen disponibles, així com de quins clients han
   llogat quines pel·lícules. Dels clients es vol el nom i cognoms, el
   DNI, i l'adreça de residència (amb el codi postal), i un enter que
   indiqui quantes vegades han retornat la pel·lícula més tard de 3
   dies (quan això succeeix, el client rep un avís, i al 3 avís, es
   cancel·la el seu compte). De les pel·lícules es necessita el títol,
   director, actor i actriu principal, l'any i el gènere de la
   pel·lícula, i també el preu del lloguer (que és fix). De cada
   pel·lícula només hi ha una còpia. Quan un client lloga una
   pel·lícula, es registra la data de lloguer, així quan la retorna es
   pot calcular el preu del lloguer. Només un client pot tenir una
   película en cert moment.

   El tipus de consultes que el videoclub necessita poder realitzar
   són:

   * Obtenir un llistat dels clients en un cert codi postal.

   * Obtenir un llistat de les pel·lícules (títol i any) de cert
     gènere, o de cert director (o actor/actriu principal).

   * Obtenir un llistat de les pel·lícules llogades (títol i any).
   
   * Donada una pel·lícula, mostrar les dades del client que la té
     llogada.
    
   * Donat un client, obtenir el preu total de les pel·lícules que té
     llogades (per quan les retorna).

   * Per poder actualitzar els avisos, mostrar un llistat dels clients
     que tenen alguna pel·lícula en lloguer desde fa més de 3 dies.

   Escriu les comandes SQL per crear la base de dades, insertar
   algunes registres de clients, pel·lícules i lloguers i fer totes
   les consultes que es necessiten. Per manipular dates en SQLite, cal
   fer servir la funció ``date``, i crear els camps de la base de
   dades amb tipus ``DATE``. Vegem-ne un exemple::

     CREATE TABLE events (event TEXT, data DATE);

   Per insertar registres, fem servir la funció ``date`` amb la data
   en format ``AAAA-MM-DD``::

     INSERT INTO events VALUES ("Esclat 1a Gerra Mundial", date('1914-06-14'));
     INSERT INTO events VALUES ("Aterratge a la Lluna", date('1969-07-20'));
     INSERT INTO events VALUES ("Star Wars IV: A New Hope", date('1977-05-25'));

   Per consultar els events posteriors a certa data::

     SELECT * from events WHERE data > date('1950-01-01');

   Això mostra tots els events posteriors l'1 de Gener de 1950. Per
   obtenir una data respecte al dia d'avui, es fa servir:

   - ``date('now')``: la data d'ara mateix.
   - ``date('now', '+1 day')``: la data de demà.
   - ``date('now', '-5 days')``: la data de fa 5 dies.

   Canviant el segon paràmetre per un número de dies (``days``) i
   utilitzant ``+`` i ``-`` es pot obtenir una data relativa al dia
   d'avui.
     
