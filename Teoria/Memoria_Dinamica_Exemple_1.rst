
.. _seq_int:

Exemple: Mostrar una seqüència al revés sense límits
----------------------------------------------------

Aquest és un programa que no podiem fer fins ara. Es tracta d'un
programa que llegeix una seqüència d'enters acabada en -1 i tot seguit
la mostra per pantalla al revés, però la seqüència pot tenir un tamany
qualsevol, només limitat per la quantitat de memòria disponible. Per
fer-ho ha d'emmagatzemar la seqüència sencera en memòria, no hi ha cap
altra manera. Fins ara, havíem de suposar un tamany màxim per a la
seqüència, però amb la memòria dinàmica, si ens arriba un nou element,
el podem posar a una zona nova reservada dinàmicament, i així no hem
d'imposar un límit arbitrari.

Per emmagatzemar els elements de la seqüència farem servir un
``struct`` molt peculiar:

.. literalinclude:: ../src/06_Memoria_Dinamica/seq_int.cpp
   :lines: 4-8

Aquest ``struct`` és com una peça d'una cadena. Pot emmagatzemar un
enter i a part també un punter a un altre peça de la cadena (un
``Element``), que hem anomenat ``anterior`` perquè apuntarà a la peça
prèvia.

El programa és el següent:

.. literalinclude:: ../src/06_Memoria_Dinamica/seq_int.cpp
   :linenos:

Aquest programa utilitza un punter ``actual`` que apunta a
l'``Element`` actual. Al principi aquest punter és 0, perquè no hi ha
cap peça. Tot seguit llegeix cada element de la seqüència, i quan ho
fa, emmagatzema l'element amb un ``Element``  ``nou`` que reserva en
memòria (línia 16). A ``nou`` hi posa l'enter i l'adreça de la peça anterior
(que és l'``actual``), per no perdre el fil (línies 17 i 18). Finalment, la nova peça
es converteix en l'``actual`` (línia 19). Cada enter que llegim incrementa una
mica la memòria que el programa té reservada, però no reservem cap
tamany concret al principi.

Un cop llegida la seqüència, si "tibem del fil", és a dir si a partir
de la peça actual anem mirant el camp ``anterior`` i anem saltant de peça
en peça, trobarem tots els enters que hem anat posant. Això és el que
fa la iteració que mostra els enters (línies 24 a 27).

.. exercici::

   Modifica el ``struct Element`` del programa anterior perquè sigui
   una classe. Tindrà la declaració següent

   .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_class.cc
      :lines: 5-14

   Modifica el programa per fer servir la nova classe.

   .. solucio::

      .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_class.cc

.. exercici::

   Considera la classe ``Contenidor`` amb la declaració i
   implementació següents
    
   .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_stack.cc
      :lines: 29-62

   Aquesta classe fa servir ``Element`` per emmagatzemar enters amb
   els mètodes ``posa`` i ``treu`` (una diferència és que ``treu`` ara
   fa ``delete`` dels elements, tal com ha de ser). Llegeix atentament
   cada mètode per entendre què fa, comparant amb el programa original
   per veure-ho.

   Reimplementa ara el programa fent servir la classe ``Contenidor``.

   .. solucio::

      El programa principal serà:
   
      .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_stack.cc
         :lines: 63-
   
      Pots també :download:`descarregar el programa sencer<../src/06_Memoria_Dinamica/seq_int_stack.cc>`.


.. exercici::

   Afegeix el mètode amb declaració::

      int num_elements() const;

   a la classe ``Contenidor`` i implementa'l.

   .. solucio::

      Tenim dues opcions per implementar el mètode:
   
      1. Quan ens demanen el número d'elements, el calculem *in situ*.
   
      2. Afegim un atribut ``_num_elements`` a on guardem el número
         d'elements que tenim i retornem aquest número.

      En la primera opció gastem menys memòria, y en la segona menys CPU.

      Anem per la primera. A la declaració només cal afegir el mètode
      ``num_elements``::

         class Contenidor {
           // ...
           int num_elements() const;
         };
 
         int Contenidor::num_elements() const {
           Element *e = _ultim;
           int k = 0;
           while (e != 0) {
             k++;
             e = e->anterior();
           }
           return k;
         }

      Ara la segona. Hem d'afegir el nou atribut ``_num_elements``, i
      haurem de modificar el constructor, ``posa`` i ``treu`` perquè
      l'alterin. Les línies afegides estan marcades amb una fletxa::

         class Contenidor {
           // ...
         private:               // <==
           int _num_elements;   // <==
         };
 
         Contenidor::Contenidor() {
           _ultim = 0;
           _num_elements = 0;   // <==
         }
 
         void Contenidor::posa(int n) {
           Element *nou = new Element(num);
           nou->enllasa(_ultim);
           _ultim = nou;
           _num_elements++;     // <==
         }
 
         void Contenidor::treu() {
           Element *anterior = _ultim->anterior();
           delete _ultim;
           _ultim = anterior;
           _num_elements--;     // <==
         }
 
         // ...   

