
#include <vector>
#include <list>
#include <queue>
#include <iostream>
using namespace std;

// 1+
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
// 1-

int main() {
  vector< list<int> > Graf;
  int tam, n1, n2;
  cin >> tam;
  Graf.resize(tam);
  cin >> n1 >> n2;
  while (n1 != -1 || n2 != -1) {
    Graf[n1].push_back(n2);
    Graf[n2].push_back(n1);
    cin >> n1 >> n2;
  }

  cin >> n1 >> n2;
  cout << distancia_minima(Graf, n1, n2) << endl;
}
