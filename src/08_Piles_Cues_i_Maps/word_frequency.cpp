
#include <iostream>
#include <fstream>
#include <map>
#include <list>
using namespace std;

typedef pair<string,int> Freq;

string neteja(string s) {
  string res = "";
  for (int k = 0; k < s.size(); k++) {
    if (isalpha(s[k]) && s[k] != ' ') 
      res += char(tolower(s[k]));
  }
  return res;
}

void llegeix_text(map<string,int>& fp) {
  ifstream fin("Pride_and_Prejudice.txt");
  string par;

  fin >> par;
  while (!fin.eof()) {
    par = neteja(par);
    if (!par.empty()) {
      map<string,int>::iterator i = fp.find(par);
      if (i != fp.end()) i->second++;
      else fp[par] = 1;
    }
    fin >> par;
  }
}

void inserta_maxim(int nmax, list<Freq> & freq, const Freq& f) {
  list<Freq>::iterator i = freq.begin();
  while (i != freq.end() && f.second > i->second)  {
    i++;
  }
  if (freq.size() < nmax) {
    freq.insert(i, f);
  } 
  else if (i != freq.begin()) {
    freq.insert(i, f);
    freq.pop_front();
  }
}
		   
void calcula_maxim(int nmax, list<Freq>& freq, const map<string,int>& fp) {
  map<string,int>::const_iterator i = fp.begin();
  while (i != fp.end()) {
    inserta_maxim(nmax, freq, *i);
    i++;
  }
}

void mostra_resultat(const list<Freq>& L) {
  list<Freq>::const_reverse_iterator i;
  for (i = L.rbegin(); i != L.rend(); i++) 
    cout << i->second << ' ' << i->first << endl;
}

int main() {
  map<string,int> freq;
  list<Freq> max_freq;

  llegeix_text(freq);
  calcula_maxim(25, max_freq, freq);
  mostra_resultat(max_freq);
}
