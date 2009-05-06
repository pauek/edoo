
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct FMinim {
  int min;
  FMinim(int m) { min = m; }
  void operator()(int& n) {
    if (n < min) min = n;
  }
};

int main() {
  int n;
  vector<int> v;
  
  cin >> n;
  while (n != -1) {
    v.push_back(n);
    cin >> n;
  }

  FMinim M(v[0]);
  for_each(v.begin() + 1, v.end(), M);
  cout << M.min << endl;
}
