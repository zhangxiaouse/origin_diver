#include "idle.hpp"

#include <iostream>

#include "configuring.hpp"

using namespace std;

Idle::Idle() {
  cout << "Enter Idle" << endl;
}

Idle::~Idle() {
  cout << "Exit Idle" << endl;
}

string Idle::getStateName() const {
  return string("Idle");
}

result Idle::react(const EvConfig& evConfig) {
  cout << "Idle::react(const EvConfig & evConfig)" << endl;
  return transit<Configuring>();  // no transition action
}