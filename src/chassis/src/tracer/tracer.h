#include "data/basic/can.h"
#include "data/feedback/feedback_tracer.h"
#include "data/command/tracer_command.h"
#include <iostream>
#include <vector>
#include <thread>
#include "lcan/lcan.h"

namespace cyberc3
{
  namespace vehicle
  {
    class tracer
    {
    public:
      std::vector<unsigned int> WhiteList;

    private:
    public:
      tracer(/* args */);
      ~tracer();
      void Decode(const cyberc3::basic::can &CanData, const double time, cyberc3::feedback::tracer &Tracer);
      void setSteerSpeed(cyberc3::feedback::tracer &car_state, cyberc3::command::tracer_command &tracer_cmd, cyberc3::basic::can &CanData);
    };

  }
}