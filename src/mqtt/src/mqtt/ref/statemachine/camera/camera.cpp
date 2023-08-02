#include "camera.hpp"

#include <iostream>

#include "../state/istate.hpp"

// Yuanguo: although the full definition of the initial state "NotShooting" is
// not needed when declare Camera (thus only forward declaration is needed), the
// full definition of the states are necessary for
//       camera.initiate();
// thus, include NotShooting and its inner states definition here;
#include "../state/notshoot/idle.hpp"
#include "../state/notshoot/notshooting.hpp"
#include "../state/shoot/shooting.hpp"

using namespace std;

Camera::Camera() {
  cout << "Construct Camera" << endl;
}

Camera::~Camera() {
  cout << "Destruct Camera" << endl;
}

bool Camera::isMemAvail() const {
  return true;
}

bool Camera::isBatteryLow() const {
  return false;
}

string Camera::get_state() const {
  return string("CurrentState ------> ") + state_cast<const IState&>().getStateName();
}

void Camera::displayFocused(const EvInFocus& evInFocus) {
  cout << "[Transition Action]: Camera focused on objects" << endl;
}

void Camera::allocMem(const EvShutterFull& evShutterFull) {
  cout << "[Transition Action]: Memory allocated for storing the picture" << endl;
}

void Camera::powerSavingMode(const EvConfig& evConfig) {
  cout << "[Transition Action]: Camera goes into Power Saving Mode" << endl;
}

int main() {
  Camera camera;

  camera.initiate();
  cout << camera.get_state() << endl;

  camera.process_event(EvConfig());  //模拟按Config键
  cout << camera.get_state() << endl;

  camera.process_event(EvConfig());  //模拟按Config键 触发savemode 回到 idle
  cout << camera.get_state() << endl;

  camera.process_event(EvShutterHalf());  //模拟半按快门
  cout << camera.get_state() << endl;

  cout << "Press Shutter Full before focused" << endl;
  camera.process_event(EvShutterFull());  //在对焦完成之前，模拟全按快门
  cout << camera.get_state() << endl;

  camera.process_event(EvInFocus());  //模拟对焦完成事件
  cout << camera.get_state() << endl;

  camera.process_event(EvShutterRelease());  //模拟释放快门
  cout << camera.get_state() << endl;

  camera.process_event(EvStored());  //模拟存储完成
  cout << camera.get_state() << endl;

  return 0;
}