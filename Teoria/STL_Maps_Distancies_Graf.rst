
Exemple: distàncies entre nodes d'un graf
=========================================

Ens donen un graf amb una estructura de dades com la següent (una
llista d'adjacència)::

   vector< list<int> > Graf;

Cada número és un node del graf i per a cada node tenim una casella
del vector ``Graf`` que conté una llista dels seus veïns.

Es tracta de fer un algorisme que calculi la distància mínima entre
dos nodes d'aquest graf. L'estratègia consisteix en calcular les
distàncies del node orígen a *tots* els nodes del graf i després
retornar només la que ens demanen (aquesta estratègia pot semblar molt
ineficient però no ho és tant). La capçalera de la funció serà::

  int distancia_minima(const vector< list<int> >& Graf, 
                       int orig, int desti)

Per fer el càlcul de les distàncies, farem servir les següents
estructures:

- Un vector amb les distàncies (de cada node a l'orígen).

- Un vector de Booleans per saber quins nodes del graf hem processat.

- Una cua amb els nodes pendents de visitar.

Els dos vectors tenen el mateix tamany que el graf, ja que necessitem
emmagatzemar la distància i el estat (processat o no) per a cada node.
Al principi de la funció, doncs, tenim::

  vector<int>  distancia(Graf.size(), -1);
  vector<bool> visitat(Graf.size(), false);
  queue<int>   pendents;

Al principi, insertarem a la cua de pendents el node orígen, i posarem
la seva distància a 0::

  distancia[orig] = 0; 
  pendents.push(orig);

Ara comença el bucle principal, en què es pren l'element de davant de
la cua, al que anomenarem ``n``, i per a cada un dels seus veïns
``i``, es calcula la seva distància amb ``orig`` (una unitat més que
la distància de ``n`` amb ``orig``) i després es posa a la cua de
pendents. Amb una excepció:

* Com que les distància al principi són -1, si veiem que un veí ``i``
  té una distància major o igual a 0, vol dir que ja hem posat la
  distància abans, i llavors no la modifiquem, ni el posem a la cua de
  pendents.

També, un cop processat cada element de la cua, s'ha de treure de la
cua. Una idea important és que només posem a la cua aquells elements
per als quals sabem la distància. Així quan arribi el moment de
processar-los, podrem actualitzar la distància dels seus veïns.

El bucle és, doncs, el següent. Aquest bucle acaba quan no queden més
elements per a processar, o sigui que la cua està buida::

  while (!pendents.empty()) {
    int n = pendents.front();
    list<int>::const_iterator i = Graf[n].begin();
    for (; i != Graf[n].end(); i++) {
      if (distancia[*i] < 0) {
	distancia[*i] = distancia[n] + 1;
	pendents.push(*i);
      }
    }
    pendents.pop();
  }

Finalment, s'ha de retornar el valor de la distància al node
``dest``. Si no es podia arribar a ell desde ``orig`` el valor de la
distància serà -1 (que ja serveix per indicar que no es pot accedir)::

  return distancia[dest];

El codi de la funció sencera és:

.. literalinclude:: ../src/08_Piles_Cues_i_Maps/graf.cpp
   :start-after: 1+
   :end-before: 1-


Problemes
---------

.. problema::

   Disposem del mapa del Metro de Barcelona i volem un programa que
   llegeixi el mapa del metro i calculi quin és el número mínim
   de parades que hi ha entre una estació i una altra. 

   El mapa està en un fitxer ``metro.txt`` i està en el següent
   format: una seqüència de parelles d'estacions que són veïnes (en
   cap ordre particular), separades per ``';'`` tal com::
 
      Hospital Clínic;Diagonal
      Diagonal;Verdaguer
      Fontana;Lesseps
      Lesseps;Vallcarca
      ...

   El programa primer ha de llegir el mapa de metro:

   1. Associar cada estació amb un número (si s'ha llegit per primer
      cop, se li assigna un nou número). Si és una estacio ja vista,
      s'ha de fer servir el número assignat prèviament.

   2. Tenir un vector de llistes a on cada casella del vector
      representa una estació i els element de la llista són les
      estacions veïnes a la xarxa de metro.

   Tot seguit, el programa ha de demanar el nom de dues estacions i
   calcular el número mínim d'estacions que hi ha entre una i l'altra.
   Per fer-ho, feu servir l'algorisme d'exemple sobre grafs.

   .. solucio::

      .. literalinclude:: ../src/08_Piles_Cues_i_Maps/metro.cpp

   
