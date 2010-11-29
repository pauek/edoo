
namespace edoo {

class Data {
  int mes, dia, any;

  static int dies_per_mes[12];
public:
  Data();
  Data(int m, int d, int a);
  Data(const Data& d);

  int dia() const;
  int mes() const;
  int any() const;

  void endavant(int dies);
  void endarrere(int dies);
  
  void mes_recent_que(const Data& d) const;
  
  void llegeix(istream& i);
  void escriu(ostream& o) const;
};

}
