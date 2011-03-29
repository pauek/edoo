
class Racional {
  int _num, _den;

  // mètode privat per reduir el racional (2/8 => 1/4)
  void redueix(); 

public:
  Racional();
  Racional(int num, int den);
  Racional(const Racional& r);
  
  int num() const;
  int den() const;
  
  void set(int n, int d); 
  void setnum(int n);
  void setden(int d);

  Racional operator+(const Racional& r) const;
  Racional operator-(const Racional& r) const;
  Racional operator*(const Racional& r) const;
  Racional operator/(const Racional& r) const;

  void operator+=(const Racional& r);
  void operator-=(const Racional& r);
  void operator*=(const Racional& r);
  void operator/=(const Racional& r);

  // Operacions amb un enter (a la dreta)
  Racional operator+(int i) const;
  Racional operator-(int i) const;
  Racional operator*(int i) const;
  Racional operator/(int i) const;

  bool operator>(const Racional& r) const;
  bool operator<(const Racional& r) const;
  bool operator>=(const Racional& r) const;
  bool operator<=(const Racional& r) const;
  bool operator==(const Racional& r) const;
  bool operator!=(const Racional& r) const;
};

istream& operator>>(istream& i, Racional& r);
ostream& operator<<(ostream& o, const Racional& r);

