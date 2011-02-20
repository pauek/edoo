

Els punters permeten fer pas per referència de paràmetres a accions
-------------------------------------------------------------------

Suposem que tenim una acció com la següent::

  void suma5(int& a) {
    a += 5;
  }

Aquesta acció es crida desde un programa principal com::

  int main() {
    int x;
    cout << "Un enter? ";
    cin >> x;
    suma5(x);
    cout << "Més 5 dóna: " << x << endl;
  }

El main, doncs, té una variable ``x`` que conté el valor al que volem
sumar 5. Si fem una acció ``suma5p`` que rebi un punter en comptes
d'un valor per referència, es pot aconseguir el mateix resultat, ja
que el punter contindrà l'adreça de la variable que s'ha de modificar
i en el ``main`` passarem l'adreça de ``x`` a ``suma5p``. La nova
implementació és::

  void suma5p(int *a) {
    *a += 5;
  }

I per invocar l'acció ``suma5p`` ara haurem de posar l'adreça de ``x``
en el ``main``::

  int main() {
    int x;
    cout << "Un enter? ";
    cin >> x;
    suma5p(&x);
    cout << "Més 5 dóna: " << x << endl;
  }

.. exercici::
   
   Digues quina és la sortida del següent programa si l'entrada és "7 11"::

     void f(int *a, int *b) {
       int x = *a;
       *a = *b;
       *b = x;
     }

     int main() {
       int i, j;
       cout << "Dos enters? ";
       cin >> i >> j;
       f(&i, &j);
       cout << "Ara són: " << i << ' ' << j << endl;
     }

   .. exercici::
   
      La sortida serà "11 7". L'acció ``f`` en realitat intercanvia els
      valors continguts a les adreces ``a`` i ``b``. El programa
      principal simplement crida la funció amb valors llegits del teclat.
