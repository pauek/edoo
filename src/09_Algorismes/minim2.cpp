
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
  int n;
  vector<int> v;

  cin >> n;
  while (n != -1) {
    v.push_back(n);
    cin >> n;
  }

  vector<int>::iterator i;
  i = min_element(v.begin(), v.end());
  cout << *i << endl;
}
