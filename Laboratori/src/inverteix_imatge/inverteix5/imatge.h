
const int XMAX = 400, YMAX = 320;

class Imatge {
  int tamx, tamy;
  Pixel pixel[XMAX][YMAX];
public:
  void llegeix(istream& i);
  void inverteix();
  void escriu(ostream& o) const;
};

