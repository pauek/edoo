
Organització de taules en memòria
=================================

A un punter se li pot sumar i restar un enter
---------------------------------------------

Els punters, ja que són variables, també es poden modificar. Fins ara
hem vist que els podem assignar l'adreça d'una variable. Però també
se'ls pot sumar i restar un enter. Si un punter conté l'adreça d'un
caràcter (suposem que val ``13925``)::

  char c;
  char *pc = &c;

i li sumem 1::

  pc += 1;

llavors teòricament tindrem l'adreça ``13926``, que seria l'adreça del
caràcter situat just al costat de ``c`` a la memòria.

Però com hem vist abans, no tots els tipus de dades tenen el mateix
tamany. Llavors, si tenim un punter ``px``::

  int x;
  int *px = &x;

i volem fer-lo apuntar a l'adreça de memòria de l'enter del costat,
hauríem de sumar 4 en comptes de 1 (ja que els enters ocupen 4 bytes i
cada adreça és per a 1 byte). El propi C++, però, ja controla aquest
fet, i quan sumem 1 a un punter a enters, realment a l'adreça **se li
suma 4**.

.. exercici::

   Compila el següent programa:

   .. literalinclude:: ../src/05_Punters/ptr_inc.cpp

   i observa les adreces que surten per pantalla:

   .. solucio::
   
      Tal com deiem abans, aquest programa pot donar diferents
      resultats en funció de la màquina en què estiguem. En el meu
      ordinador el resultat és::
   
        0x7fff80ae1e9c
        0x7fff80ae1ea0
   
      Que indica que un enter ocupa 4 bytes (de ``9c`` a ``a0`` hi ha
      una distància de 4 en 
      `hexadecimal <http://en.wikipedia.org/wiki/Hexadecimal>`_ ).


Les caselles de les taules ocupen posicions de memòria consecutives
-------------------------------------------------------------------

En C++, les taules no són més que posicions de memòria consecutives
que contenen valors d'un mateix tipus. Quan declarem una taula, es
reserva un bloc en memòria amb tants bytes com el tipus de la casella
multiplicat pel tamany de la taula. Per exemple::

  bool conjunt[5] = { true, false, true, false, false };

reserva 5 bytes consecutius en memòria, ja que un ``bool`` hem vist
abans que ocupa 1 byte. La representació d'aquesta taula seria:

.. image:: img/memoria_taula.png
   :scale: 50

Quan fem servir un índex a una casella, doncs, el que succeeix és que
es fa servir la primera adreça de la taula i se li suma un enter que
és l'índex que posem, per tant escriure::

  conjunt[2]

vol dir agafar l'adreça base, sumar 2 (tercera casella), i accedir a
la posició resultant (ja sigui per modificar o per consultar). El fet
que els índexs de les taules facin servir com a primer element el 0
prové d'aquesta manera de emmagatzemar taules en memòria.

.. exercici::

   Quants bytes ocupa una taula de 10 floats?

   .. solucio::

      Si un ``float`` ocupa 4 bytes, una taula de 10 floats n'ocupa 40,
      tots seguits en memòria.


El nom d'una taula és un punter al seu primer element
-----------------------------------------------------

Quan declarem una taula, per obtenir la seva adreça (la primera adreça
que conté dades de la taula) tenim dues opcions. Una de senzilla, pel
que hem vist, seria treure l'adreça de la primera casella::

  int prim[5] = { 2, 3, 5, 7, 11 };
  int *p1;
  p1 = &prim[0];

Al cap i a la fi, ``prim[0]`` és una variable i per tant podem obtenir
l'adreça amb l'operador ``&``. L'altra manera que tenim és fer servir
el nom de la taula sense corxets::
 
  int *p2 = prim; // igual que p2 = &prim[0]

En C++, se segueix la convenció que el nom d'una taula és *un punter a
la seva primera casella*. De fet, això implica (tenint en compte que
sumar un enter a un punter incrementa la seva posició en funció del
tamany del tipus al que apunta) que una instrucció com::

  prim[2] = 5;

És equivalent a::

  int *p3 = prim;
  p3 += 2;
  *p3 = 5;

O, si ho posem tot junt::

  *(prim + 2) = 5;


.. exercici::
   
   Digues quina serà la sortida del següent programa::

     int main() {
       char T[4] = { 'a', 'b', 'c', 'd' };
       char *p = T + 3;
       cout << *(p - 1) << endl;
     }

   .. solucio::
   
      La sortida serà "c". El punter ``p`` s'inicialitza a la 4 casella
      de la taula (``'d'``), però al mostrar-lo per pantalla se li resta 1
      i es mira el valor d'aquella posició.

.. exercici::

   Digues quina serà la sortida del següent programa::

     int main() {
       int T[3] = { 5, 10, 15 };
       int *p = T;
       p += 2;
       *p = *p / 3;
       p--;
       *p = *p - 1;
       cout << T[0] << ", " << T[1] << ", " << T[2] << endl;
     }

   .. solucio::
   
      La sortida serà::
   
         5 9 5
   
      La raó és que ``p`` primer es posa a la primera casella, però de
      seguida se li suma 2 (i es coloca a la tercera). Llavors es
      divideix per 3 el valor de la casella (el 15), es decrementa ``p``
      (estem a la segona casella) i se li resta 1 al valor al que apunta
      ``p`` (el 10).


Els *strings* de C són punters a caràcters
------------------------------------------

El llenguatge C++ prové de C, i en C els punters a caràcter tenen un
significat especial. En C, s'assumeix que si tenim un punter a
caràcters, aquest punter apunta a una **taula de caràcters acabada en
0**. La taula té un sentinella perquè així sabem el seu tamany
implícitament. Si no hi hagués sentinella, no es pot transmetre el
tamany de la taula només amb el punter (que és una simple adreça).

Quan escrivim en un programa una paraula entre cometes dobles (``"``),
es crea una taula de caràcters amb un caràcter més del compte (per
posar el sentinella), i es retorna un punter a la primera casella::

  int main() {
    char *paraula = "hola";
  }

Les cadenes de caracters com aquestes són més bàsiques que el tipus
``string`` (que és una classe de C++). Però una cadena de caracters es
pot mostrar per pantalla fàcilment::

  int main() {
    char *paraula = "hola";
    cout << paraula << endl;
  }

La instrucció "``cout << paraula``" és com "``cout << "hola"``", que
hem fet servir sempre abans. Ara sabem, però, que realment ``cout``
rep un punter a caracter i l'interpreta com una taula.

.. exercici::

   Determina la sortida del següent programa:

   .. literalinclude:: ../src/05_Punters/petita_gran_frase.cpp

   .. solucio::

      La sortida del programa serà::
   
        Gran Frase
   
      La raó és que ``pf`` s'inicialitza al principi de la frase ``F``,
      però després se li sumen 7 valors (salta 7 lletres). Llavors el
      punter que rep ``cout`` és d'una taula acabada en 0 a partir de la
      ``'G'``, i per això mostra només aquesta part.


La classe ``string`` de C++, doncs, té un constructor que permet crear
un string a partir d'una cadena de caràcters de C, tal com en::

  string R("Rosebud");

i també té un mètode ``c_str`` que permet obtenir un punter a
caràcters a partir d'un ``string``::

  const char *p = R.c_str();

El tipus del punter no és "``char *``", però, ja que això ens permetria
modificar els caracters individuals. El punter és, de fet, a una taula
de caràcters constants (no modificables), per això el ``const``.

.. rubric:: Els arguments d'un programa

Quan executem un programa, aquest pot rebre arguments (com si fós una
"funció del sistema operatiu"). Per exemple, si tenim un programa
anomenat ``img_invert`` que inverteix una imatge, per dir-li al
programa quina imatge ha d'invertir, podem posar en la comanda, al
costat del nom del programa, un nom de fitxer [#nota4]_::

  C:\Mis Documentos\PBD\05_Punters> img_invert groucho.pgm

Aquests arguments (en aquest cas només ``groucho.pgm``) els rep la
funció ``main``, però amb la declaració de la funció que hem fet
servir fins ara no es poden obtenir, ja que declarem ``main`` sense
paràmetres (``int main()``). La declaració de ``main`` si volem
tenir accés als arguments és::

  int main(int argc, char *argv[]);

En aquesta versió, ``main`` rep un enter (``argc``, el número
d'arguments) i una taula ``argv`` de cadenes de caracters (paraules),
que són els arguments en sí. De fet, ``argv`` és una taula de punters,
ja que cada cadena és un punter. Els arguments, de fet, comencen a la
casella 1, ja que el primer argument (el 0) és el nom del programa.

El següent programa ``hola`` fa servir el primer argument
(``argv[1]``) i fa una salutació suposant que se li passa un nom:

.. literalinclude:: ../src/05_Punters/hola.cpp

.. exercici::

   Compila :download:`programa anterior <../src/05_Punters/hola.cpp>` i
   executa'l de manera que mostri per pantalla el següent::

     Hola, Groucho, què tal estàs?

   Com s'hauria d'executar per produir::

     Hola, Groucho Marx, què tal estàs?

   .. solucio::
 
      *[Aquesta solució està per fer...]*


.. exercici::

   Canvia el programa anterior perquè saludi a tots els noms que rep
   com a arguments. Si l'executem com::

     hola Groucho Chicco Harpo

   he de dir::

     Hola, Groucho, què tal estàs?
     Hola, Chicco, què tal estàs?
     Hola, Harpo, què tal estàs?

   .. solucio::
 
      *[Aquesta solució està per fer...]*


.. exercici::

   Fes un programa que mostri el número d'arguments i els arguments
   per pantalla, de manera que puguis comprovar quins arguments rep el
   programa. Anomena el programa ``see_args``. Comprova la sortida per
   a les següents comandes::

      see_args a1 a2 a3
      see_args "a1 a2 a3"
      see_args /x /w

   .. solucio::
 
      *[Aquesta solució està per fer...]*


La forma més ràpida de recórrer una taula és amb un punter
----------------------------------------------------------

Quan tenim punters, per recórrer les caselles d'una taula, és
suficient amb tenir un punter que comença a la primera casella de la
taula, i que es va incrementant d'un en un (anirà saltant de casella
en casella per la memòria). Per exemple, la següent funció calcula la
longitud d'una paraula (fem la suposició que és un *string* de C)::

  int longitud(char *paraula) {
    int L = 0;
    char *p = paraula;
    while (*p != 0) {
      L++;
      p++;
    }
    return L; 
  }

Si el punter que ens passen no és realment una taula amb sentinella 0,
el programa donarà un error d'execució gairebé segur.

Donat que el punter que ens passen com a paràmetre el podem fer servir
per recórrer la taula directament (no necessitem una variable més),
podem fins i tot escriure::

  int longitud(char *par) {
    int L = 0;
    while (*par != char(0)) {
      L++;
      par++;
    }
    return L;
  }

Des del programa principal, podriem cridar aquesta funció així::

  int main() {
    cout << longitud("Supercalifragilísticorl!") << endl;
  }

.. exercici::

   Escriu una funció que rebi 2 punters a enters. El primer és una
   taula acabada en -1 (l'orígen). El segon és l'adreça d'una taula
   amb un tamany igual o major que la primera. La funció ha de copiar
   els valors de la primera taula a la segona. Recorda posar el
   sentinella a la segona taula al final de tot.

   .. solucio::
      ::
   
        void copia(int *orig, int *dest) {
          while (*orig != -1) {
            *dest = *orig;
            orig++; dest++;
          }
          *dest = -1;
        }

.. exercici::

   Tradueix la següent funció, que concatena dues cadenes de
   caracters) per tal que faci servir punters en comptes de taules::

      typedef char Cadena[MAX_CHARS];
      
      void concatena(Cadena c1, Cadena c2, Cadena res) {
        int i = 0;
        while (c1[i] != char(0)) {
          res[i] = c1[i];
          i++;
        }
        int k = i;
        while (c2[i-k] != char(0)) {
          res[i] = c2[i-k];
          i++;
        }
        res[i] = char(0);
      }

   .. solucio::

      La funció és més fàcil amb punters perquè no s'ha de calcular
      l'índex a partir d'on ha d'anar la segona taula, el punter ``res``
      ja està situat a lloc::
  
        void concatena(char *c1, char *c2, char *res) {
          while (*c1 != char(0)) {
            *res = *c1;
            res++; c1++;
          }
          while (*c2 != char(0)) {
            *res = *c2;
            res++; c2++;
          }
          *res = char(0);
        }

