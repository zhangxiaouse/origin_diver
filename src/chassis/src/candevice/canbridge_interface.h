#pragma once

#include "../tracer/data/basic/can.h"
// include "canmodules/basic/can.h"
namespace cyber_c3 {
namespace can_bridge {

class interface {
 public:
  virtual ~interface() = default;

  virtual int Read(cyberc3::basic::can &can_data) = 0;
  virtual void Write(const cyberc3::basic::can &can_data) = 0;
  virtual void Close() = 0;
};

}  // namespace can_bridge
}  // namespace cyber_c3