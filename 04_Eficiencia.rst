
=======================
Eficiència d'Algorismes
=======================

Objectius
=========

- Descriure el concepte d'ordre de creixement.

- Enumerar els ordres de creixement típics.

- Descriure la utilitat dels ordres de creixement en la comparació
  d'algorismes.

- Analitzar l'eficiència d'un algorisme senzill.


Anàlisi d'algorismes
====================

Anàlisi d'algorismes
  Estudi teòric sobre els programes d'ordinador en termes de la seva
  eficiència (velocitat) i ús de recursos.

Velocitat 
  Temps *real* que triga un algorisme en produir el seu resultat

Exemple: Ordenació
------------------

El problema d'ordenar una seqüència de nombres es pot enunciar
explicitant quina és l'entrada de l'algorisme i quina n'és la sortida:

**Entrada:** Una taula de nombres :math:`a_1, a_2, \ldots, a_n`. 

**Sortida:** Permutació dels nombres :math:`a_1', a_2', \ldots, a_n'` tal
que :math:`a_1' < a_2' < \ldots < a_n'`.


Ordenació per inserció
----------------------

Una forma de resoldre aquest problema seria implementar la ordenació
per inserció::

  const int N = 100;
  typedef int Vector[N];
  
  void ordena_insercio(Vector& A) {
    int j, k, i;
    for (j = 2; j < N; j++) {
      k = A[j];
      i = j - 1;
      while (i >= 0 && A[i] > k) {
        A[i+1] = A[i];
	i--;
      }
      A[i+1] = k;
    }
  }

La ordenació per inserció funciona suposant que hi ha dues zones en la
taula: la zona baixa (amb índexs petits), que està ordenada, i la zona
alta, que està per ordenar. Cada pas de l'algorisme agafa el primer
element de la zona alta i llavors mou elements de la zona ordenada per
tal d'obrir-li una posició al lloc que li pertoca. L'element es coloca
llavors al forat que ha quedat. Aquesta operació amplia la zona
ordenada en 1 element. Aplicant-la repetidament, ordenarem la taula.

Temps d'execució de l'algorisme
===============================

Ens preguntem: quan triga aquest algorisme en executar-se?

De fet, el temps d'execució depèn de molts factors:

- De la taula concreta que rep com entrada. Si aquesta taula ja està
  ordenada, per exemple, el procés és molt ràpid. Si la taula està
  ordenada al revés, el procés és molt més lent.

- Del tamany de la taula: no es triga el mateix en ordenar una taula
  de 100 elements que una de 10000 elements.

- De la velocitat de la màquina amb què fem els càlculs. El nostre
  algorisme acabarà molt més ràpid si l'executem en un ordinador té
  una freqüència de rellotge més alta (i pot executar més instruccions
  per segon).

Anàlisi dels diferents temps d'execució
=======================================

En general, es pren el tamany de l'entrada :math:`n` com a paràmetre
clau (en el nostre cas el tamany de la taula), i es dóna un valor únic
al temps d'execució d'un algorisme, que és llavors una funció
:math:`T(n)` del tamany de l'entrada. També se suposa que l'algorisme
és correcte per a qualsevol entrada (dóna sempre un resultat
correcte).

Donat que el temps d'execució real de l'algorisme depèn de molts
factors, hi haurà en realitat molts temps diferents (tindrem una
distribució de valors). Si suposem que executem l'algorisme en el
mateix ordinador, podem resumir tots aquests diferents valors en un de
sol de 3 maneres:

- *Pitjor cas*: li donem a :math:`T(n)` el valor del temps més gran que
  triga l'algorisme per a entrades de tamany :math:`n`.

- *Cas mitjà*: li donem a :math:`T(n)` el valor de la mitjana dels
  temps d'execució per a totes les entrades de tamany :math:`n`.

- *Cas millor*: li donem a :math:`T(n)` el valor del temps més petit
  que triga per a entrades de tamany :math:`n`.

L'anàlisi del millor cas és, de fet, inútil. Si el valor de la funció
:math:`T(n)` descriu el temps més curt d'execució de l'algorisme, és
com no saber-ne res. La raó és que l'algorisme pot ser que ordeni
certa taula concreta molt ràpidament (perquè té la solució
precalculada, per exemple) i en canvi la majoria de les altres les fa
molt malament. Llavors, el temps d'execució :math:`T(n)` ens semblaria
molt bo quan en realitat no ho és.

El temps mitjà és un referent millor. Si :math:`T(n)` és la mitjana
dels temps d'execució, aquest valor reflexa de forma més acurada el
comportament de l'algorisme en el conjunt sencer dels cassos. Però tot
i ser útil, no ens dóna garanties. Un algorisme amb temps mitjà
:math:`T(n) = 5n` pot ser molt més lent en cassos concrets. Necessitem
doncs, una manera d'assegurar que el temps d'execució és menor que un
cert valor, i poder *certificar-ne* la seva eficiència.

És per això que en general es fa servir el pitjor cas. Si :math:`T(n)`
representa el valor màxim del temps que triga l'algorisme, aquest
valor és una cota superior al temps que trigarà, i per tant tenim la
garantia que el temps serà aquest o menor. Amb el pitjor cas tenim la
seguretat de poder fer afirmacions sòlides sobre el temps d'execució
de l'algorisme.

Anàlisi assimptòtica
====================

Però encara tenim el problema de que un algorisme lent executat en un
ordinador ràpid pot trigar menys que un algorisme ràpid executat en un
ordinador lent. Com podem comparar algorismes diferents sense
necessitat de tenir un ordinador amb una velocitat de referència?

La resposta està en la idea no analitzar els valors concrets, sinó les
*tendències* d'aquests valors. Com que disposem dels valors del temps
d'execució :math:`T(n)` per a entrades de diferents tamanys, el que
farem és mirar com creix el temps d'execució quan augmentem el valor de
:math:`n`. El que importarà, doncs, no són els valors precisos sobre
els temps sino quin *ordre* de creixement tenen. 

Límits
------

En matemàtiques, la noció de límit ens permet obtenir el valor d'una
funció quan el seu paràmetre creix. Tenim els següents límits bàsics:

.. math::

   \lim_{n\rightarrow\infty} n = \infty

.. math::

   \lim_{n\rightarrow\infty} \log n = \infty

.. math::

   \lim_{n\rightarrow\infty} \frac{1}{n} = 0

.. math::
   
   \lim_{n\rightarrow\infty} \frac{\log n}{n} = 0

El primer límit és, de fet, una tautologia, perquè per definició, la
variable :math:`n` tendeix a :math:`\infty` en un límit. I el segon es
pot demostrar, però la demostració no és tan senzilla. De fet el
logaritme és la funció que creix cap a :math:`\infty` de la forma més
lenta possible (però hi arriba).

En els límits a on hi ha una divisió, es pot pensar que hi ha una
cursa entre el denominador i el numerador i depenent del guanyador
tindrem un valor diferent: :math:`\infty` si guanya el numerador,
:math:`0` si guanya el denominador i una constant si queden empatats.

Quan una funció :math:`f(n)` "guanya" a una altra funció :math:`g(n)`
en un límit d'aquests, podem escriure:

.. METER AQUÍ LA COMPARACION

.. math::

   f(n) < g(n)


Fent servir la noció de límit, es pot classificar a les funcions en
grups fixant-nos en qui guanya a qui.


.. exercici::
   
   Busca un argument per demostrar que

   .. math::
      
      \lim_{n\rightarrow\infty} \frac{e^n}{n} = \infty

.. exercici::

   Calcula el següent límit

   .. math::

      \lim_{n\rightarrow\infty} 
      \frac{2 (n + 1) (\log n + 7)}{ 7n^2 + 1 }

Notació assimptòtica
--------------------

Quan analitzem el comportament d'una funció de :math:`n` quan
:math:`n` creix, ens hem de fixar en el seu *ordre*, és a dir, el valor
de l'exponent més alt que veiem. Si la funció és

.. math::

   T(n) = 3 n^3 + 90 n^2 - 5n + 6046

el valor que realment domina quan :math:`n` creix és
:math:`n^3`. L'obtenim així:

- Expressant al funció com un polinomi.

- Descartant els termes d'ordre inferior del polinomi.

- Ignorant les constants multiplicatives.

Per expressar aquesta operació farem servir la notació :math:`\Theta`,
que donada una funció, indica el seu l'ordre de creixement entre
parèntesis:

.. math::

   3 n^3 + 90 n^2 - 5n + 6046 = \Theta(n^3)

El valor :math:`\Theta(n^3)` indica, de fet, el conjunt de totes les
funcions que tenen un terme cúbic com a màxim i qualsevol valor en les
constants. Totes elles són equivalents en aquest tipus d'anàlisi. 

.. exercici::

   Determina l'ordre de creixement de les següents funcions: 

   .. math::
   
      f_1(n) = 14n(n-1)

   .. math::

      f_2(n) = \frac{3n^2 - 15}{5n}

   .. math::

      f_3(n) = \frac{8n^7 + n^4}{3n^2-17}


Definició matemàtica de :math:`\Theta`
""""""""""""""""""""""""""""""""""""""

La definició de :math:`\Theta` és la següent 



Comparació d'algorismes
-----------------------

El gran avantatge dels ordres de creixement és que ens permeten comparar
algorismes directament. Un algorisme A amb un temps d'execució :math:`\Theta(n^3)`
*és sempre pitjor* que un algorisme B amb temps :math:`\Theta(n^2)`. Per
la definició matemàtica de :math:`\Theta`, sempre hi haurà un valor de
:math:`n` a partir del qual A triga més que B, fins i tot si A
s'executa en un ordinador més ràpid que el de B.

Vegem un exemple concret. Suposem que :math:`T_A(n) = 2 n^2` i que
:math:`T_B(n) = 50 n \log n`, a on les dues funcions mesuren el número
d'instruccions totals necessàries per produir la sortida. L'ordinador
d'A és capaç d'executar :math:`10^9` d'instruccions per segon, i
l'ordinador de B només :math:`10^7` (un factor 100). Malgrat aquest
gran avantatge de A sobre B, si el tamany de l'entrada :math:`n` és
d'un milió, els temps reals d'execució de cada algorisme seràn:

.. math::
   
   t_A = \frac{2\times (10^6)^2\ \text{instruccions}}
              {10^9\ \text{instruccions}/\text{segon}} = 2000\ \text{segons}

.. math::

   t_B = \frac{50\times 10^6 \log 10^6\ \text{instruccions}}
              {10^7\ \text{instruccions}/\text{segon}} \approx 100\ \text{segons}

És clar, doncs, que l'avantatge de A no ha servit per a res. Malgrat
l'ordinador de A és 100 vegades més ràpid, l'algorisme A s'executa
finalment 20 vegades més lentament que B, per a una entrada
suficientment gran. La clau està els ordres de creixement,
:math:`T_A(n) = \Theta(n^2)` i :math:`T_B(n) = \Theta(n \log n)`, ja
que l'ordre de A és major que el de B.

Ordres de creixement típics
---------------------------

Cotes superiors: notació :math:`O`
----------------------------------


Anàlisi de la ordenació per inserció
====================================


