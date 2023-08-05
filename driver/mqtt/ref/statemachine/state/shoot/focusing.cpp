#include "focusing.hpp"

#include <iostream>

#include "../../camera/camera.hpp"
#include "focused.hpp"

using namespace std;

Focusing::Focusing() {
  cout << "Enter Focusing" << endl;
}
Focusing::~Focusing() {
  cout << "Exit Focusing" << endl;
}
string Focusing::getStateName() const {
  return string("Focusing");
}
result Focusing::react(const EvInFocus& evInFocus) {
  cout << "Focusing::react(const EvInFocus & evInFocus)" << endl;
  return transit<Focused>(&Camera::displayFocused,
                          evInFocus);  // transition action is Camera::displayFocused()
}