
================
Memòria dinàmica
================

Objectius
=========

- Aprendre a fer servir els operadors **new** i **delete**.

- Relacionar els operadors **new** i **delete** amb els constructors i destructors.


Memòria dinàmica
================

A classe de teoria hem vist que podem reservar espai per a objectes fent servir l'operador **new** i eliminar-los utilitzant l'operador **delete**. Per exemple, si tenim la classe ``Llibre``::

  class Llibre
  {
    string titol, autor;
    
  public:
    Llibre();
    ~Llibre();
  };
  
podem reservar un objecte de tipus llibre amb el codi següent::

  Llibre *ptr;
  
  ptr = new Llibre;
  
i podem eliminar l'objecte que hem creat fent servir l'operador **delete**::

  delete ptr;
  
També era possible crear un conjunt d'objectes (un array), fent servir el codi::

  Llibre *ptr;
  
  ptr = new Llibre[100];
  
encara que llavors per eliminar-los calia fer::

  delete [] ptr;


Constructors i destructors
==========================

Ara bé, si recordeu, cada vegada que creem un objecte nou al nostre programa, s'ha de cridar necessàriament a un dels constructors de l'objecte creat. De la mateixa manera, quan destruim un objecte sempre es crida al seu destructor.

Si això és cert, quan al codi anterior creem un objecte de la classe ``Llibre``, s'hauria de cridar al constructor corresponent. Això ho podem comprovar afegint una línia de codi al constructor de ``Llibre`` tal que escrigui per pantalla un missatge. Per exemple::

  cout << "S'ha creat un objecte de la classe Llibre" << endl;
  
.. exercici::

   Crea un nou projecte per a provar que els constructors es criden quan fem servir l'operador **new**. Aquest projecte haurà de tenir tres fitxers: **Llibre.h** que contindrà la definició de la classe Llibre, **Llibre.cpp** que contindrà la implementació dels mètodes de ``Llibre`` (de moment, només el constructor i el destructor), i **main.cpp** que haurà de crear un objecte de la classe ``Llibre``.
   
.. exercici::

   Fes el mateix amb el destructor de la classe ``Llibre``. Afegeix un missatge, destrueix l'objecte ``Llibre`` que has creat i comprova que el missatge del destructor s'escriu per pantalla.

.. exercici::

   Llavors, que passa si reservem tot un array d'objectes ``Llibre``?. Crea un array de 100 ``Llibre``'s i després destrueix-los. Compila i executa el programa per a veure que passa amb els missatges que has afegit al constructor i al destructor.



Arrays dinàmics
===============

La principal utilitat de la memòria dinàmica es la de poder crear objectes quan els necessitem i en la quantitat en que els necessitem durant l'execució del programa. Per exemple, quan en sessions anteriors llegiem imatges des d'un fitxer feiem el codi per a que poguès guardar-se imatges de diverses mides. Per a fer-ho, definiem un array d'objectes de tipus ``Pixel``, però feiem amb una mida fixa, cosa que feia que no poguèssim llegir imatges més grans. En aquests casos és útil fer servir memòria dinàmica.

També passa de vegades que hi ha problemes que no es poden resoldre si no és fent servir memòria dinàmica. Per exemple, si tenim una llista de llibres i resulta que aquesta no està en l'ordre que toca sino que es troba del revés, com podriem fer per a rectificar-ho? Una solució és llegir la llista a un array que previament hem creat i després escriure-la començant per l'últim element.

Juntament amb l'enunciat d'aquesta sessió trobareu un fitxer **books.txt** que conté una llista de llibres. El format és el següent:

100
The Lord of the Rings
JRR Tolkien
Pride and Prejudice
Jane Austen
...
...
...

El primer element és un nombre enter que indica quants llibres hi ha a la llista (100 llibres). Tot seguit trobeu el títol del primer llibre i el seu autor. Després el títol del segon llibre i el seu autor. I així succesivament.

Es tracta de llegir tota aquesta llista a un array que previament haureu reservat fent servir memòria dinàmica i escriure-la en un altre fitxer en l'ordre invers. 

Cal tenir en compte que tant els títols com els noms dels autors tenen espais. Això fa que no es puguin llegir directament amb ``cin`` com feiem fins ara::

  cin >> titol;
  
Però per sort els títols i els noms dels autors estan en línies diferents. Podem llegir-los fent servir ``getline`` que llegeix tota una línia sense espais::

  getline(cin, titol);
  
Per a poder fer servir la funció ``getline``, caldrà que afegiu al vostre codi el include::

  #include <string>

.. exercici::

   Fent servir la classe ``Llibre``, afegeix a la funció ``main`` el codi necessari per a llegir la llista del fitxer **books.txt**. Tan bon punt has llegit el nombre de llibres del fitxer pots crear un array del tamany necessari amb l'operador **new**. Afegeix a la classe ``Llibre`` els mètodes que necessitis.
   
.. exercici::

   Ara cal recorrer l'array en ordre invers, des de l'últim element fins al primer, escrivint els llibres de la llista. D'aquesta manera tindrem la llista del revés.
   
.. exercici::

   Si s'ha fet servir memòria dinàmica, el programa realitzat es podrà aplicar a la llista de llibres del fitxer **books2.txt** sense cap canvi del codi. Prova-ho.
   

