
/*
  
  Matriu2D:

    _x<Fila><Columna>

      ( _x00 _x01 )
      ( _x10 _x11 )

 */

class Matriu2D {
  double _x00, _x01, _x10, _x11;
public:
  Matriu2D();
  Matriu2D(double a, double b, double c, double d);
  Matriu2D(const Matriu2D& altra);

  double get00() const;
  double get01() const;
  double get10() const;
  double get11() const;

  void set00(double x);
  void set01(double x);
  void set10(double x);
  void set11(double x);

  Matriu operator+(const Matriu& M) const;
  Matriu operator-(const Matriu& M) const;
  Matriu operator*(const Matriu& M) const;

  void operator+=(const Matriu& M);
  void operator-=(const Matriu& M);
  void operator*=(const Matriu& M);

  bool operator==(const Matriu& M);
  bool operator!=(const Matriu& M);
};

istream& operator>>(istream& i, Matriu& M);
ostream& operator<<(ostream& o, const Matriu& M);
