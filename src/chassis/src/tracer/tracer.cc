#include "tracer.h"

namespace cyberc3
{
  namespace vehicle
  {
    tracer::tracer(/* args */)
    {
      WhiteList.push_back(0x211);
      WhiteList.push_back(0x221);
      WhiteList.push_back(0x311);
    };

    tracer::~tracer(){};
    void tracer::Decode(const cyberc3::basic::can &CanData, const double time, cyberc3::feedback::tracer &Tracer)
    {
      switch (CanData.id)
      {
      case 0x211:
        Tracer.control_mode = CanData.data[1];
      case 0x221:
        Tracer.speed = static_cast<int16_t>(CanData.data[0] << 8 | CanData.data[1]);
        Tracer.rotate = static_cast<int16_t>(CanData.data[2] << 8 | CanData.data[3]);
        // std::cout << "speed:" << Tracer.speed << "   steer:" << Tracer.steer << std::endl;
        break;
      default:
        break;
      }
    }

    void tracer::setSteerSpeed(cyberc3::feedback::tracer &car_state, cyberc3::command::tracer_command &tracer_cmd, cyberc3::basic::can &CanData)
    {

      double left_speed_mps_ = tracer_cmd.left_speed_mps;
      double right_speed_mps_ = tracer_cmd.right_speed_mps;
      tracer_cmd.speed_mmps = (left_speed_mps_ + right_speed_mps_) * 500;
      tracer_cmd.rotate_0p001radps = (right_speed_mps_ - left_speed_mps_) * 1000 / 0.269;

      if (car_state.control_mode == 0x01)
      {
        if (car_state.is_init == false)
        {
          CanData.id = 0x421;
          CanData.len = 1;
          CanData.data[0] = 1;
          car_state.is_init = true;
        }
        else
        {
          CanData.id = 0x111;
          CanData.len = 8;
          CanData.data[0] = static_cast<uint8_t>(static_cast<int16_t>(tracer_cmd.speed_mmps) >> 8);
          CanData.data[1] = static_cast<uint8_t>(static_cast<int16_t>(tracer_cmd.speed_mmps));
          CanData.data[2] = static_cast<uint8_t>(static_cast<int16_t>(tracer_cmd.rotate_0p001radps) >> 8);
          CanData.data[3] = static_cast<uint8_t>(static_cast<int16_t>(tracer_cmd.rotate_0p001radps));
          CanData.data[4] = 0;
          CanData.data[5] = 0;
          CanData.data[6] = 0x00;
          CanData.data[7] = 0x00;
        }
      }
      else
      {
        car_state.is_init = false;
      }
    }

  } // namespace vehicle
} // namespace cyberc3