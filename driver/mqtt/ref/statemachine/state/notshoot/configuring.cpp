#include "configuring.hpp"

#include <iostream>

using namespace std;

Configuring::Configuring() {
  cout << "Enter Configuring" << endl;
}

Configuring::~Configuring() {
  cout << "Exit Configuring" << endl;
}

string Configuring::getStateName() const {
  return string("Configuring");
}