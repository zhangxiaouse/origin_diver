#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include <boost/statechart/state_machine.hpp>

#include "../event/events.hpp"

using namespace boost::statechart;
using namespace std;

// Yuanguo: forward declaration
class NotShooting;

class Camera : public state_machine<Camera, NotShooting> {
 public:
  Camera();
  ~Camera();
  bool isMemAvail() const;
  bool isBatteryLow() const;

  string get_state() const;

  // transition actions
  void displayFocused(const EvInFocus& evInFocus);
  void allocMem(const EvShutterFull& evShutterFull);
  void powerSavingMode(const EvConfig& evConfig);
};

#endif