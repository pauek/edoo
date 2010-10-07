
.. tema:: pimd

==========================
Punters i Memòria Dinàmica
==========================

.. exercici::
   ::

      q = &d;
      p = &e;

.. exercici::
   
   ``q`` apunta a ``r``.

.. exercici::
   ::

      tImatge I;
      tImatge *p = &I;

.. exercici::
   ::

     A x(1);        
     A *p = &x;
     p->metode1(5);
     int resultat = p->metode2();

.. exercici::
   ::

      int main() {
        Data *d = new Data();
        cout << "Data? ";
	d->llegeix(cin);
	d->incrementa(21);
	cout << "Passades tres setmanes la data serà: ";
	d->escriu(cout);
	delete d;
      }

.. exercici::
   
   .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_class.cc

.. exercici::

   El programa principal serà:
   
   .. literalinclude:: ../src/06_Memoria_Dinamica/seq_int_stack.cc
      :lines: 63-
   
   Pots també :download:`descarregar el programa sencer <../src/06_Memoria_Dinamica/seq_int_stack.cc>`.


.. exercici::

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
