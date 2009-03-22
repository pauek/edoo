
================
Memòria Dinàmica
================

.. rubric:: Objectius

- Escriure programes que utilitzen correctament els operadors ``new``
  i ``delete`` per reservar memòria de tipus qualssevol.

- Desciure els errors típics derivats de la gestió incorrecta de la memòria.

- Descriure la utilitat del destructor en el context de la memòria
  dinàmica.

- Implementar classes que continguin punters com a membres i reservin
  memòria dinàmicament.


Gestió de la memòria
====================

La gestió dinàmica de la memòria permet sobrepassar certes limitacions
----------------------------------------------------------------------

Quan declarem una variable en un programa:

A. es fa servir una zona de memòria amb un tamany màxim força petit per
   col·locar-la; i

B. la porció de memòria que ocupava la variable desapareix quan la
   funció on hem declarat la variable finalitza.

Necessitem fer servir memòria dinàmica, doncs, quan:

A. el tamany de la zona que volem utilitzar és gran, o

B. algunes dades del nostre programa han de sobreviure a la funció a
   on són creades.

L'operador ``new`` reserva memòria i retorna un punter
------------------------------------------------------

Per reservar memòria de forma dinàmica, farem servir l'operador
``new``, que es pot cridar de 3 formes diferents (si bé s'assemblen bastant):

1. ``new B[n]``: on ``B`` és un tipus bàsic i ``n`` és un
   enter. Aquesta versió retorna un punter a una taula de ``n``
   elements del tipus ``B``. El valor de ``n`` pot provenir d'una
   variable, no ha de ser una constant.

2. ``new C(...)``: on ``C`` és el nom d'una classe (o un ``struct``) i
   els paràmetres que l'acompanyen són els d'un constructor de la
   classe ``C``.

3. ``new D[n]``: on ``D`` és el nom d'una classe *amb constructor per
   defecte* i ``n`` un enter. Es retorna un punter a una taula de
   ``n`` objectes de tipus ``D`` inicialitzats amb el constructor per
   defecte. Si aquest no existeix, hi haurà un error de compilació. El
   valor de ``n`` pot no ser una constant.

En tots 4 cassos, ``new`` retorna una adreça a la zona de memòria
reservada, que s'ha de guardar en un punter del tipus pertinent.

Vegem exemples de cada cas. El següent programa reserva espai per a
una taula d'1000000 d'enters, i després l'omple amb els enters de l'1
al 1000000. És un exemple del cas 1::

  int main() {
    int *pI, *p;
    pI = new int[1000000];
    p = pI;
    for (int k = 1; k <= 1000000; k++) {
      *p = k;
      p++;
    }
  }

Un exemple del segon cas pot ser el següent. Si tenim una classe
``Punt3D`` que representa punts tridimensionals amb la següent
declaració::

  class Punt3D {
    // ...
  public:
    Punt3D(); // inicialitza amb (0, 0, 0)
    Punt3D(double x, double y, double z);
    double get_x() const;
    double get_y() const;
    double get_z() const;
  };

Podem reservar un ``Punt3D`` en memòria dinàmica així::

  Punt3D *p = new Punt3D(0.0, 1.0, 0.5);
  cout << "El punt és: (" 
       << p->get_x() << ", " 
       << p->get_y() << ", "
       << p->get_z() << ")" << endl;

L'últim cas seria si volem crear una taula de punts, per
exemple::

  int npunts;
  cout << "Numero de punts? ";
  cin >> npunts;
  Punt3D *pT = new Punt3D[npunts];




L'operador ``delete`` allibera la memòria que indica un punter
--------------------------------------------------------------








   
