
class Frase {
  string _paraules[100];
  int _nparaules;
public:
  Frase();
  void afegeix_paraula(string s);
  void mostra(ostream& o);
  void esborra();
  int  num_paraules() const;
};
