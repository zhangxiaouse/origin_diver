#pragma once

namespace cyberc3 {
namespace command {
class car_command {
private:
  /* data */
public:
  bool pull_fork = false;
  bool push_fork = false;
  bool lift_fork = false;
  bool drop_fork = false;
  bool lean_forward_fork = false;
  bool lean_backward_fork = false;
  bool start_charge = false;
  bool start_pump = false;
  bool light_1_red = false;
  bool light_1_yellow = false;
  bool light_1_green = false;
  bool light_2_red = false;
  bool light_2_yellow = false;
  bool light_2_green = false;
  bool light_start = false;
  bool light_stop = false;
  bool light_reset = false;
  bool alarm_1 = false;
  bool alarm_2 = false;
  bool alarm_3 = false;
  void reset() {
    pull_fork = false;
    push_fork = false;
    lift_fork = false;
    drop_fork = false;
    lean_forward_fork = false;
    lean_backward_fork = false;
    start_charge = false;
    start_pump = false;
    light_1_red = false;
    light_1_yellow = false;
    light_1_green = false;
    light_2_red = false;
    light_2_yellow = false;
    light_2_green = false;
    light_start = false;
    light_stop = false;
    light_reset = false;
    alarm_1 = false;
    alarm_2 = false;
    alarm_3 = false;
  }
};
} // namespace command
} // namespace cyberc3