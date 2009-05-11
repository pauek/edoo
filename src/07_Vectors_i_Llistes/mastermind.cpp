
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class Comb {
  vector<int> _nums;
public:
  Comb() {}
  Comb(int a, int b, int c, int d) {
    _nums.resize(4);
    _nums[0] = a, _nums[1] = b, _nums[2] = c, _nums[3] = d;
  }

  bool numeros_diferents() const;
  pair<int, int> morts_i_ferits(Comb& altra);
  friend ostream& operator<<(ostream& o, const Comb& C);
};

ostream& operator<<(ostream& o, const Comb& C) {
  return o << C._nums[0] << C._nums[1] << C._nums[2] << C._nums[3];
}

bool Comb::numeros_diferents() const {
  for (int i = 0; i < 4; i++) 
    for (int j = i+1; j < 4; j++) 
      if (_nums[i] == _nums[j]) return false;
  return true;
}

pair<int, int> Comb::morts_i_ferits(Comb& altra) {
  int morts = 0, ferits = 0;
  vector<bool> usat(4, false);
  for (int i = 0; i < 4; i++) {
    if (_nums[i] == altra._nums[i]) {
      morts++;
      usat[i] = true;
    }
  }
  for (int i = 0; i < 4; i++) {
    if (!usat[i]) {
      int j = 0;
      bool trobat = false;
      while (j < 4 && !trobat) {
	if (!usat[j] && altra._nums[j] == _nums[i]) {
	  trobat = usat[j] = true;
	  ferits++;
	}
	else j++;
      }
    }
  }
  return make_pair(morts, ferits);
}

void totes_les_combinacions(list<Comb>& L) {
  L.clear();
  for (int i = 0; i < 10; i++) 
    for (int j = 0; j < 10; j++) 
      for (int k = 0; k < 10; k++) 
	for (int l = 0; l < 10; l++) 
	  L.push_back(Comb(i, j, k, l));
}

bool numeros_diferents(const Comb& c) {
  return c.numeros_diferents();
}

Comb primer_candidat(list<Comb>& L) {
  list<Comb>::iterator i = find_if(L.begin(), L.end(), numeros_diferents);
  if (i == L.end()) i = L.begin();
  Comb c = *i;
  L.erase(i);
  return c;
}

int main() {
  list<Comb> candidats;
  totes_les_combinacions(candidats);
  Comb prova = primer_candidat(candidats);

  while (!candidats.empty()) {
    cout << candidats.size() << " Morts i ferits per " << prova << "? ";
    int morts, ferits;
    cin >> morts >> ferits;
    
    list<Comb>::iterator j = candidats.begin();
    while (j != candidats.end()) {
      pair<int, int> m_i_f = prova.morts_i_ferits(*j);
      if (m_i_f.first != morts || m_i_f.second != ferits) {
	j = candidats.erase(j);
      }
      else j++;
    }

    if (!candidats.empty()) {
      prova = primer_candidat(candidats);
    }
  }
  cout << prova << endl;
}
