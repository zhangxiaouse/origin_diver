#include <iostream>

#include "events.hpp"

using namespace std;

//============EvConfig============//
EvConfig::EvConfig() {
  cout << "Construct EvConfig" << endl;
}
EvConfig::~EvConfig() {
  cout << "Destruct EvConfig" << endl;
}

//============EvShutterHalf============//
EvShutterHalf::EvShutterHalf() {
  cout << "Construct EvShutterHalf" << endl;
}
EvShutterHalf::~EvShutterHalf() {
  cout << "Destruct EvShutterHalf" << endl;
}

//============EvShutterFull============//
EvShutterFull::EvShutterFull() {
  cout << "Construct EvShutterFull" << endl;
}
EvShutterFull::EvShutterFull(const EvShutterFull& other) {
  cout << "Copy Construct EvShutterFull" << endl;
}

EvShutterFull::~EvShutterFull() {
  cout << "Destruct EvShutterFull" << endl;
}

//============EvShutterRelease============//
EvShutterRelease::EvShutterRelease() {
  cout << "Construct EvShutterRelease" << endl;
}
EvShutterRelease::~EvShutterRelease() {
  cout << "Destruct EvShutterRelease" << endl;
}

//============EvInFocus============//
EvInFocus::EvInFocus() {
  cout << "Construct EvInFocus" << endl;
}
EvInFocus::~EvInFocus() {
  cout << "Destruct EvInFocus" << endl;
}

//============EvStored============//
EvStored::EvStored() {
  cout << "Construct EvStored" << endl;
}
EvStored::~EvStored() {
  cout << "Destruct EvStored" << endl;
}