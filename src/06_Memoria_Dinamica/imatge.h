
#ifndef IMATGE_H
#define IMATGE_H

class Imatge {
  float *_pixels;   // Punter als píxels
  int _xtam, _ytam; // Tamanys horitzontal i vertical
  int _resolucio;   // Resolució de grisos

  void _copia_pixels(float *pixs, int tam);
  void _copia(const Imatge& I);
  void _redimensiona(int xtam, int ytam);
  void _omple_zeros();
public:
  Imatge();
  Imatge(int xtam, int ytam);
  Imatge(const Imatge& I);

  int tamany_x() const { return _xtam; }
  int tamany_y() const { return _ytam; }

  void operator=(const Imatge& I);

  float get_pixel(int x, int y) const;
  void  set_pixel(int x, int y, float val);

  void  inverteix();

  friend ostream& operator<<(ostream& o, const Imatge& I);
  friend istream& operator>>(istream& i, Imatge& I);
};


#endif
