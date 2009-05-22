
#include <map>
#include <iostream>
using namespace std;

class IP {
  int a, b, c, d;
public:
  IP() {}
  IP(int _a, int _b, int _c, int _d);
  bool operator==(const IP& ip) const;
  friend istream& operator>>(istream& i, IP& ip);
};

IP::IP(int _a, int _b, int _c, int _d) {
  a = _a; b = _b; c = _c; d = _d;
}

bool IP::operator==(const IP& ip) const {
  return a == ip.a && b == ip.b && c == ip.c && d == ip.d;
}

istream& operator>>(istream& i, IP& ip) {
  i >> ip.a >> ip.b >> ip.c >> ip.d;
}

bool connecta(map<int, IP>& ports, int port, const IP& ip) {
  map<int, IP>::iterator i = ports.find(port);
  if (i == ports.end()) {
    ports.insert(make_pair(port, ip));
    return true;
  }
  return false;
}

bool desconnecta(map<int, IP>& Ports, int port, const IP& ip) {
  map<int, IP>::iterator i = Ports.find(port);
  if (i != Ports.end() && i->second == ip) {
    Ports.erase(i);
    return true;
  }
  return false;
}

int main() {
  map<int, IP> Ports;
  string cmd;
  int port;
  IP ip;

  cin >> cmd;
  while (cmd != "FI") {
    cin >> port >> ip;

    if (cmd == "connecta") {
      if (connecta(Ports, port, ip))
	cout << "Connectat ";
      else
	cout << "Error de connexió ";
    }
    else if (cmd == "desconnecta") {
      if (desconnecta(Ports, port, ip)) {
	cout << "Desconnectat ";
      } else {
	cout << "Error de desconnexió ";
      }
    }
    cout << port << endl;
    cin >> cmd;
  }
}
