#pragma once

namespace cyberc3 {
namespace data {

class GNSSData {
public:
  // Geodetic from GNSS
  double time = 0.0;

  double longitude = 0.0;
  double latitude = 0.0;
  double altitude = 0.0;

  int position_init_status = 0;
  int heading_init_status = 0;
  int gps_num = 0;
};

} // namespace data
} // namespace cyberc3
