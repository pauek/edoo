
const int BLANC = 255;

class Pixel {
  float red, green, blue;
public:
  void llegeix(istream& i, int nmax);
  void inverteix();
  void escriu(ostream &o) const;
};

