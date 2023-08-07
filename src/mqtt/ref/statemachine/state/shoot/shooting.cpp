#include "shooting.hpp"

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

Shooting::Shooting() {
  cout << "Enter Shooting" << endl;
}

Shooting::~Shooting() {
  cout << "Exit Shooting" << endl;
}

string Shooting::getStateName() const {
  return string("Shooting");
}

result Shooting::react(const EvShutterRelease& evShutterRelease) {
  cout << "Shooting::react(const EvShutterRelease & evShutterRelease)" << endl;
  return transit<NotShooting>();
}