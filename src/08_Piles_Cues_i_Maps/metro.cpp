
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <fstream>
using namespace std;

int distancia_minima(const vector< list<int> >& Graf, 
		     int orig, int dest) {
  vector<int> distancia(Graf.size(), -1);
  queue<int> pendents;
  
  distancia[orig] = 0;
  pendents.push(orig);

  while (!pendents.empty()) {
    int n = pendents.front();
    list<int>::const_iterator i = Graf[n].begin();
    for (; i != Graf[n].end(); i++) {
      if (distancia[*i] < 0) {
	distancia[*i] = distancia[n] + 1;
	pendents.push(*i);
      }
    }
    pendents.pop();
  }
  return distancia[dest];
}

int busca_estacio(map<string, int>& estacions, string nom) {
  map<string, int>::iterator i = estacions.find(nom);
  if (i != estacions.end()) {
    return i->second;
  }
  else return -1;
}

int index_estacio(map<string, int>& estacions, int& ultim, string nom) {
  int idx = busca_estacio(estacions, nom);
  if (idx == -1) {
    idx = ultim + 1;
    ultim++;
    estacions.insert(make_pair(nom, idx));
  }
  return idx;
}

void llegeix_graf(istream& i, 
		  map<string, int>& Estacions, 
		  vector< list<int> >& Graf) 
{
  int ultim = -1;
  string e1, e2;

  getline(i, e1, ';');
  getline(i, e2);
  while (!i.eof()) {
    int n1 = index_estacio(Estacions, ultim, e1);
    int n2 = index_estacio(Estacions, ultim, e2);
    Graf.resize(ultim + 1);
    Graf[n1].push_back(n2);
    Graf[n2].push_back(n1);
    getline(i, e1, ';');
    getline(i, e2);
  }
}

int main() {
  map<string, int> Estacions;
  vector< list<int> > Graf;

  {
    ifstream fin("metro.txt");
    llegeix_graf(fin, Estacions, Graf);
  }

  string orig, dest;
  cout << "Estacio orígen? "; getline(cin, orig);
  cout << "Estació destí? ";  getline(cin, dest);
  int norig = busca_estacio(Estacions, orig);
  int ndest = busca_estacio(Estacions, dest);
  if (norig == -1 || ndest == -1) {
    cout << "Alguna de les estacions no existeix" << endl;
  }
  else {
    int d = distancia_minima(Graf, norig, ndest);
    cout << "Distancia: " << d << " parades" << endl;
  }
}
