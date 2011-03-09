
// 0+
class Taula {
  double *_p_reals;
  int     _tamany;
 public:
  Taula();
  Taula(int tamany);
  Taula(int tamany, double valor_inicial);
  Taula(const Taula& altra_taula);
  
  double get(int n) const;
  void   set(int n, double valor);
  
  int tamany() const;
};
// 0-
