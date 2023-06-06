#include "notshooting.hpp"

#include <iostream>

// Yuanguo:
// We need a full definition of Shooting in line
//      return transit<Shooting>();
// Focusing is the initial state of Shooting, thus we have to include
// focusing.hpp here, otherwise, compiler will complain about error like
//      incomplete type 'boost::statechart::simple_state ...
//      ... MostDerived = NotShooting, Context = Camera ....'
// inclusion of non-initial states of Shooting is not necessary;
#include "../shoot/focusing.hpp"
#include "../shoot/shooting.hpp"

using namespace std;

NotShooting::NotShooting() {
  cout << "Enter NotShooting" << endl;
}

NotShooting::~NotShooting() {
  cout << "Exit NotShooting" << endl;
}

string NotShooting::getStateName() const {
  return string("NotShooting");
}

result NotShooting::react(const EvShutterHalf& evShutterHalf) {
  cout << "NotShooting::react(const EvShutterHalf & evShutterHalf), ";
  if (context<Camera>().isBatteryLow()) {
    cout << "Guard: isBatteryLow() is true" << endl;
    //  We cannot react to the event ourselves, so we forward it
    // to our outer state (this is also the default if a state
    // defines no reaction for a given event).
    // 没有定义这个状态 所以需要抛弃到外围
    return forward_event();
  } else {
    cout << "Guard: isBatteryLow() is false" << endl;
    return transit<Shooting>();  // no transition action
  }
}