
Piles
=====

adaptadors
   Alguns contenidors de la STL s'implementen a partir d'altres. És a
   dir, defineixen mètodes nous però fan servir les operacions
   d'altres contenidors per treballar.

pila 
   *Stack* en anglès. Estructura de dades *Last In First Out*, o LIFO
   (l'últim que va entrar és el primer que surt). Si imaginem les
   piles com estructures verticals (que és la forma que adopten les
   piles d'objectes físics, com ara plats), podem interpretar que
   l'element que ha entrat l'últim està a dalt de tot (el *top*).


Per fer servir piles hem de fer l'``include`` corresponent::

   #include <stack>

Per declarar una pila es fa com amb els altres contenidors de la STL::

   stack<int> S;

que declara una pila d'enters buida. 

Operacions amb piles
--------------------

Les piles són estructures molt bàsiques, només tenen 3 operacions
principals:

- **apilar**, *push* en anglès, que posa un element al damunt de tot
  de la pila. 

- **desapilar**, *pop* en angès, que treu l'element de dalt de tot (i
  deixa al descobert el següent).

- **consultar** el primer, per obtenir el *top*, l'element de dalt de
  tot, sense treure'l de la pila.

Aquestes operacions típiques tenen 3 mètodes especials


Mètodes de la classe ``stack``
------------------------------

Constructors:

.. cpp:function:: stack<T>()
   
   Crea una pila buida.


.. cpp:function:: stack<T>(const stack<T>& s)
   
   Crea una pila a partir d'una altra.


Els mètodes de la classe ``stack`` són els següents:


.. cpp:function:: int stack<T>::size() const
   
   Per obtenir el tamany.


.. cpp:function:: bool stack<T>::empty() const
   
   Per saber si la pila està buida. 


.. cpp:function:: T& stack<T>::top()
   
   Retorna una referència a l'element de dalt de tot.


.. cpp:function:: void stack<T>::push(const T& t)
   
   Apila un element a dalt de tot.


.. cpp:function:: void stack<T>::pop()
   
   Elimina l'elemnt de dalt de tot.


.. exercici::

   Què mostra per pantalla el següent codi?
   ::
     
      stack<char> S;
      S.push('l'); S.push('e'); S.push('a');
      S.push('r'); S.push('z'); S.push('A');
      while (!S.empty()) {
        cout << S.top();
	S.pop();
      }

   .. solucio::

      El codi mostrarà per pantalla::
    
        Azrael
   

.. exercici::
   
   Fes una acció ``opera`` que rebi una pila d'enters i un caracter
   (que podrà ser només un de ``'+'``, ``'-'``, ``'*'`` i ``'/'``), i
   tregui els 2 valors superiors de la pila, realitzi la operació que
   indica el caracter, i posi el resultat a la pila. En el cas
   de la resta, si el *top* és ``a`` i el de sota ``b``, la resta ha
   de fer ``b - a`` (i semblant amb la divisió).

   .. solucio::
   
      L'acció seria::

        void opera(stack<int>& s, char op) {
          int b = s.top(); s.pop();
          int a = s.top(); s.pop();
          int res;
          switch (op) {
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/': res = a / b; break;
          }      
          s.push(res);
        }


.. exercici::

   Imagina un programa que fa servir una pila d'enters i rep una
   seqüència d'enters i operacions. Quan rep un enter, l'apila, i quan
   rep una operació, tal com amb l'acció de l'exercici anterior,
   realitza la operació amb els 2 enters de dalt de la pila. Si el
   programa rep "``3 2 +``" deixarà un 5 a la pila. Si rep ``1 1 + 2
   *`` deixarà un 4. Calcula el resultat de les seqüències següents:

   - ``3 3 3 + *``
   - ``3 4 5 1 * + -``
   - ``1 2 + 3 -``
   - ``5 4 * 100 + 2 3 * 10 * -``

   Escriu aquestes expressions de la forma habitual (amb
   parèntesis). Per exemple, la seqüència ``1 1 + 2 *`` seria ((1 +
   1) * 2). La notació amb forma de seqüència s'anomena postfixa o
   polaca (algunes calculadores la fan servir).

   .. solucio::
      ::

        (3 * (3 + 3))
        (3 - (4 + (5 * 1)))
        ((1 + 2) - 3)
        (((5 * 4) + 100) - ((2 * 3) * 10))

.. exercici::
   
   L'acció següent intenta convertir un ``string`` en un enter i si
   pot, retorna ``true`` i fa servir el paràmetre ``val`` per retornar
   el resultat. Si no pot, retorna ``false``. Per fer-la servir és
   necessari fer un ``include`` especial: ``#include <sstream>``.
   ::

      bool es_enter(string s, int& val) {
        istringstream sin(s);
        sin >> val;
        return !sin.fail();
      }

   Amb l'ajuda, doncs, de l'acció ``es_enter`` i l'acció ``opera`` de
   l'exercici anterior, fes un programa que rebi una seqüència de
   paraules (acabada en ``"."``) que poden ser interpretats com enters
   o operadors, en notació polaca. Un exemple de seqüència seria::

      3 2 1 + * .
      
   El programa he de tenir una pila d'enters, i ha de llegir la
   seqüència com si fós de ``string``\s. Donat un element, si aquest
   representa un enter s'ha d'apilar, i si no s'ha de cridar a
   ``opera`` amb el caracter corresponent (podem suposar que la
   seqüència només conté les 4 operacions amb enters). Un cop rebut
   l'últim element (el ``"."``), s'ha de mostrar el *top* de la pila
   per pantalla.

   .. solucio::
   
      El programa sencer quedarà així::

         #include <stack>
         #include <sstream>
         #include <iostream>
         using namespace std;
         
         bool es_enter(string s, int& val) {
           // ...
         }
      
         void opera(stack<int>& s, char op) {
           // ...
         }
         
         int main() {
           stack<int> P;
           string s;
           cin >> s;
           while (s != ".") {
             int x;
             if (es_enter(s, x)) {
               P.push(x);
             }
             else {
               opera(P, s[0]);
             }
             cin >> s;
           }
           if (!P.empty()) {
             cout << P.top() << endl;
           }
         }
   
  
Cues
====

cua
   *Queue* en anglès. Estructura de dades *First In First Out*, o FIFO
   (el primer que va entrar és el primer que surt).

Per fer servir cues hem de fer l'``include`` corresponent::

   #include <queue>

Per declarar una cua es fa com amb els altres contenidors de la STL::

   queue<int> S;

que declara una cua d'enters buida.

Operacions amb cues
-------------------

Les cues són estructures també molt bàsiques, i com les piles, només
tenen 3 operacions principals:

- **posar** (també *push*), que inserta un element al final de
  la cua.

- **treure** (també *pop*), que treu l'element del principi de la cua
  (el *front*).

- **consultar** el primer, per obtenir el *front*, el primer element.


Mètodes de la classe ``queue``
------------------------------

Constructors:

.. cpp:function:: queue<T>()
   
   Crea una cua buida.


.. cpp:function:: queue<T>(const queue<T>& s)
   
   Crea una cua a partir d'una altra.


Altre mètodes:

.. cpp:function:: int queue<T>::size() const
   
   Per obtenir el tamany.


.. cpp:function:: bool queue<T>::empty() const
   
   Per saber si la cua està buida. 


.. cpp:function:: T& queue<T>::front()
   
   Retorna una referència al primer element.


.. cpp:function:: T& queue<T>::back()
   
   Retorna una referència a l'últim element.


.. cpp:function:: void queue<T>::push(const T& t)
   
   Inserta un element al final de la cua.


.. cpp:function:: void queue<T>::pop()
   
   Elimina el primer element.


.. exercici::

   Determina el que mostrarà el següent codi per pantalla::

     queue<int> Q;
     for (int k = 3; k < 9; k++) Q.push(k);
     int& f = Q.front();
     f = 5;
     int& b = Q.back();
     b = 11;
     while (!Q.empty()) {
       cout << Q.front() << ' ';
       Q.pop();
     }
     
   .. solucio::

      La sortida serà::
  
         5 4 5 6 7 11
      
