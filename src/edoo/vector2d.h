
class Vector2D {
  double x, y;
public:
  Vector2D();
  Vector2D(double x, double y);
  Vector2D(const Vector2D& v);

  double getX() const;
  double getY() const;

  void setX(double x);
  void setY(double y);

  Vector operator+(const Vector& v) const;
  Vector operator-(const Vector& v) const;
  double operator*(const Vector& v) const; // Producte Escalar

  void operator+=(const Matriu& M);
  void operator-=(const Matriu& M);
  void operator*=(const Matriu& M);
};

istream& operator>>(istream& i, Vector2D& M);
ostream& operator<<(ostream& o, const Vector2D& M);



