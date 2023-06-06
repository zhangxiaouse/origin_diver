#include "focused.hpp"

#include <iostream>

#include "../../camera/camera.hpp"
#include "storing.hpp"

using namespace std;

Focused::Focused() {
  cout << "Enter Focused" << endl;
}
Focused::~Focused() {
  cout << "Exit Focused" << endl;
}
string Focused::getStateName() const {
  return string("Focused");
}
result Focused::react(const EvShutterFull& evShutterFull) {
  cout << "Focused::react(const EvShutterFull & evShutterFull ), ";
  if (context<Camera>().isMemAvail()) {
    cout << "Guard: isMemAvail() is true" << endl;
    return transit<Storing>(&Camera::allocMem,
                            evShutterFull);  // transition action is Camera::allocMem()
  } else {
    cout << "Guard: isMemAvail() is false" << endl;
    // Yuanguo: Indicate that the event can be discarded. So, the
    // dispatch algorithm will stop looking for a reaction
    // and the machine remains in the Focused state.
    return discard_event();
  }
}