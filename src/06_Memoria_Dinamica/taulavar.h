
class Taulavar {
  int *_dades;
  int  _max, _tam;
  
  void _copia_dades(int *orig, int *dest, int N);
  void _copia(const Taulavar& T);
 public:
  Taulavar();
  Taulavar(int tamany);
  Taulavar(const Taulavar& T);
  ~Taulavar();
  
  void operator=(const Taulavar& T);
  
  void redimensiona(int noutam);
  int  tamany() const;
  int  get(int k) const;    // com: ... = T[k]
  void set(int k, int val); // com: T[k] = val
  
  int  afegeix(int val); // afegeix al final
};
