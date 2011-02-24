
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
