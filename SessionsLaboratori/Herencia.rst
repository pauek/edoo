
.. tema:: lab.he


===============================
Guió de pràctiques: Herència
===============================

.. rubric:: Objectius

   - Crear programes senzills amb Qt.


Inversió d'imatges super-fàcil
=================================

En aquesta sessió de pràctiques, farem un programa molt senzill amb Qt
que inverteix una imatge, és a dir, inverteix el color de cada píxel
(si un píxel és blanc, passa a negre i si és groc, passa a blau). 

El primer que hem de fer és crear un projecte amb Qt fent servir la
opció de menú *File* |-->| *New file or project...*. Això mostra el
quadre de diàleg següent, a on hem d'escollir "Empty Qt Project":

.. image:: img/qt_new_empty_project.png
   :align: center
   :scale: 75

El projecte s'ha de situar en algun directori i li direm
``inverteix_imatge`` (el nom del projecte no pot tenir espais ni
caracters extranys).

Ara cal afegir un fitxer codi nou, també amb *File* |-->| *New file or
project...*. Ara caldrà escollir la opció de "C++ Source File" (un
fitxer .cpp). 

.. image:: img/qt_new_cpp_source_file.png
   :align: center
   :scale: 75

Al nou fitxer li hem de posar de nom ``main.cpp`` i l'afegim al
projecte.

El resultat és un projecte com el següent:

.. image:: img/qt_project_view_inverteix_imatge.png
   :align: center
   :scale: 75

En el fitxer main posarem el següent codi::

   #include <QImage>
   
   int main() {
     QImage I("test.jpg");
     I.invertPixels();
     I.save("test_i.jpg");
   }

Ara compila el projecte amb ``Ctrl+B`` o amb *Build* |-->| *Build
Project ``inverteix_imatge``*. Si executes el projecte (amb
``Ctrl+R``) el programa no farà res, perquè no hi ha cap imatge
``test.jpg``. Per poder veure el resultat del programa has d'anar a un
directori que hi haurà al costat del directori del projecte amb un
sufix ``-build-desktop`` (si has seguit els passos fins aquí serà
``inverteix_imatge-build-desktop``) i a dins veuràs que hi ha un
executable anomenat ``inverteix_imatge``. Copia una imatge de prova
amb el nom ``test.jpg`` en aquest directori i executa el programa fent
doble clic. Veuràs que apareixerà una nova imatge invertida amb el nom
``test_i.jpg``.

.. image:: img/qt_exec_inverteix_imatge.png
   :align: center
   :scale: 75

No és fantàstic? El programa ocupa només 3 línies: es construeix un
object ``QImage``, i en el constructor se li diu de quin fitxer ha de
treure la imatge, i es crida a un parell de mètodes que la inverteixen
i la guarden amb un altre nom. Aquest programa treu partit la classe
``QImage`` de la llibreria Qt per fer una operació força complexa.

.. exercici::
   
   Si situes el cursor sobre de la paraula ``QImage`` en el codi font
   i prems la tecla F1, veuràs que surt l'ajuda de la classe
   ``QImage``. Busca un mètode ``copy`` (el que rep 4 enters). Observa
   el tipus de retorn. Modifica el programa, doncs, per guardar una
   zona de 100x100 píxels de la part esquerra a dalt de la imatge
   ``test.jpg``. Guarda-la amb el nom ``tros.jpg``.

Escollir el fitxer amb un quadre de diàleg
==========================================

Pel fet que el programa és senzill, cada cop que volguem aplicar-lo a
una imatge nova, hem de posar el nom  ``test.jpg`` a la imatge o
recompilar el programa posant un nom diferent. No estaria millor que
el programa ens demani quin fitxer volem invertir?

Per fer això amb Qt haurem de fer dues modificacions:

- La primera té a veure amb el fet que si volem que surtin finestres
  en el nostre programa, hem de crear un objecte ``QApplication``.

- La segona és l'ús del quadre de diàleg de fitxers en sí.

Primera modificació: afegir un ``QApplication``
-----------------------------------------------

Anem per la primera. Cal afegir el següent:

- Modificar la funció ``main`` perquè tingui dos paràmetres així::

     int main(int argc, char *argv[]) {
       // ...
     }

- Crear un objecte al principi del ``main`` de la classe
  ``QApplication`` (i per tant afegir ``#include <QApplication>`` a
  dalt de tot)::

       QApplication app(argc, argv);

  Aquest objecte rep en el seu constructor els paràmetres que hem
  posat al ``main``.

Segona modificació: fer servir ``QFileDialog``
----------------------------------------------

Un quadre de diàleg per a fitxers ens permet escollir un fitxer, i té
la següent pinta:

.. image:: img/qt_file_dialog.png
   :align: center
   :scale: 75

Des del programa, obrim el quadre i si l'usuari escull un fitxer, el
quadre ens retorna el nom del fitxer complet. Si l'usuari prem
"Cancel", el quadre ens informa que s'ha cancel·lat la tria.

Per posar el quadre s'han de seguir els passos següents:

- Crear un objecte ``QFileDialog`` (mai abans de ``QApplication``), i
  per tant hem de posar a dalt de tot ``#include
  <QFileDialog>``. Anomena l'objecte ``F``.

- Invocar el mètode ``exec`` del quadre, i mirar el valor que
  retorna. Es pot considerar com un ``bool``: si ``exec`` retorna ``true``,
  l'usuari ha escollit un fitxer; si retorna ``false``, ha cancel·lat.
  En el nostre cas, si l'usuari cancel·la, no hem de fer res, per tant
  posarem::

     if (F.exec()) {
       // codi per invertir la imatge escollida
     }

- Obtenir el nom del fitxer que s'ha seleccionat. Per fer això hem de
  cridar el mètode ``seletedFiles`` de ``QFileDialog``. Aquest mètode
  retorna una llista de fitxers (un objecte ``QStringList``), ja que
  un quadre de diàleg en general permet seleccionar més d'un
  fitxer. Per tant, posarem::

     QStringList fitxers = F.selectedFiles();
     
- Per obtenir un ``QString`` que és el nom del fitxer seleccionat, hem
  de mirar el primer element de la llista, el de la posició 0, amb el
  mètode ``at``::

     QString nom = fitxers.at(0);

- Ara ja podem crear l'objecte ``QImage`` com abans, però posant
  ``nom`` com a paràmetre del constructor, en comptes de
  ``test.jpg``::
    
     QImage I(nom);

- Ara vindria la inversió com abans, i finalment hem de guardar la
  imatge amb un nom diferent (perquè si no ens carreguem la imatge
  original). Per fer això hem d'afegir al nom una ``"_i"``. La manera més fàcil és cridar al mètode ``replace`` de
  ``QString`` (n'hi ha vàrios), que permet reemplaçar un tros del
  ``nom`` amb un altre. Si fem::

     nom.replace(".", "_i.");

  estem canviant allà on posa ``"."`` per ``"_i."``, que té
  l'efecte desitjat. Si el nom era ``gat.jpg``, ara serà
  ``gat_i.jpg``. Un cop fet això, podem cridar el mètode ``QImage::save`` com
  abans.

Invertir múltiples imatges
==========================

Ja posats, podem fer que el programa inverteixi vàries imatges, no
només una. En un quadre de diàleg de fitxers, en general, per
seleccionar més d'un fitxer s'ha de clicar el nom del fitxer mentre es
prem la tecla ``Ctrl``.

Per modificar el programa, haurem de:

- Indicar al ``QFileDialog`` que volem poder seleccionar més d'una
  imatge.

- Fer una iteració amb cada una de les imatges seleccionades i
  invertir-la, tal com fem ara amb una de sola.

Seleccionar vàries imatges a un ``QFileDialog``
-----------------------------------------------

Això és senzill, només hem de "configurar" el ``QFileDialog`` abans de
cridar-lo amb ``exec``. Just després de ser creat, al principi del
programa, posem::

  F.setFileMode(QFileDialog::ExistingFiles);

Mira l'ajuda per al mètode ``setFileMode`` i veuràs que accepta un
paràmetre de tipus ``QFileDialog::FileMode``, que és un enumerat. La
opció per múltiples fitxers és el número 3,
``QFileDialog::ExistingFiles``.

Fer una iteració amb les imatges
--------------------------------

Un cop el quadre de diàleg ha retornat, en comptes d'invertir una
imatge, la idea és fer una iteració com::

  for (int i = 0; i < ...; i++) {
    QString nom = ...; // nom de la imatge 'i'
    QImage I(nom);
    ...
  }

La llista té un mètode ``at`` que ja hem vist que permet obtenir
l'element ``i``-èssim, però ens faltaria un mètode per determinar el
tamany de la llista. Aquest mètode és ``QStringList::size``. Modifica
doncs el programa i compila'l. Comprova que pots invertir almenys 2
imatges.

Un quadre de diàleg personalitzat
=================================

En aquesta secció farem un programa que ens demana el nom i ens
saluda, fent servir un quadre de diàleg fet per nosaltres. El programa
principal serà molt senzill::

  #include <QApplication>
  #include "textdialog.h"
  
  int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TextDialog td("Escriu el teu nom");

    if (td.exec()) {
      QString salutacio = "Com estàs, ";
      salutacio += td.text();
      salutacio += ", ets un gran programador";
  
      QMessageBox missatge;
      missatge.setWindowTitle("Salutacio");
      missatge.setText(salutacio);
      missatge.exec();
    }
  }

Aquest programa fa servir 3 classes: ``QApplication``, que coneixem;
``QMessageBox``, que serveix per mostrar petites informacions; i
finalment, ``TextDialog`` que és la que farem nosaltres.

Quan engegues el programa, surt una finesta com:

.. image:: img/qt_textdialog_your_name.png
   :align: center
   :scale: 75

Un cop has posat el nom, et surt un missatge:

.. image:: img/qt_textdialog_greetings.png
   :align: center
   :scale: 75

La part d'utilització de ``QMessageBox`` és força
auto-explicativa. ``QMessageBox`` és un quadre de diàleg a on només
pots prémer un botó i poc més. Aquest tipus de quadres es fan servir
per alertar l'usuari d'alguna cosa que ha succeït. En el nostre cas se
li posa un títol (amb ``setWindowTitle``) i un text (amb
``setText``). Finalment es mostra amb ``exec``.

El nostre quadre ``TextDialog``
-------------------------------

Per començar crearem dos fitxers de codi font nous: ``textdialog.h`` i
``textdialog.cpp``. La declaració de la classe serà (situada al fitxer
``textdialog.h``)::

  class TextDialog : public QDialog {
    QLineEdit *_edit;
    QPushButton *_ok, *_cancel;
  public:
    TextDialog(QString titol, QWidget *parent = 0);
    QString text() const;
  };

La declaració és simple, el nostre quadre té 3 atributs: una caixeta
d'edició i dos botons, tots ells punters. El constructor rep 2
paràmetres, un *string* (el text del títol) i el ``QWidget``
pare. Totes els elements en Qt tenen un punter a la finestra pare
(que les conté), tot i que aquest pot ser 0 (no apunta enlloc). Com
que la classe ``QDialog`` rep aquest punter com a paràmetre del
constructor, nosaltres l'hem de posar al nostre constructor, també.

La implementació de la classe comença amb els ``#include``s::

  #include <QDialog>
  #include <QLineEdit>
  #include <QPushButton>
  #include <QGridLayout>

Ens cal implementar 2 mètodes: el constructor i ``text``. Comencem amb
el constructor::

  TextDialog::TextDialog(QString titol, QWidget *parent) 
    : QDialog(parent)
  {
    setWindowTitle(titol);
    
    _edit = new QLineEdit;
    _ok = new QPushButton("D'acord");
    _cancel = new QPushButton("Cancel.la");

    QGridLayout *graella = new QGridLayout;
    graella->addWidget(_edit, 0, 0, 1, 2);
    graella->addWidget(_ok, 1, 0);
    graella->addWidget(_cancel, 1, 1);
    setLayout(graella);
  }

Abans de començar, es fa servir una llista d'inicialització per cridar
el constructor de la classe ``QDialog`` amb el paràmetre ``parent``
(per indicar de qui és "fill" el quadre de diàleg). La primera
instrucció invoca un mètode de la classe ``QDialog``, que permet
canviar el títol, i posa el títol passat com a paràmetre.

Les tres següents línies reserven memòria i inicialitzen els 3
atributs, i les següents 5 línies creen un ``QGridLayout`` (un
distribuidor de tipus graella) i col·loquen els objectes en les seves
caselles. Les crides indiquen el número de casella començant
per 0. L'objecte ``_edit`` és especial: es col·loca a la casella (0, 0) però en
comptes d'ocupar només una casella n'ocupa 1 en vertical i 2 en
horitzontal, per això la crida té 4 números. La crida a ``setLayout``
assigna el distribuidor al quadre de diàleg.

La implementació del mètode ``text`` és senzilla, només s'ha de
retornar el valor que conté l'objecte ``_edit``. Si mirem 

.. |-->| unicode:: U+2192

   

