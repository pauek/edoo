
Quan es gestiona la memòria dinàmicament és fàcil cometre certs errors
----------------------------------------------------------------------

Els tres errors més típics es comenten en les seccions següents.

Accedir a un objecte a través d'un punter no inicialitzat
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""

Si declarem un punter però no hi posem cap adreça, el punter apunta a
algun lloc igualment. El problema és que l'adreça a la que apunta pot
ser qualsevol. Si el programa intenta accedir a aquesta adreça,
típicament serà abortat pel sistema operatiu amb un missatge que a
Windows és similar a: "Este programa ha realizado una operación
inválida y se cerrará".

Un exemple d'aquest problema seria::

  Data *d;
  d->escriu(cout);

Com es pot veure, just després de declarar el punter es fa servir per
invocar el mètode escriu sense haver-hi posat cap adreça vàlida. Això
provoca el problema.

El mateix problema apareix si posem el valor 0, ja que l'adreça 0 de la
memòria no és accessible per a cap programa.


No alliberar la memòria que ja no es fa servir
""""""""""""""""""""""""""""""""""""""""""""""

En un programa a on tota la memòria que es reserva es fa servir fins
al final, no és necessari alliberar-la, ja que quan el programa acaba,
la memòria que tenia reservada s'allibera automàticament. A
l':ref:`exemple anterior <seq_int>` no feiem servir ``delete`` per
aquest motiu precisament.

Però si un programa utilitza memòria reservada dinàmicament, és
possible que ja no li faci falta més endavant. Quan això succeeix, la
memòria s'ha d'alliberar. Si no ho fem, el sistema operatiu creu que
encara la utilitzem, i la té marcada com a "propietat nostra". Si li
demanem més memòria, ens donarà una altra porció
diferent. Eventualment, si el programa va demanant memòria sense
allibrerar la que no fa servir, acapararà tota la memòria del sistema
(això fa que l'ordinador vagi molt lent i que no es puguin executar
altres programes). Aquest tipus d'error s'anomena una "fuita de
memòria" (un *memory leak*).

Un exemple senzill a on això passa és un programa com Photoshop. Quan
obrim una imatge amb Photoshop, el programa reserva memòria per poder
treballar amb la imatge. Si la tanquem, allibera aquesta memòria. Si
no ho fés, en una sessió en que obrim 25 o 30 imatges consecutivament
(o sigui, no totes alhora), de seguida s'ompliria la memòria de
imatges que ja no estan obertes ni s'estan utilitzant, i s'hauria de
tancar el programa i tornar-lo a obrir (perquè quan el tanques, tota
la memòria s'allibera per força). Això seria inacceptable i per tant
és clar que Photoshop allibera la memòria que no fa servir.


Alliberar una posició de memòria dues vegades
"""""""""""""""""""""""""""""""""""""""""""""

Si per error nostre, en un programa fem un ``delete`` de la mateixa
adreça dues vegades, el programa donarà un error d'execució. Un cop
alliberada una adreça de memòria, *és un error alliberar-la un altre
cop*. El següent programa::

  int main() {
    Data *d = new Data(23, 1, 1789);
    delete d;
    delete d;
  }

dóna un error d'execució. Aquest tipus d'error és fàcil de cometre
quan copiem punters, ja que si tenim una mateixa adreça en dos llocs
diferents, és més fàcil caure al parany de cridar a ``delete`` amb els
dos.
