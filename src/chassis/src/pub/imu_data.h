#pragma once

namespace cyberc3 {
namespace data {

class IMUData {
public:
  class LinearAccleration {
  public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };
  class AngularVelocity {
  public:
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
  };
  class HeadingPitchRoll {
  public:
    double roll = 0.0;
    double pitch = 0.0;
    double yaw = 0.0;
  };

  double time = 0.0;
  LinearAccleration linear_acceleration;
  AngularVelocity angular_velocity;
  HeadingPitchRoll rpy;
};

} // namespace data
} // namespace cyberc3
