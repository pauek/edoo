
====================
Anàlisi d'eficiència
====================

Objectius
=========

- Comparar execucions d'algorismes per diferentes entrades.

- Analitzar l'eficiència d'algorismes.


Anàlisi empíric d'algorismes
============================

Per mesurar el temps d’execució d’un programa en DevC++, podem fer servir la funció clock() de la llibreria time.h, que ens retorna el temps que ha passat des de l’inici de l’execució d’un programa.

A continuació teniu un exemple d’ús d’aquesta funció. Si el programa del qual volem mesurar el temps d’execució és aquest::

  //Un programa d’exemple
  #include <iostream>
  #include <stdlib.h>
  
  using namespace std;
  
  int main (int argc, char *argv[])
  {
    int a,i;
    
    a=0;
    for (i=0; i<1000000; i++)
      a=a+i;
    system("PAUSE");
    return 0;
  }

Les modificacions que hem de fer són::

  //Un programa d’exemple per mesurar el temps
  #include <iostream>
  #include <stdlib.h>
  #include <time.h>
  
  using namespace std;
  
  double TempsExecucio(void)
  {
    return clock()/double(CLK TCK);
  }
  
  int main (int argc, char *argv[])
  {
    int a,i;
    double t1=TempsExecucio();
    
    cout << "Temps inici: "<< t1 << endl;
    a=0;
    for (i=0; i<10000000; i++)
      a=a+i;
    double t2=TempsExecucio();
    cout << "Temps finalitzacio: "<< t2 << endl;
    cout << "Temps execucio: "<< t2-t1 << endl;
    system("PAUSE");
    return 0;
  }

Es tracta d’estudiar empiricament els algorismes d’ordenació per selecció i per inserció. Per això mesurareu els temps d’execució dels programes amb diferents dades d’entrada, i compareu aquests resultats empírics que ens permetrà treure conclusions sobre l’eficiència dels diferent algorismes.

Per exemple, el següent algorisme ordena una taula mitjançant el mètode de selecció::

  #include <iostream>
  #include <stdlib.h>
  #include <time.h>

  using namespace std;

  const int N=30000;

  typedef int TaulaEnters[N];

  void omplirTaula(TaulaEnters& t)
  {
    int i;
    
    for(i=0; i<N; i++)
      t[i]=i;
  }

  void ordenarSeleccio(TaulaEnters& t)
  {
    int j,k,menor,aux;
    
    j=0;
    while (j<N-1){
      menor=j;
      k=j+1;
      while (k<N){
        if (t[k] < t[menor]) menor=k;
        k=k+1;
      }
      aux=t[j];
      t[j]=t[menor];
      t[menor]=aux;
      j=j+1;
    }
  }

  double TempsExecucio(void)
  {
    return clock()/double(CLK TCK);
  }

  int main (int argc, char *argv[])
  {
    TaulaEnters t;

    cout << "Inici!";
    omplirTaula(t);
    double t1=TempsExecucio();
    cout << "Temps inici ordenacio: "<< t1 << endl;
    ordenarSeleccio(t);
    double t2=TempsExecucio();
    cout << "Temps finalitzacio ordenacio: "<< t2 << endl;
    cout << "Temps ordenacio per selecio: "<< t2-t1 << endl;
    system("PAUSE");
    return 0;
  }

.. exercici::

   Doneu diferents valors a la constant N (per exemple 20000, 40000, 60000, 80000, 100000) i preneu nota dels temps d’execució per cada valor de N.

.. exercici::

   Feu una altra versió de l’accio omplirTaula per tal d’omplir la taula amb valors decreixents. Podeu fer servir aquesta versió::
   
     void omplirTaula2(TaulaEnters& t)
     {
       int i;
       for(i=0; i<N; i++)
         t[i]=N-i;
     }

   Repetiu les mesures del temps d’execució del programa amb aquesta nova versió d’omplir taula.

.. exercici::

   Feu una altra versió de l’acció omplirTaula. Aquest cop cal que ompli la taula amb valors aleatoris. Repetiu les mesures del temps d’execució del programa amb aquesta nova versió d’omplir taula. Podeu fer servir aquestes dues funcions (cal incloure la capçalera stdlib.h)::

     //genera un nombre enter aleatori entre 1 i n

     int randn(int n)
     {
       return rand()%n + 1;
     }
  
     void omplirTaula3(TaulaEnters t)
     {
       long i;
    
       for (i=0; i<N; i++) 
         t[i]=randn(N);
     }

.. exercici::

   Mesureu empiricament el cost temporal d’un programa que inicialitza una taula i l’ordena pel mètode d’inserció utilitzant la següent acció::
   
     void ordenarTaula2(TaulaEnters& t)
     {
       int x,i,j;
       
       i=1; 
       while (i<N){
         x=t[i];
         j=i;
         while(j!=0 && x<t[j-1]){
           t[j]=t[j-1];
           j=j-1;
         }
         t[j]=x;
         i=i+1;
       }
     }

   Repetiu les mesures del temps d’execució de l’algorisme amb aquesta nova versió d’ordenar taula, per cadascuna de les tres versions d’omplirTaula vistes anteriorment.
   
.. exercici::

   Compareu la complexitat dels mètodes estudiats.
   
   +------------+-----------------------+-------------------------+-----------------------+
   | Valor de N | Omplir taula creixent | Omplir taula decreixent | Omplir taula aleatori |
   +------------+-----------------------+-------------------------+-----------------------+
   |    20000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |    40000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |    60000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |    80000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   |   100000   |                       |                         |                       |
   +------------+-----------------------+-------------------------+-----------------------+
   
   Dibuixeu una gràfica amb cada temps d’execució obtingut usant un full de càlcul (excel, maple o altres). A l’eix X poseu el valor de la N, i a l’eix Y el temps d’execució.

.. exercici::

   Per què la gràfica que s’obté és una paràbola? Per tal de justificar la resposta, podeu analitzar l’eficiència T(N), en el cas pitjor, de l’algorisme d’ordenació per selecció, i el mateix per l’algorisme d’ordenació per inserció. Per analitzar l’eficiència, compteu el nombre d’assignacions que fa cada algorisme, en funció del valor de N.


