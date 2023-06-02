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
        break;
      case 0x221:
        Tracer.speed = static_cast<signed int>(CanData.data[0] << 8 | CanData.data[1]);
        Tracer.steer = static_cast<signed int>(CanData.data[2] << 8 | CanData.data[3]);
        std::cout << "speed:" << Tracer.speed << "   steer:" << Tracer.steer << std::endl;
        break;
      default:
        break;
      }
    }

  } // namespace vehicle
} // namespace cyberc3