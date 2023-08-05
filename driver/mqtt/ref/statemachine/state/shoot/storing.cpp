#include "storing.hpp"

#include <iostream>

// Yuanguo:
// We need a full definition of NotShooting in line
//      return transit< NotShooting >();
// Idle is the initial state of NotShooting, thus we have to include idle.hpp
// here, otherwise, compiler will complain about error like
//      incomplete type 'boost::statechart::simple_state ...
//      ... MostDerived = NotShooting, Context = Camera ....'
// inclusion of non-initial states of NotShooting is not necessary;
#include "../notshoot/idle.hpp"
#include "../notshoot/notshooting.hpp"

using namespace std;

Storing::Storing() {
  cout << "Enter Storing" << endl;
}
Storing::~Storing() {
  cout << "Exit Storing" << endl;
}
string Storing::getStateName() const {
  return string("Storing");
}
result Storing::react(const EvStored& evStored) {
  cout << "Storing::react(const EvStored & evStored)" << endl;
  // Yuanguo: goto NotShooting when storing is finished;
  return transit<NotShooting>();
}
result Storing::react(const EvShutterRelease& evShutterRelease) {
  cout << "Storing::react(const EvShutterRelease & evShutterRelease)" << endl;
  cout << "Discard EvShutterRelease" << endl;
  // Yuanguo: Don't go to NotShooting until storing is finished, even if the
  // user releases the shutter
  return discard_event();
}